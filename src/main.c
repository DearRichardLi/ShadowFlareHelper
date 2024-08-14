#define UNICODE

#include <Windows.h>
#include <Windowsx.h>
#include <Shlwapi.h>
#include <CommCtrl.h>
#include <stdlib.h>
#include <WinDef.h>
// #include <tchar.h>
// #include <wchar.h>
#include <locale.h> 
#include <stdio.h>
#include <pthread.h>

#include "SFHelperAddr.c"
#include "SFHelperException.c"
#include "SFHelperFunc.c"
#include "SFHelperLanguage.c"
#include "SFHelperStd.c"
#include "SFHelperWindows.c"
#include "SFHelperResource.c"



// extern LPCWSTR APP_VERSION;
extern LPCWSTR GitHub_Address;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];

Hack_Statu_Info Hack_Status = {
        APP_DEFAULT_LANGUAGE, // CHT, but auto change to locale lan (Windows sys)
        FALSE,                // Have Not Bind Game
        DEFAULT_GAME_MODE,    // 0: single; 1: ol-host; 2: ol-client; default: -1
        DEFAULT_CLIENT_INDEX, // default 0xFFFFFFFF, like in game memory
        0x0,                  // Character_Attribute pointer
        FALSE,                // No keyboard hook
        FALSE,                // Check game keep opening
        FALSE,                // Refresh Game data to APP: OFF
        DEFAULT_DATA_REFRESH_DELAY_MILLISECOND, // Data_Refresh_Delay
        APP_NORMAL            // last err code
};
SF_Window_Info SF_Window = {
        0,    // SF_Version
        NULL, // hWnd
        0,    // PID
        0,    // TID
        0,    // SF_Handle
        0,    // Module_Count
        NULL  // Base_hModule
};
Hook_Move_Info Hook_Move = {
        0,                              // X
        0,                              // Y
        DEFAULT_MOVE_DISTANCE,          // move distance
        DEFAULT_MOVE_DELAY_MILLISECOND  // move delay
};
SF_Tab_Info SF_Tab = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // app icon
HICON icon;
HICON iconsm;

    // Fonts. CH: 宋体; EN: Times New Roman
HFONT hFontCH;
HFONT hFontEN;

    // Tray Bar Data
NOTIFYICONDATAW nid;

    // Main Window
HWND hwnd;
    // APP Menu
HMENU hMenuBar;

//window controls
    // tab control
HWND hwndTab;
__int32 iPageOld = 0;
__int32 iPageNew = 0;
    // tab 0, Init
HWND hwndButtonOpenSF, hwndComboBoxGameVersion, hwndButtonBindGame,
        hwndButtonRefresh,
        hwndStaticRefreshDelay, hwndEditRefreshDelay, hwndUpDownRefreshDelay,
        hwndEditInitLog, 
        hwndStaticGameMode, hwndEditGameMode, hwndStaticOnlineRole, hwndEditOnlineRole, 
        hwndStaticPlayerName, hwndEditPlayerName, hwndButtonApplyPlayerName,
        hwndStaticLV, hwndEditLV, hwndUpDownLV, hwndStaticSex, hwndComboBoxSex, 
        hwndStaticEXP, hwndEditEXP, hwndButtonApplyExp,
        hwndStaticProf, hwndComboBoxProf, hwndStaticProfToBe, hwndComboBoxProfToBe,
        hwndStaticCompanionLV, hwndEditCompanionLV, hwndUpDownCompanionLV,
        hwndStaticCompanionID, hwndComboBoxCompanionID,
        hwndStaticCompanionEXP, hwndEditCompanionEXP, hwndButtonApplyCompanionExp,
        hwndButtonChangeLanguage;
BOOL isRefreshDelayChanged = FALSE;
BOOL isLVChanged           = FALSE;
BOOL isCompanionLVChanged  = FALSE;
    // tab 1, WallHack
