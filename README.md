# ShadowFlareHelper

![Logo](/README/icon256.png)

ShadowFlare Helper is an intergrated hack tool of the game Shadowflare, help you to experience the game in a brand new easy way.

![Screenshot](/README/ScreenShot1.png)  
![Screenshot](/README/ScreenShot2.png)  
![Screenshot](/README/ScreenShot3.png)

## How To Use
Put `SFHelper` and `libwinpthread-1.dll` to your ShadowFLare Game Folder.  
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
- Timely monitor and update Game data 
- Integrated [ShadowFlare WallHack](https://github.com/DearRichardLi/ShadowFlareWallHack) to this APP 



## Future Functions

- Unlimited & Instantly Teleport to ANY place.
- Player Status Modify
- Quest/Magic/GiantWarehouse Modify
- extend Swordman Atk Range
- Be super rich in game
- Customized Teleportation (To Any map, Any where)
- more......





## License
[License](#license)

## build shell
```
// windows: 

windres SFHelperResource.rc -o SFHelperResource.o 

gcc -o SFHelper SFHelperResource.o main.c libshlwapi.a libpsapi.a libwinpthread.dll.a -mwindows -lcomctl32 -luser32 -lgdi32 -pthread
```

## Update Log

### v0.1.0
- First publication  
- Bind game and print log  
- Read and modify Player name, LV, EXP, Prof., Companion LV, ...  
- 3 Available App Language (CHT, CHN, ENG)  
- Support 5 version of SF Game (Full 4 Episodes) (CHT, CHN, ENG, JPN, KOR)  
- Auto detect PC locale and set APP Language  
- Hide APP to taskbar  
- Compitable with resulution hack. (Administrator privilege needed)  

### v0.2.0
- Refresh data: after switch on, timely update player status in APP.  
- Keyboard Hook: after switch on, use Numpad/ Arror keys to move in game. (Integrated [ShadowFlare WallHack](https://github.com/DearRichardLi/ShadowFlareWallHack) )  
- Customize Move Distance, Move Delay, Refresh Data Delay Time  
- Display Player Position (Map ID, Map Name, X/Y Coordinate)  

### v0.3.0
- Teleport Function Available! choose destination Map and location, teleport you immediately like a Doraemon Anywhere Door!
- Assist functions Tab Available! "Open Warehouse at any time" "Infinite Power" "Revive Companion immediately".... and more....
- Magic Hack Available! Unlock Magic as you wish, modify Magic LV and EXP easily.
- Bug fixed: Map ID display incorrectly sometime.
More experience enhanced.