# ShadowFlareHelper

![Logo](/README/icon256.png)

ShadowFlare Helper is an intergrated hack tool of the game Shadowflare, help you to experience the game in a brand new easy way.

![Screenshot](/README/ScreenShot1.png)

## How To Use
Put `SFHelper` to your ShadowFLare Game Folder.  
Opening SF Game and Load your Savefile.  
Choose SF Version from ComboBox and "Bind Game"  
After Binding successfully, Hack functions unlock.  
ATTENTION: Re-Bind Game after you S/L Savefile.  

## Feature
- Support 5 version of SF Game (Full 4 Episodes) (CHT, CHN, ENG, JPN, KOR) 
- 3 available APP Lang (CHT, CHN, ENG)  
- Auto detect user PC locale 
- Compatible with SF Resolution Hack 
- Hide APP to Task Bar 
- Modify as much data as possible





## Future Functions
- Timely monitor and update Game data 
- Integrate [ShadowFlare WallHack](https://github.com/DearRichardLi/ShadowFlareWallHack) to this APP 
- Unlimited & Instantly Teleport to ANY place.
- Player Status Modify
- Quest/Magic/GiantWarehouse Modify
- more......





## License
[License](#license)

## build shell
```
// windows: 

windres SFHelperResource.rc -o SFHelperResource.o 

gcc -o SFHelper SFHelperResource.o main.c libshlwapi.a libpsapi.a -mwindows -lcomctl32 
```