HWND hwndButtonHook, hwndStaticHookStatus, hwndEditHookStatus,
        hwndEditHookLog,
        hwndStaticMapID, hwndEditMapID, 
        hwndStaticX, hwndEditX, hwndStaticY, hwndEditY,
        hwndEditMapName,
        hwndStaticMapGateID, hwndEditMapGateID,
        hwndStaticMoveDistance, hwndEditMoveDistance, hwndUpDownMoveDistance,
        hwndStaticMoveDelay, hwndEditMoveDelay, hwndUpDownMoveDelay,
        hwndStaticTeleport, hwndComboBoxTeleportPreset,
        hwndStaticTeleportMapID, hwndComboBoxTeleportMapName, hwndEditTeleportMapID,
        hwndGroupBoxGateOrXY, hwndButtonRadioGate, hwndButtonRadioXY,
        hwndStaticTeleportGateID, hwndEditTeleportGateID, hwndStaticTeleportGateWarn,
        hwndStaticTeleportX, hwndEditTeleportX, hwndStaticTeleportY, hwndEditTeleportY,
        hwndButtonTeleport;
BOOL isMoveDistanceChanged = FALSE;
BOOL isMoveDelayChanged    = FALSE;
    // tab 2, Assist
HWND hwndButtonOpenWarehouse, hwndButtonOpenGaintWarehouse, 
        hwndButtonOpenCustomOutfit, hwndButtonPauseGame,
        hwndButtonInfinitePower, hwndButtonCompanionRevive,
        hwndButtonExtraLandmine, hwndButtonExtraLandminePower,
        hwndButtonBeRich, hwndButtonNoMonsterDisplay,
        hwndButtonMagicLVto30, hwndButtonCrazySpeed,
        hwndButtonGodMode, hwndButtonExtendAtkRange,
        hwndEditAssistLog,
        hwndButtonReviveEnemy,
        hwndButtonSuicide;
    // tab 3, Magic
HWND hwndStaticMagicName1, hwndStaticMagicLV1, hwndStaticMagicEXP1,
        hwndStaticMagicName2, hwndStaticMagicLV2, hwndStaticMagicEXP2,
        hwndGroupBoxTab1,  hwndGroupBoxTab2,  hwndGroupBoxTab3, hwndGroupBoxTab4,
        hwndButtonMagic1,  hwndEditMagicLV1,  hwndUpDownMagicLV1,  hwndEditMagicEXP1,  hwndUpDownMagicEXP1, 
        hwndButtonMagic2,  hwndEditMagicLV2,  hwndUpDownMagicLV2,  hwndEditMagicEXP2,  hwndUpDownMagicEXP2, 
        hwndButtonMagic3,  hwndEditMagicLV3,  hwndUpDownMagicLV3,  hwndEditMagicEXP3,  hwndUpDownMagicEXP3, 
        hwndButtonMagic4,  hwndEditMagicLV4,  hwndUpDownMagicLV4,  hwndEditMagicEXP4,  hwndUpDownMagicEXP4, 
        hwndButtonMagic5,  hwndEditMagicLV5,  hwndUpDownMagicLV5,  hwndEditMagicEXP5,  hwndUpDownMagicEXP5, 
        hwndButtonMagic6,  hwndEditMagicLV6,  hwndUpDownMagicLV6,  hwndEditMagicEXP6,  hwndUpDownMagicEXP6, 
        hwndButtonMagic7,  hwndEditMagicLV7,  hwndUpDownMagicLV7,  hwndEditMagicEXP7,  hwndUpDownMagicEXP7, 
        hwndButtonMagic8,  hwndEditMagicLV8,  hwndUpDownMagicLV8,  hwndEditMagicEXP8,  hwndUpDownMagicEXP8, 
        hwndButtonMagic9,  hwndEditMagicLV9,  hwndUpDownMagicLV9,  hwndEditMagicEXP9,  hwndUpDownMagicEXP9, 
        hwndButtonMagic10, hwndEditMagicLV10, hwndUpDownMagicLV10, hwndEditMagicEXP10, hwndUpDownMagicEXP10, 
        hwndButtonMagic11, hwndEditMagicLV11, hwndUpDownMagicLV11, hwndEditMagicEXP11, hwndUpDownMagicEXP11, 
        hwndButtonMagic12, hwndEditMagicLV12, hwndUpDownMagicLV12, hwndEditMagicEXP12, hwndUpDownMagicEXP12, 
        hwndButtonMagic13, hwndEditMagicLV13, hwndUpDownMagicLV13, hwndEditMagicEXP13, hwndUpDownMagicEXP13, 
        hwndButtonMagic14, hwndEditMagicLV14, hwndUpDownMagicLV14, hwndEditMagicEXP14, hwndUpDownMagicEXP14, 
        hwndButtonMagic15, hwndEditMagicLV15, hwndUpDownMagicLV15, hwndEditMagicEXP15, hwndUpDownMagicEXP15, 
        hwndButtonMagic16, hwndEditMagicLV16, hwndUpDownMagicLV16, hwndEditMagicEXP16, hwndUpDownMagicEXP16, 
        hwndButtonMagic17, hwndEditMagicLV17, hwndUpDownMagicLV17, hwndEditMagicEXP17, hwndUpDownMagicEXP17, 
        hwndButtonMagic18, hwndEditMagicLV18, hwndUpDownMagicLV18, hwndEditMagicEXP18, hwndUpDownMagicEXP18, 
        hwndButtonMagic19, hwndEditMagicLV19, hwndUpDownMagicLV19, hwndEditMagicEXP19, hwndUpDownMagicEXP19, 
        hwndButtonMagic20, hwndEditMagicLV20, hwndUpDownMagicLV20, hwndEditMagicEXP20, hwndUpDownMagicEXP20, 
        hwndButtonMagic21, hwndEditMagicLV21, hwndUpDownMagicLV21, hwndEditMagicEXP21, hwndUpDownMagicEXP21, 
        hwndButtonMagic22, hwndEditMagicLV22, hwndUpDownMagicLV22, hwndEditMagicEXP22, hwndUpDownMagicEXP22; 
