#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"
#include "settings.h"
#include "stdafx.h"

void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSHP2HDReflections.ini");

	// Resolution
	AutoRes = iniReader.ReadInteger("RESOLUTION", "AutoRes", 0);
	CubemapScale = iniReader.ReadFloat("RESOLUTION", "CubemapScale", 1.0f);
	EnviromapScale = iniReader.ReadFloat("RESOLUTION", "EnviromapScale", 1.0f);
	OldGPUCompatibility = iniReader.ReadInteger("RESOLUTION", "OldGPUCompatibility", 0);

	// Custom Resolution
	CubemapRes = iniReader.ReadInteger("CUSTOM RESOLUTION", "CubemapRes", 512);
	EnviromapRes = iniReader.ReadInteger("CUSTOM RESOLUTION", "EnviromapRes", 512);

	// General
	VehicleReflectionBrightness = iniReader.ReadFloat("GENERAL", "VehicleReflectionBrightness", 1.0f);
	ImproveReflectionLOD = iniReader.ReadInteger("GENERAL", "ImproveReflectionLOD", 1);

	if (AutoRes)
	{
		int screenY = GetSystemMetrics(SM_CYSCREEN);
		if (screenY >= 1440)
			CubemapRes = 1024;
		else if (screenY >= 1080)
			CubemapRes = 512;
		else
			CubemapRes = 256;

		EnviromapRes = CubemapRes;
	}

	// Resolution Multipliers
	CubemapRes = (int)(CubemapRes * CubemapScale);
	EnviromapRes = (int)(EnviromapRes * EnviromapScale);

	if (OldGPUCompatibility)
	{
		// Rounds the cubemap resolution down to the nearest power of two
		auto MakePOT = [](int x) -> int {
			if (x <= 0) return 128;
			int pot = 1;
			while ((pot << 1) <= x) pot <<= 1;
			return pot;
		};
		CubemapRes = MakePOT(CubemapRes);
		EnviromapRes = MakePOT(EnviromapRes);
	}

	// Safety clamping
	if (CubemapRes < 32) CubemapRes = 32;
	if (EnviromapRes < 32) EnviromapRes = 32;

	static float fCubemapRes = (float)CubemapRes;
	static float fEnviromapRes = (float)EnviromapRes;
	// The 2D projection matrix scale for the spheremap composite:
	// Vanilla: 128.0f / 256.0f = 0.5f
	static float fEnviroScale = (float)EnviromapRes / 256.0f;

	// Writes Resolution Values in NFSHP2.exe
	{
		// Composite Environment Map Target Width & Height
		injector::WriteMemory<uint32_t>(0x53E144, EnviromapRes, true);
		injector::WriteMemory<uint32_t>(0x53E149, EnviromapRes, true);

		// 6 Cubemap Faces Target Width & Height
		injector::WriteMemory<uint32_t>(0x53E176, CubemapRes, true);
		injector::WriteMemory<uint32_t>(0x53E17B, CubemapRes, true);

		// Viewport float dimensions:
		// 0x53E12A: mov ecx, dword ptr [0x665474] -> point to &fEnviromapRes
		injector::WriteMemory<float*>(0x53E12C, &fEnviromapRes, true);

		// 0x53E169: mov eax, dword ptr [0x665474] -> point to &fCubemapRes
		injector::WriteMemory<float*>(0x53E16A, &fCubemapRes, true);

		// Also update the original float constant at 0x665474
		injector::WriteMemory<float>(0x665474, fCubemapRes, true);

		// Scale the 2D orthographic projection matrix for spheremap composite!
		// Static reflection matrix:
		injector::WriteMemory<float>(0x53EB4F, fEnviroScale, true); // Scale X
		injector::WriteMemory<float>(0x53EB54, fEnviroScale, true); // Scale Y

		// Dynamic reflection matrix:
		injector::WriteMemory<float>(0x53ED47, fEnviroScale, true); // Scale X
		injector::WriteMemory<float>(0x53ED4C, fEnviroScale, true); // Scale Y
	}

	if (VehicleReflectionBrightness != 1.0f)
	{
		// Scale default reflection brightness (0xFF = 255)
		uint32_t brightness = (uint32_t)(255.0f * VehicleReflectionBrightness);
		if (brightness > 255) brightness = 255;
		injector::WriteMemory<uint32_t>(0x53E073, brightness, true); // Blue default
		injector::WriteMemory<uint32_t>(0x53E079, brightness, true); // Green default
		injector::WriteMemory<uint32_t>(0x53E080, brightness, true); // Red default
	}

	if (ImproveReflectionLOD)
	{
		// Force dynamic cubemap faces to always render every frame
		// 0x53E8FD: jne 0x53eb39 (6 bytes: 0F 85 36 02 00 00) -> NOP so it never skips dynamic face updates
		injector::MakeNOP(0x53E8FD, 6, true);
	}
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		// Check if .exe file is compatible (NFSHP2.exe entry point 0x1C76C1 -> 0x5C76C1)
		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x5C76C1)
		{
			Init();
		}
		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use retail v242 / No-CD NFSHP2.exe (2.82 MB (2,965,504 bytes)).", "NFSHP2 HD Reflections", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
}
