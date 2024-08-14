#include <Windows.h>


#ifndef _SF_HELPER_STD
#define _SF_HELPER_STD

    // Windows Message type ID (must not duplicate with sys WM)
#define WM_TRAYICON       (WM_USER + 1)
#define WM_REFRESH_DATA   (WM_USER + 2)
#define WM_GAME_LOGOUT    (WM_USER + 3)
#define WM_GAME_CLOSED    (WM_USER + 4)

    // 10 tabs in current version
#define APP_TAB_COUNT           10

#define SF_VERSION_COUNT         5
#define SF_SEX_COUNT             2
#define SF_PROF_COUNT            4
#define SF_COMPANION_COUNT       6
#define SF_MAGIC_COUNT          22
#define SF_TELEPORT_GATE_COUNT  51
#define PLAYER_NAME_LEN         20
#define MAP_NAME_LEN           256
#define TELEPORT_PRESET_COUNT  104
#define SCENARIO_COUNT         209

#define DEFAULT_CHECK_GAME_CLOSED_WAIT_MILLISECONDS 10

    // available Version
typedef struct _Version{
    LPCWSTR Language;
    LPCWSTR VersionNumber;
    LPCWSTR Info;
    LPCWSTR WindowTitle;
} Version;

    // Hack running status
typedef struct _Hack_Statu_Info{
    DWORD     App_Language;
    BOOL      isBind_Game;
    DWORD     Game_Mode; // 0: single; 1: ol-host; 2: ol-client; default: -1
    DWORD     Client_Index;
    ULONG_PTR Character_Attribute_P;
    BOOL      isGlobal_Keyboard_Hooked;
    BOOL      isChecking_Game;
    BOOL      isRefresh_On;
    DWORD     Data_Refresh_Delay;
    DWORD     LastErrorCode;
} Hack_Statu_Info;
#define DEFAULT_GAME_MODE                       -1
#define DEFAULT_CLIENT_INDEX                    -1
#define DEFAULT_DATA_REFRESH_DELAY_MILLISECOND 200

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

    // variable during using hook
typedef struct _Hook_Move_Info{
    __int32 X;
    __int32 Y;
    DWORD   Move_Distance;
    DWORD   Move_Delay;
} Hook_Move_Info;
#define DEFAULT_MOVE_DISTANCE          100
#define DEFAULT_MOVE_DELAY_MILLISECOND  10

typedef struct _SF_Tab_Info{ // 14 tabs
    __int32 Tab_Status;
    __int32 Tab_Item;
    __int32 Tab_Magic;
    __int32 Tab_Shop;
    __int32 Tab_Warehouse;
    __int32 Tab_G_Warehouse;
    __int32 Tab_Teleport_Gates;
    __int32 Tab_Quest;
    __int32 Tab_Help;
    __int32 Tab_Esc_Menu;
    __int32 Tab_Customize_Outfit;
    __int32 Tab_Minimap;
    __int32 Tab_Special_Item;
    __int32 Tab_Blackjack;
} SF_Tab_Info;

typedef struct _God_Mode{
    __int32 Atk_Speed;
    __int32 Walking_Speed;
    __int32 HP_1;
    __int32 HP_2;
    __int32 MP_1;
    __int32 MP_2;
    __int32 Strength;
    __int32 Atk;
    __int32 Def;
    __int32 Hit_Rate;
    __int32 Evasion_Rate;
    __int32 M_Atk;
    __int32 M_Def;
    __int32 M_Hit_Rate;
    __int32 M_Evasion_Rate;
} God_Mode;
#endif /* SFHelperStd.h */