BOOL isMagicLVChanged = FALSE;

pthread_t th_GlobalKeyboardHook = 0;
pthread_t th_CheckGameCloseOrLogout = 0;
pthread_t th_SendRefreshSignal = 0;

/*Init public control libs*/
// INITCOMMONCONTROLSEX icex;
// icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
// icex.dwICC = ICC_TAB_CLASSES;
// InitCommonControlsEx(&icex);

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
    HWND hwndParent = GetParent(hwndTab);
    switch(Message){
    case WM_CREATE: {
        CreateFonts_CH_EN(&hFontCH, &hFontEN);
        InitTrayBarData(hwnd);
        CreateTabControl(hwnd, lParam);
        
            // Create Tab Contents
        // tab 0, Init
        CreateTab0();
        // tab 1, WallHack
        CreateTab1();
        // tab 2, Assist
        CreateTab2(); 
        // tab 3, Magic
        CreateTab3(); 


        SwitchBindGameControl(hwndTab, FALSE);
            // initially show contents of tab 0
        ShowTabContents(hwndTab, 1, -1);
        ShowTabContents(hwndTab, 2, -1);
        ShowTabContents(hwndTab, 3, -1);
        // ShowTabContents(hwndTab, 4, -1);

        UseCustomFont(hwndTab, hFontEN);
        Shell_NotifyIconW(NIM_ADD, &nid);
        return 0;
    }
    break; // WM_CREATE
    case WM_COMMAND:
        switch(LOWORD(wParam) >> 8){
        case 0x0:
            switch(LOWORD(wParam) & 0xff){
            case 0xff & IDM_OPTION_HIDE:
                ShowWindow(hwnd, SW_HIDE);
                break;
            case 0xff & IDM_OPTION_EXIT:
                SendMessageW(hwnd, WM_DESTROY, 0, 0);
                PostQuitMessage(0);
                break;
            case 0xff & IDM_ABOUT_HELP:
                    // print help on log area?
                MessageBoxW(hwnd, L"Not finished.", L"No", MB_OK);
                break;
            case 0xff & IDM_ABOUT_ABOUTAPP:
                    // print About on MsgBox?
                MessageBoxW(hwnd, L"Not finished.", L"No", MB_OK);
                break;
            case 0xff & IDM_ABOUT_ADDRESS:
                ShellExecuteW(NULL, L"open", GitHub_Address, NULL, NULL, SW_SHOWNORMAL);
                break;
            }
        break;
        case 0x1:
            switch(LOWORD(wParam) & 0xff){
            case 0xff & IDC_BUTTON_OPENSF: {
                if(OpenSF() != TRUE){
                    ExceptionHandler();
                }
                OpenSFLogger(hwndEditInitLog);
            }
                break;
            case 0xff & IDC_COMBOBOX_GAMEVERSION: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyGameVersion(hwndParent);
                }
                break;
            case 0xff & IDC_BUTTON_BIND_GAME: 
                CloseAllExtraThread();
                Hack_Status.isBind_Game = BindSF();
                if(Hack_Status.isBind_Game){
                    SwitchBindGameControl(hwndTab, Hack_Status.isBind_Game);
                    GetAndDisplayValues(hwndParent);
                    DisplayRefreshDelay(hwndParent);
                    DisplayMoveDistance(hwndParent);
                    DisplayMoveDelay(hwndParent);
                    ApplyTeleportMapID(hwndParent);
                    SFHelperCreateThread(&th_CheckGameCloseOrLogout, NULL,
                            (void*(*)(void*))CheckGameCloseOrLogout, NULL);
                    // Debug_Printer();
                } else{
                    CloseAllExtraThread();
                    SwitchBindGameControl(hwndTab, Hack_Status.isBind_Game);
                    if(Hack_Status.LastErrorCode != APP_NORMAL){
                        ExceptionHandler();
                    }
                }
                BindSFLogger(hwndEditInitLog);
                break;
            case 0xff & IDC_BUTTON_REFRESH:
                if(Hack_Status.isRefresh_On){
                    Hack_Status.isRefresh_On = FALSE;
                    SFHelperJoinThread(th_SendRefreshSignal, NULL);
                } else{
                    Hack_Status.isRefresh_On = TRUE;
                    SFHelperCreateThread(&th_SendRefreshSignal, NULL,
                            (void*(*)(void*))SendRefreshSignal, NULL); 
                }
                SwitchRefreshControl(hwndTab, Hack_Status.isRefresh_On);
                RefreshLogger(hwndEditInitLog);
                break;          
            case 0xff & IDC_EDIT_REFRESH_DELAY:
                if(HIWORD(wParam) == EN_CHANGE && !isRefreshDelayChanged){
                    isRefreshDelayChanged = TRUE; // this is to avoid endless call WndProc
                    Hack_Status.Data_Refresh_Delay = KeepWndNumWStrInRange(
                            hwndParent, LOWORD(wParam), 5, 1, 9999, TRUE, 10);
                    isRefreshDelayChanged = FALSE; // this is to avoid endless call WndProc
                }
                break;
            case 0xff & IDC_BUTTON_APPLY_PLAYER_NAME: 
                ApplyPlayerName(hwndParent);
                break;
            case 0xff & IDC_EDIT_LV: 
                if(HIWORD(wParam) == EN_CHANGE && !isLVChanged){
                    isLVChanged = TRUE; // this is to avoid endless call WndProc
                    KeepWndNumWStrInRange(hwndParent, LOWORD(wParam), 4, 1, 100, TRUE, 10);
                    ApplyPlayerLV(hwndParent);
                    isLVChanged = FALSE; // this is to avoid endless call WndProc
                }
                break;
            case 0xff & IDC_COMBOBOX_SEX: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyPlayerSex(hwndParent);
                }
                break;
            case 0xff & IDC_BUTTON_APPLY_EXP: 
                ApplyPlayerEXP(hwndParent);
                break;
            case 0xff & IDC_COMBOBOX_PROF: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyPlayerProf(hwndParent);
                }
                break;
            case 0xff & IDC_COMBOBOX_PROF_TO_BE: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyPlayerProfToBe(hwndParent);
                }
                break;
            case 0xff & IDC_EDIT_COMPANION_LV:
                if(HIWORD(wParam) == EN_CHANGE && !isCompanionLVChanged){
                    isCompanionLVChanged = TRUE; // this is to avoid endless call WndProc
                    KeepWndNumWStrInRange(hwndParent, LOWORD(wParam), 3, 1, 35, TRUE, 10);
                    ApplyCompanionLV(hwndParent);
                    isCompanionLVChanged = FALSE; // this is to avoid endless call WndProc
                }
                break;
            case 0xff & IDC_COMBOBOX_COMPANION_ID: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyCompanionID(hwndParent);
                }
                break;
            case 0xff & IDC_BUTTON_APPLY_COMPANION_EXP: 
                ApplyCompanionEXP(hwndParent);
                break;
            case 0xff & IDC_BUTTON_CHANGE_LANG: // Change Lan
                ChangeLanguage();
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
                DrawMenuBar(hwnd);
                break;
            }
        break;
        case 0x2:
            switch(LOWORD(wParam) & 0xff){
            case 0xff & IDC_BUTTON_HOOK:
                if(Hack_Status.isGlobal_Keyboard_Hooked){
                    Hack_Status.isGlobal_Keyboard_Hooked = FALSE;
                    SFHelperJoinThread(th_GlobalKeyboardHook, NULL);
                } else{
                    Hack_Status.isGlobal_Keyboard_Hooked = TRUE;
                    SFHelperCreateThread(&th_GlobalKeyboardHook, NULL,
                            (void*(*)(void*))GlobalKeyboardHook, NULL); 
                }
                HookLogger(hwndEditHookLog);
                DisplayHookStatus(hwndParent);
                break;
            case 0xff & IDC_EDIT_MOVE_DISTANCE:
                if(HIWORD(wParam) == EN_CHANGE && !isMoveDistanceChanged){
                    isMoveDistanceChanged = TRUE; // this is to avoid endless call WndProc
                    Hook_Move.Move_Distance = KeepWndNumWStrInRange(
                            hwndParent, LOWORD(wParam), 5, 1, 9999, TRUE, 10);
                    isMoveDistanceChanged = FALSE; // this is to avoid endless call WndProc
                }
                break;
            case 0xff & IDC_EDIT_MOVE_DELAY:
                if(HIWORD(wParam) == EN_CHANGE && !isMoveDelayChanged){
                    isMoveDelayChanged = TRUE; // this is to avoid endless call WndProc
                    Hook_Move.Move_Delay = KeepWndNumWStrInRange(
                            hwndParent, LOWORD(wParam), 5, 1, 9999, TRUE, 10);
                    isMoveDelayChanged = FALSE; // this is to avoid endless call WndProc
                }
                break;
            case 0xff & IDC_COMBOBOX_TELEPORT_PRESET: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyTeleportPreset(hwndParent);
                }
                break;
            case 0xff & IDC_COMBOBOX_TELEPORT_MAP_NAME: 
                if(HIWORD(wParam) == CBN_SELCHANGE){
                    ApplyTeleportMapID(hwndParent);
                }
                break;
            case 0xff & IDC_BUTTON_RADIO_GATE:
                SwitchTeleportModeControl(hwndTab, 0);
                SetXYDefault(hwndParent);
                break;
            case 0xff & IDC_BUTTON_RADIO_XY:
                SwitchTeleportModeControl(hwndTab, 1);
                SetGateIDDefault(hwndParent);
                break;
            // case 0xff & IDC_EDIT_TELEPORT_GATE_ID:
            // case 0xff & IDC_EDIT_TELEPORT_MAP_ID:
            // case 0xff & IDC_EDIT_TELEPORT_X:
            // case 0xff & IDC_EDIT_TELEPORT_Y:
            //     if(HIWORD(wParam) == EN_CHANGE){
            //         PresetContentChange(hwndParent);
            //     }
            //     break;
            case 0xff & IDC_BUTTON_TELEPORT:
                ApplyTeleport(hwndParent);
                break;
            }
        break;
        case 0x3:
            switch(LOWORD(wParam) & 0xff){
            case 0xff & IDC_BUTTON_OPEN_WAREHOUSE:
                OpenWarehouseTab();
                break;
            case 0xff & IDC_BUTTON_OPEN_G_WAREHOUSE:
                OpenGaintWarehouseTab();
                break;
            case 0xff & IDC_BUTTON_OPEN_CUSTOM_OUTFIT:
                OpenCustomOutfitTab();
                break;
            case 0xff & IDC_BUTTON_PAUSE_GAME:
                PauseGame();
                break;
            case 0xff & IDC_BUTTON_INFINITE_POWER:
                InfinitePower();
                break;
            case 0xff & IDC_BUTTON_COMPANION_REVIVE:
                CompanionRevive();
                break;
            case 0xff & IDC_BUTTON_EXTRA_LANDMINE:
                ExtraLandMine();
                break;
            case 0xff & IDC_BUTTON_EXTRA_LANDMINE_POWER:
                ExtraLandMinePower();
                break;
            case 0xff & IDC_BUTTON_BE_RICH:
                BeRich();
                break;
            case 0xff & IDC_BUTTON_NO_MONSTER:
                NoMonsterDisplay();
                break;
            case 0xff & IDC_BUTTON_MAGIC_LV_TO_30:
                MagicLVto30();
                break;
            case 0xff & IDC_BUTTON_CRAZY_SPEED:
                CrazySpeed();
                break;
            case 0xff & IDC_BUTTON_GOD_MODE:
                GodMode();
                break;
            case 0xff & IDC_BUTTON_EXTEND_ATK_RANGE:
                ExtendAtkRange();
                break;
            case 0xff & IDC_BUTTON_REVIVE_ENEMY:
                ReviveEneny();
                break;
            case 0xff & IDC_BUTTON_SUICIDE:
                Suicide();
                break;
            }
        break;
        case 0x4:
            switch(LOWORD(wParam) & 0xff){
            case 0xff & IDC_BUTTON_MAGIC_1:
            case 0xff & IDC_BUTTON_MAGIC_2:
            case 0xff & IDC_BUTTON_MAGIC_3:
            case 0xff & IDC_BUTTON_MAGIC_4:
            case 0xff & IDC_BUTTON_MAGIC_5:
            case 0xff & IDC_BUTTON_MAGIC_6:
            case 0xff & IDC_BUTTON_MAGIC_7:
            case 0xff & IDC_BUTTON_MAGIC_8:
            case 0xff & IDC_BUTTON_MAGIC_9:
            case 0xff & IDC_BUTTON_MAGIC_10:
            case 0xff & IDC_BUTTON_MAGIC_11:
            case 0xff & IDC_BUTTON_MAGIC_12:
            case 0xff & IDC_BUTTON_MAGIC_13:
            case 0xff & IDC_BUTTON_MAGIC_14:
            case 0xff & IDC_BUTTON_MAGIC_15:
            case 0xff & IDC_BUTTON_MAGIC_16:
            case 0xff & IDC_BUTTON_MAGIC_17:
            case 0xff & IDC_BUTTON_MAGIC_18:
            case 0xff & IDC_BUTTON_MAGIC_19:
            case 0xff & IDC_BUTTON_MAGIC_20:
            case 0xff & IDC_BUTTON_MAGIC_21:
            case 0xff & IDC_BUTTON_MAGIC_22:
                UnlockMagic(hwndParent, (LOWORD(wParam) - IDC_BUTTON_MAGIC_1) / 5);
                break;
            case 0xff & IDC_EDIT_MAGIC_LV_1:
            case 0xff & IDC_EDIT_MAGIC_LV_2:
            case 0xff & IDC_EDIT_MAGIC_LV_3:
            case 0xff & IDC_EDIT_MAGIC_LV_4:
            case 0xff & IDC_EDIT_MAGIC_LV_5:
            case 0xff & IDC_EDIT_MAGIC_LV_6:
            case 0xff & IDC_EDIT_MAGIC_LV_7:
            case 0xff & IDC_EDIT_MAGIC_LV_8:
            case 0xff & IDC_EDIT_MAGIC_LV_9:
            case 0xff & IDC_EDIT_MAGIC_LV_10:
            case 0xff & IDC_EDIT_MAGIC_LV_11:
            case 0xff & IDC_EDIT_MAGIC_LV_12:
            case 0xff & IDC_EDIT_MAGIC_LV_13:
            case 0xff & IDC_EDIT_MAGIC_LV_14:
            case 0xff & IDC_EDIT_MAGIC_LV_15:
            case 0xff & IDC_EDIT_MAGIC_LV_16:
            case 0xff & IDC_EDIT_MAGIC_LV_17:
            case 0xff & IDC_EDIT_MAGIC_LV_18:
            case 0xff & IDC_EDIT_MAGIC_LV_19:
            case 0xff & IDC_EDIT_MAGIC_LV_20:
            case 0xff & IDC_EDIT_MAGIC_LV_21:
            case 0xff & IDC_EDIT_MAGIC_LV_22:
                if(HIWORD(wParam) == EN_CHANGE && !isMagicLVChanged){
                    isMagicLVChanged = TRUE; // this is to avoid endless call WndProc
                    KeepWndNumWStrInRange(hwndParent, LOWORD(wParam), 3, 1, 20, TRUE, 10);
                    ApplyMagicLV(hwndParent, (LOWORD(wParam) - IDC_EDIT_MAGIC_LV_1) / 5);
                    isMagicLVChanged = FALSE; // this is to avoid endless call WndProc
                }
                break;
            case 0xff & IDC_EDIT_MAGIC_EXP_1:
            case 0xff & IDC_EDIT_MAGIC_EXP_2:
            case 0xff & IDC_EDIT_MAGIC_EXP_3:
            case 0xff & IDC_EDIT_MAGIC_EXP_4:
            case 0xff & IDC_EDIT_MAGIC_EXP_5:
            case 0xff & IDC_EDIT_MAGIC_EXP_6:
            case 0xff & IDC_EDIT_MAGIC_EXP_7:
            case 0xff & IDC_EDIT_MAGIC_EXP_8:
            case 0xff & IDC_EDIT_MAGIC_EXP_9:
            case 0xff & IDC_EDIT_MAGIC_EXP_10:
            case 0xff & IDC_EDIT_MAGIC_EXP_11:
            case 0xff & IDC_EDIT_MAGIC_EXP_12:
            case 0xff & IDC_EDIT_MAGIC_EXP_13:
            case 0xff & IDC_EDIT_MAGIC_EXP_14:
            case 0xff & IDC_EDIT_MAGIC_EXP_15:
            case 0xff & IDC_EDIT_MAGIC_EXP_16:
            case 0xff & IDC_EDIT_MAGIC_EXP_17:
            case 0xff & IDC_EDIT_MAGIC_EXP_18:
            case 0xff & IDC_EDIT_MAGIC_EXP_19:
            case 0xff & IDC_EDIT_MAGIC_EXP_20:
            case 0xff & IDC_EDIT_MAGIC_EXP_21:
            case 0xff & IDC_EDIT_MAGIC_EXP_22:
                ApplyMagicEXP(hwndParent, (LOWORD(wParam) - IDC_EDIT_MAGIC_EXP_1) / 5);
                break;
            
            }
        break;
        default:
        break;
        }
        break; //WM_COMMAND
    case WM_NOTIFY:
        if(((LPNMHDR)lParam)->idFrom == IDC_TABCONTROL && ((LPNMHDR)lParam)->code == TCN_SELCHANGE){
            iPageNew = TabCtrl_GetCurSel(hwndTab);
            ShowTabContents(hwndTab, iPageOld, iPageNew);
            iPageOld = iPageNew;
        }
        // if(((LPNMHDR)lParam)->idFrom==IDC_UPDOWN_LV && ((LPNMHDR)lParam)->code==UDN_DELTAPOS){
        //         NMUPDOWN* nmUpDown = (NMUPDOWN*)lParam;
        //         __int32 currentPos = nmUpDown->iPos;
        //         __int32 delta = nmUpDown->iDelta;
        //         __int32 newPos = currentPos + delta;

        //         // myprocessing...
        //         wchar_t buffer[10];
        //         wsprintf(buffer, L"%d", newPos);
        //         // SetWindowText(hEdit, buffer);
        //         MessageBoxW(NULL, buffer, L"new posi", 0);

        //         // disable default processing
        //         return 0;
        // }
        break;
    case WM_SIZE:
        if(hwndTab) {
            RECT rc;
            GetClientRect(hwnd, &rc);
            SetWindowPos(hwndTab, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER);
        }
        break;
    case WM_TRAYICON:
        if(lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN) {
            ShowWindow(hwnd, SW_SHOW);
        }
        break;
    case WM_REFRESH_DATA:
        GetAndDisplayValues(hwndParent);
        break;
    case WM_GAME_LOGOUT:
    case WM_GAME_CLOSED:
        Hack_Status.isBind_Game = FALSE;
        CloseAllExtraThread();
        SwitchBindGameControl(hwndTab, Hack_Status.isBind_Game);
        break;
    case WM_DESTROY: { /* Upon destruction, tell the main thread to stop */
        CloseAllExtraThread();
        Shell_NotifyIconW(NIM_DELETE, &nid);
        PostQuitMessage(Hack_Status.LastErrorCode);
        break;
    } 
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
        EndPaint(hwnd, &ps);
        return 0;
    }
    /* All other messages (a lot of them) are processed using default procedures */
    default:
        return DefWindowProcW(hwnd, Message, wParam, lParam);
    }
    // DeleteObject(hFontCH);
    // DeleteObject(hFontEN);
    return 0;
}

