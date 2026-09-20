# NFS HD Reflections (Fork)

> **Fork Note**: This repository is a fork of [NFS HD Reflections by Aero_](https://github.com/AeroWidescreen/NFSHDReflections) adding full support for **Need for Speed: Hot Pursuit 2 (PC)** (**NFSHP2HDReflections**).

### What's New in this Fork (Need for Speed: Hot Pursuit 2)
- **High-Definition Vehicle Reflections**: Increases the resolution of dynamic vehicle cubemap faces and the composite environment spheremap from the vanilla 128x128 up to 512x512, 1024x1024, 2048x2048, etc.
- **Dynamic Projection Matrix Scaling**: Dynamically scales the 2D orthographic projection matrix for spheremap composition according to the selected resolution, ensuring reflections cover the entire vehicle body seamlessly without distortion or clipping.
- **Independent Resolution Controls**: Allows setting `CubemapRes` and `EnviromapRes` independently, or using resolution multipliers (`CubemapScale`, `EnviromapScale`).
- **AutoRes**: Automatically selects optimal reflection resolution based on your monitor's display resolution (512 for 1080p, 1024 for 1440p, 2048 for 4K).
- **Force Real-Time Dynamic LOD**: Forces dynamic cubemap faces to render every frame regardless of the in-game graphics detail setting (`ImproveReflectionLOD`).
- **Vehicle Reflection Brightness**: Allows fine-tuning reflection brightness/intensity (`VehicleReflectionBrightness`).
- **Full Compatibility**: Compatible with retail v242 / No-CD `NFSHP2.exe` (2.82 MB), Widescreen Fix (`HP2WSFix.asi`), and Ultimate ASI Loader (`d3d8.dll`).

---

## Original Mod Information (by Aero_)

## Download  
https://nfsmods.xyz/mod/3363  

## Optional HD Cubemap for Need for Speed Carbon  
https://mega.nz/file/gCxGUCpK#QlO57l7xjYyyFXGhjqlu6AcJq9nEFeZueNr2ywC04Hc  

## How To Use  
1. Move the appropriate *scripts* folder to your game's install folder.  
2. Download and extract [Ultimate-ASI-Loader.zip](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases).  
3. Move *dinput8.dll* to your game's install folder.  
4. Enjoy!  

## General Features (check INI file)
• AutoRes : Automatically changes the resolution.  
• OldGPUCompatibility: The cubemap resolution will always be rounded down to the nearest power of two.  
• Scale : Controls the resolution multiplier of reflections.  
• ImproveReflectionLOD : Increases the level of detail used in reflections.  
• ExtendRenderDistance : Increases the render distance of vehicle reflections.  
• RealFrontEndReflections : Enables real-time vehicle reflections in the front end.  
• RealisticChrome : Makes the chrome material more reflective.  
• VehicleReflectionBrightness : Controls the intensity of vehicle reflections.  

## FAQ  
Q: **Is this compatible with other mods?**  
A: I can't make any promises. It's been tested with Widescreen Fix, Xbox 360 Stuff, XtendedInput, Extra Options, and Unlimiter. All texture mods and car mods should work.  

Q: **What are the system requirements?**  
A: It depends on your resolution, settings, and other graphical enhancements being used. For 1080p, an NVIDIA GTX 1060 / AMD RX 480 should be more than enough for the default configuration.  

Q: **Why is a No-CD fix required?**  
A: Need for Speed games have protections (DRM) that make it difficult to view and modify their code, so No-CD patches are often recommended when using ASI mods. Additionally, the memory addresses in my mods are all hardcoded and it's not something I can easily change.  

Q: **Why is the Widescreen Fix recommended?**  
A: Most features I make are often designed to work with the Widescreen Fix. Carbon's "ReflectionContrast" (HD Reflections) and "LightingFix" (Widescreen Fix) features are a good example of this. The Widescreen Fix also provides a solid foundation that everyone should use, since it corrects visual and technical errors the PC ports have.  

 ## Credits
[Aero_](https://github.com/AeroWidescreen) : Creator of NFS HD Reflections.  
[ExOpts Team](https://github.com/ExOptsTeam) : This project is based on Extra Options and it wouldn't exist without them.  

 ## Thanks
[Archie](https://nfsmods.xyz/user/213) : Providing information needed for RestoreDetails in Need for Speed Carbon, and RestoreHeadlights in Need for Speed Underground 2.  
[Berkay & Nlgxzef](https://nfsmods.xyz/user/31) : Providing information needed for ExpandMemoryPools in Need for Speed Underground 2 and Need for Speed Most Wanted.  
[osdever](https://nfsmods.xyz/usermods/16) : Providing information needed for RestoreShaders in Need for Speed Most Wanted.  
[rx](https://www.youtube.com/c/rxyyy) : Providing information needed for DisableFlareRotation in Need for Speed Carbon.  
[SpeedyHeart](https://nfsmods.xyz/usermods/3) : Providing information needed for RestoreSkybox and AspectRatioFix in Need for Speed Carbon.  
