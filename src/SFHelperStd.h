#include <Windows.h>


#ifndef _SF_HELPER_STD
#define _SF_HELPER_STD

/*
 * define the supported versons.
 * 
 * This program only support the "original" game versions.
 * And is not currently compatible with 
 * "resulution hack" "open game with multiple copies" "Black Jack hack (From CN community)"
 */
#define SF_VERSION_COUNT 5
typedef struct _Version{
    LPCWSTR Language;
    LPCWSTR VersionNumber;
    LPCWSTR Info;
    LPCWSTR WindowTitle;
} Version;
#define SF_SEX_COUNT 2
#define SF_PROF_COUNT 4
#define SF_COMPANION_COUNT 6

/*
 * define the default moving distance 
 * and the delay between two movements (in millisecond)
 * 
 * in SF, the coordinate is presented as X and Y (signed int32) 
 */
#define DEFAULT_MOVING_DISTANCE 100
#define DEFAULT_MOVING_DELAY_MILLISECONDS 10


/*
 * define the sleep duration when an error occur, then exit.
 * and the waiting time to check whether the game is closed.
 */
#define DEFAULT_SLEEP_MILLISECONDS 3000
#define DEFAULT_CHECKIFSFCLOSED_WATING_MILLISECONDS 10 


/*
 * used for multi threads and Keyboard Hook.
 * Avoid High CPU Usage
 */
#define DEFAULT_CPU_SLEEP_MILLISECONDS 10

// Hack running status
typedef struct _Hack_Statu_Info{
    DWORD     App_Language;
    BOOL      isBind_Game;
    DWORD     Game_Mode; // 0: single; 1: ol-host; 2: ol-client; default: -1
    DWORD     Client_Index;
    ULONG_PTR Character_Attribute_P;
    BOOL      isGlobal_Keyboard_Hooked;
    DWORD     LastErrorCode;
}Hack_Statu_Info;
#define DEFAULT_GAME_MODE    -1
#define DEFAULT_CLIENT_INDEX -1
// Info of the SF Game Window
typedef struct _SF_Window_Info{
    DWORD   SF_Version;
    HWND    hWnd;
    DWORD   PID;
    DWORD   TID;
    HANDLE  SF_Handle;
    DWORD   Module_Count;
    HMODULE Base_hModule;
} SF_Window_Info;



#endif /* SFHelperStd.h */