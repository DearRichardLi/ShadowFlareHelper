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


#include "SFHelperAddr.c"
#include "SFHelperException.c"
#include "SFHelperFunc.c"
#include "SFHelperLanguage.c"
#include "SFHelperStd.c"
#include "SFHelperWindows.c"



// extern LPCWSTR APP_VERSION;
// extern LPCWSTR LINE_SEPARATER;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];

Hack_Statu_Info Hack_Status = {
        APP_DEFAULT_LANGUAGE, // CHT, but auto change to locale lan (Windows sys)
        FALSE,                // Have Not Bind Game
        DEFAULT_GAME_MODE,    // 0: single; 1: ol-host; 2: ol-client; default: -1
        DEFAULT_CLIENT_INDEX, // default 0xFFFFFFFF, like in game memory
        0x0,                  // Character_Attribute pointer
        FALSE,                // No keyboard hook
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
__int32 iPageOld = 0, iPageNew = 0;
    // tab 0
HWND hwndButtonOpenSF, hwndComboBoxGameVersion, hwndButtonBindGame,
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
BOOL isLVChanged = FALSE;
BOOL CompanionisLVChanged = FALSE;
/*Init public control libs*/
// INITCOMMONCONTROLSEX icex;
// icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
// icex.dwICC = ICC_TAB_CLASSES;
// InitCommonControlsEx(&icex);

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
    // to be del
    static HWND hwndParent;
    
    switch(Message){
    case WM_CREATE: {
        CreateFonts_CH_EN(&hFontCH, &hFontEN);
        InitTrayBarData(hwnd);
        CreateTabControl(hwnd, lParam);
        
            // Create Tab Contents
        // tab 0
        CreateTab0();

            // initially show contents of tab 0
        ShowTabContents(hwndTab, -1, 0);
        UseCustomFont(hwndTab, hFontEN);
        Shell_NotifyIconW(NIM_ADD, &nid);
        return 0;
    }
    break; // WM_CREATE
    case WM_COMMAND:
        switch(LOWORD(wParam)){
        case IDM_OPTION_HIDE:
            ShowWindow(hwnd, SW_HIDE);
            break;
        case IDM_OPTION_EXIT:
            SendMessageW(hwnd, WM_DESTROY, 0, 0);
            PostQuitMessage(0);
            break;
        case IDM_ABOUT_HELP:
                // print help on log area?
            MessageBoxW(hwnd, L"Not finished.", L"No", MB_OK);
            break;
        case IDM_ABOUT_ABOUTAPP:
                // print About on MsgBox?
            MessageBoxW(hwnd, L"Not finished.", L"No", MB_OK);
            break;
        case IDC_BUTTON_OPENSF: {
            if(OpenSF() != TRUE){
                ExceptionHandler();
            }
            OpenSFLogger(hwndEditInitLog);
        }
            break;
        case IDC_COMBOBOX_GAMEVERSION: 
            if(HIWORD(wParam) == CBN_SELCHANGE){
                    // integer, from 0 to SF_VERSION_COUNT
                __int32 index = SendMessageW(hwndComboBoxGameVersion, CB_GETCURSEL, 0, 0); 
                SF_Window.SF_Version = index;
                /* // show selected item inner content
                WCHAR selectedItem[32];
                SendMessageW(hwndComboBoxGameVersion, CB_GETLBTEXT, index, (LPARAM)selectedItem);
                MessageBoxW(hwnd, selectedItem, L"选择了", MB_OK);
                swprintf_s(selectedItem, sizeof(selectedItem), L"%d", index);
                AppendText(hwndEditInitLog, selectedItem, 1);
                */
            }
            break;
        case IDC_BUTTON_BIND_GAME: 
            Hack_Status.isBind_Game = BindSF();
            if(Hack_Status.isBind_Game == TRUE){
                SwitchOpenGameControl(hwndTab, FALSE);
                ReadAndSetValues(hwndTab);
                Debug_Printer();
            } else{
                SwitchOpenGameControl(hwndTab, TRUE);
                ExceptionHandler();
            }
            BindSFLogger(hwndEditInitLog);
            break;
        case IDC_BUTTON_APPLY_PLAYER_NAME: 
            ApplyPlayerName(hwndTab);
            break;
        case IDC_EDIT_LV: 
            if(HIWORD(wParam) == EN_CHANGE && !isLVChanged){
                isLVChanged = TRUE; // this is to avoid endless call WndProc
                WCHAR buffer[4];
                GetWindowTextW(hwndEditLV, buffer, 4);
                LONG64 num = KeepNumWStrInRange(buffer, 4, 1, 100, TRUE, 10);
                SetWindowTextW(hwndEditLV, buffer);
                ApplyPlayerLV(hwndTab);
                isLVChanged = FALSE; // this is to avoid endless call WndProc
            }
            break;
        case IDC_COMBOBOX_SEX: 
            if(HIWORD(wParam) == CBN_SELCHANGE){
                ApplyPlayerSex(hwndTab);
            }
            break;
        case IDC_BUTTON_APPLY_EXP: 
            ApplyPlayerEXP(hwndTab);
            break;
        case IDC_COMBOBOX_PROF: 
            if(HIWORD(wParam) == CBN_SELCHANGE){
                ApplyPlayerProf(hwndTab);
            }
            break;
        case IDC_COMBOBOX_PROF_TO_BE: 
            if(HIWORD(wParam) == CBN_SELCHANGE){
                ApplyPlayerProfToBe(hwndTab);
            }
            break;
        case IDC_EDIT_COMPANION_LV:
            if(HIWORD(wParam) == EN_CHANGE && !CompanionisLVChanged){
                CompanionisLVChanged = TRUE; // this is to avoid endless call WndProc
                WCHAR buffer[3];
                GetWindowTextW(hwndEditCompanionLV, buffer, 3);
                LONG64 num = KeepNumWStrInRange(buffer, 3, 1, 35, TRUE, 10);
                SetWindowTextW(hwndEditCompanionLV, buffer);
                ApplyCompanionLV(hwndTab);
                CompanionisLVChanged = FALSE; // this is to avoid endless call WndProc
            }
            break;
        case IDC_COMBOBOX_COMPANION_ID: 
            if(HIWORD(wParam) == CBN_SELCHANGE){
                ApplyCompanionID(hwndTab);
            }
            break;
        case IDC_BUTTON_APPLY_COMPANION_EXP: 
            ApplyCompanionEXP(hwndTab);
            break;


        case IDC_BUTTON_CHANGE_LANG: 
            // Change Lan
            ChangeLanguage();
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
            DrawMenuBar(hwnd);
            break;

        
        }
        break; //WM_COMMAND
    case WM_NOTIFY:
        if(((LPNMHDR)lParam)->idFrom == IDC_TABCONTROL && ((LPNMHDR)lParam)->code == TCN_SELCHANGE){
            iPageNew = TabCtrl_GetCurSel(hwndTab);
            ShowTabContents(hwndTab, iPageOld, iPageNew);
            iPageOld = iPageNew;
        }
        // if(((LPNMHDR)lParam)->idFrom == IDC_UPDOWN_LV && ((LPNMHDR)lParam)->code == UDN_DELTAPOS){
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
    case WM_DESTROY: { /* Upon destruction, tell the main thread to stop */
        Shell_NotifyIconW(NIM_DELETE, &nid);
        PostQuitMessage(0);
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

ATOM RegClass(HINSTANCE hInstance){ /* Register Window Class. A properties struct of the window */
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
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU, // Wnd Style
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
// gcc -o SFHelper SFHelperResource.o main.c libshlwapi.a libpsapi.a -mwindows -lcomctl32 -luser32 -lgdi32 -Wall