ATOM RegClass(HINSTANCE hInstance){ /* Register Window Class. A property struct of the window */
    WNDCLASSEXW wc   = {0}; 
    /* zero out the struct and set the stuff */
    memset(&wc,0,sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance     = hInstance;
    wc.lpfnWndProc   = WndProc; /* This is where we will send messages to */
    wc.lpszClassName = L"SFHelperWindowClass";
    wc.hIcon         = icon; /* APP icon */
    wc.hIconSm       = iconsm; /* icon in Windows Bar */
    return RegisterClassExW(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    SetTheme();
    SetDefaultLanguage();
    InitIcon();
    

    if(!RegClass(hInstance)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION|MB_OK);
        return 1;
    }

    CreateMenuBar();   // Generate menu

    hwnd = CreateWindowExW( /* A 'HANDLE', hence the H, or a pointer to our window */
        0,            // elective. extentional wnd style. // WS_EX_DLGMODALFRAME 
        L"SFHelperWindowClass",         // Wnd Class Name
        APP_WSTR[AWSTR_WNDNAME][Hack_Status.App_Language], // Wnd Title
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,               // Wnd Style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Wnd init posi
        400, 510,                       // Wnd init width, height
        NULL,                           // parant Wnd
        hMenuBar,                       // Menu  // SetMenu(hwnd, hMenuBar);
        hInstance,                      // instance handle
        NULL                            // No ext para while creating Wnd
    );

    
    if(hwnd == NULL){
        MessageBoxW(NULL, L"Window Creation Failed!", L"Error!", MB_ICONERROR|MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    /* This is the heart of our program where all input is processed and
       sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
       this loop will not produce unreasonably high CPU usage
    */
    MSG msg = {0}; /* A temporary location for all messages */
    while(GetMessageW(&msg, NULL, 0, 0)) { /* If no error is received... */
        TranslateMessage(&msg); /* Translate key codes to chars if present */
        DispatchMessage(&msg); /* Send it to WndProc */
    }
    return (int)msg.wParam;
}


// windres SFHelperResource.rc -o SFHelperResource.o
// gcc -o SFHelper SFHelperResource.o main.c libshlwapi.a libpsapi.a libwinpthread.dll.a -mwindows -lcomctl32 -luser32 -lgdi32 -pthread -Wall
