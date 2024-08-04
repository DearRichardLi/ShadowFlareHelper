#include <windows.h>
#include <locale.h>
#include <string.h>
#include <CommCtrl.h>

#include "SFHelperStd.h"
#include "SFHelperException.h"
#include "SFHelperWindows.h"
#include "SFHelperLanguage.h"

extern LPCWSTR APP_VERSION;

extern const Version GameVersions[SF_VERSION_COUNT];
extern Hack_Statu_Info Hack_Status;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SEX[APP_WSTR_SEX_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_PROF[APP_WSTR_PROF_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_COMP[APP_WSTR_COMP_COUNT][AVAILABLE_LANGUAGE_COUNT];

void SetTheme(void){
    // setlocale(LC_ALL, "chs"); //gbk
    // SetConsoleOutputCP(936);  //gbk
    setlocale(LC_ALL, "");       //utf8
    SetConsoleOutputCP(65001);   //utf8
    SetConsoleCP(65001);
}
void SetDefaultLanguage(void){
    LCID lcid = GetUserDefaultLCID();
    switch (lcid) {
    case 0x0004: case 0x048E: case 0x0804: case 0x1004:
        // zh-Hans zh-yue-HK, reserved  zh-CN zh-SG
        Hack_Status.App_Language = APP_LANG_CHS;
        break;
    case 0x0404: case 0x0C04: case 0x1404: case 0x7C04: 
        // zh-TW zh-HK zh-MO zh-Hant
        Hack_Status.App_Language = APP_LANG_CHT;
        break;
    default: 
        // JPN use Shift-JIS in game.
        // KOR use Euc-kr or kr??? 51949 or 949?
        Hack_Status.App_Language = APP_LANG_ENG;
        break;
    }
}
void CreateFonts_CH_EN(HFONT* hFontCH, HFONT* hFontEN){
    //Fonts. CH: 宋体; EN: Times New Roman
    LPWSTR ch = L"宋体";
    LPWSTR en = L"Times New Roman";
    int defaultHeight = 15;
    *hFontCH = CreateFontW(
            defaultHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
            DEFAULT_PITCH | FF_SWISS, ch);
    *hFontEN = CreateFontW(
            defaultHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
            DEFAULT_PITCH | FF_SWISS, en);
}
void ClearText(HWND hwnd){
    SetWindowTextW(hwnd, L"");
}
void AppendText(HWND hwnd, LPCWSTR newText, BOOL lineFeed) {
        // Get Now existing texts, connect with new texts
    int oldTextlen = GetWindowTextLengthW(hwnd);
    size_t newTextLen = wcslen(newText);
    int extLen = lineFeed == TRUE? 2 : 0;     // windows use \r\n to do line-feed, hence 2 WCHARs
    LPWSTR combinedText = (LPWSTR)malloc((oldTextlen + newTextLen + 1 + extLen)* sizeof(WCHAR));
    GetWindowTextW(hwnd, combinedText, oldTextlen + 1);
    wcscat(combinedText, newText);
    if(extLen == 2){
        LPWSTR lFeed = L"\r\n";
        wcscat(combinedText, lFeed);
    }
        // Set combined text
    SetWindowTextW(hwnd, combinedText);
    free(combinedText);

    SendMessageW(hwnd, EM_LINESCROLL, 0, SendMessageW(hwnd, EM_GETLINECOUNT, 0, 0)-1);
}
void InitIcon(void){
    extern HICON icon, iconsm;
    icon = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_ICON)); 
    iconsm = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_ICONSM)); 
}
void InitTrayBarData(HWND hwnd){
    extern NOTIFYICONDATAW nid;
    extern HICON icon;
    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hwnd;
    nid.uID = IDI_ICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = icon;
    wcscpy(nid.szTip, L"SFHelper");
    
}
void CreateMenuBar(void){
    extern HMENU hMenuBar;
    hMenuBar = CreateMenu();
    HMENU hOptionMenu = CreateMenu();
    AppendMenuW(hOptionMenu, MF_STRING, IDM_OPTION_HIDE, APP_WSTR[AWSTR_MENU_HIDE][Hack_Status.App_Language]);
    AppendMenuW(hOptionMenu, MF_STRING, IDM_OPTION_EXIT, APP_WSTR[AWSTR_MENU_EXIT][Hack_Status.App_Language]);

    HMENU hAboutMenu = CreateMenu();
    AppendMenuW(hAboutMenu, MF_STRING, IDM_ABOUT_HELP, APP_WSTR[AWSTR_MENU_HELP][Hack_Status.App_Language]);
    AppendMenuW(hAboutMenu, MF_STRING, IDM_ABOUT_ABOUTAPP, APP_WSTR[AWSTR_MENU_ABOUTAPP][Hack_Status.App_Language]);

        // Append "Option" "About" to top level menu.
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hOptionMenu, APP_WSTR[AWSTR_MENU_OPTION][Hack_Status.App_Language]);
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hAboutMenu, APP_WSTR[AWSTR_MENU_ABOUT][Hack_Status.App_Language]);
}

void CreateTabControl(HWND hwnd, LPARAM lParam){
    extern HWND hwndTab;
    hwndTab = CreateWindowExW(0, WC_TABCONTROLW, L"", 
            WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
            0, 0, 500, 400, hwnd, (HMENU)IDC_TABCONTROL, 
            ((LPCREATESTRUCTW)lParam)->hInstance, NULL);

    TCITEMW tie;
    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_INIT][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 0, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_WALLHACK][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 1, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_ASSIST][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 2, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_MAGIC][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 3, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_QUEST][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 4, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_1][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 5, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_2][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 6, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_3][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 7, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_4][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 8, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_5][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 9, (LPARAM)&tie);
    // TabCtrl_InsertItem(hwndTab, 0, &tie);
}


void CreateTab0(void){
    extern HWND hwndTab;
    extern HWND hwndButtonOpenSF, hwndComboBoxGameVersion, hwndButtonBindGame,
            hwndEditInitLog, 
            hwndStaticGameMode, hwndEditGameMode, hwndStaticOnlineRole, hwndEditOnlineRole, 
            hwndStaticPlayerName, hwndEditPlayerName, hwndButtonApplyPlayerName,
            hwndStaticLV, hwndEditLV, hwndUpDownLV, hwndStaticEXP, hwndEditEXP, hwndButtonApplyExp,
            hwndStaticSex, hwndComboBoxSex, 
            hwndStaticProf, hwndComboBoxProf, hwndStaticProfToBe, hwndComboBoxProfToBe,
            hwndStaticCompanionID, hwndComboBoxCompanionID,
            hwndStaticCompanionLV, hwndEditCompanionLV, hwndUpDownCompanionLV,
            hwndStaticCompanionEXP, hwndEditCompanionEXP, hwndButtonApplyCompanionExp,
            hwndButtonChangeLanguage;
    HWND hwndParent = GetParent(hwndTab);
    
    hwndButtonOpenSF = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_OPENSF][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 30, 80, 20, hwndParent, (HMENU)IDC_BUTTON_OPENSF,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndComboBoxGameVersion = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            110, 30, 180, 120, hwndParent, (HMENU)IDC_COMBOBOX_GAMEVERSION,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    for(int i = 0; i < SF_VERSION_COUNT; i++){
        SendMessageW(hwndComboBoxGameVersion, CB_INSERTSTRING, 
                -1, (LPARAM)GameVersions[i].Info);
    }
    hwndButtonBindGame = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_BIND_GAME][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            300, 30, 75, 20, hwndParent, (HMENU)IDC_BUTTON_BIND_GAME, 
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndEditInitLog = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | WS_VISIBLE | ES_READONLY,
            10, 60, 370, 200, hwndParent, (HMENU)IDC_EDIT_INIT_LOG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    AppendText(hwndEditInitLog, L"Version: ", FALSE);
    AppendText(hwndEditInitLog, APP_VERSION, TRUE);
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_INIT_HELP][Hack_Status.App_Language], TRUE);

    hwndStaticGameMode = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_GAMEMODE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            20, 270, 80, 20, hwndParent, (HMENU)IDC_STATIC_GAMEMODE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE), FALSE);
    hwndEditGameMode = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_READONLY | ES_CENTER, 
            110, 270, 80, 20, hwndParent, (HMENU)IDC_EDIT_GAMEMODE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE), FALSE);
    hwndStaticOnlineRole = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_ONLINEROLE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            210, 270, 80, 20, hwndParent, (HMENU)IDC_STATIC_ONLINEROLE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE), FALSE);
    hwndEditOnlineRole = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_READONLY | ES_CENTER, 
            295, 270, 80, 20, hwndParent, (HMENU)IDC_EDIT_ONLINEROLE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE), FALSE);
    
    hwndStaticPlayerName = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_PLAYER_NAME][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            20, 300, 80, 20, hwndParent, (HMENU)IDC_STATIC_PLAYER_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME), FALSE);
    hwndEditPlayerName = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER, 
            110, 300, 180, 20, hwndParent, (HMENU)IDC_EDIT_PLAYER_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME), FALSE);
    hwndButtonApplyPlayerName = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            300, 300, 75, 20, hwndParent, (HMENU)IDC_BUTTON_APPLY_PLAYER_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME), FALSE);

    hwndStaticLV = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_LV][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            5, 330, 40, 20, hwndParent, (HMENU)IDC_STATIC_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_LV), FALSE);
    hwndEditLV = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            45, 330, 50, 20, hwndParent, (HMENU)IDC_EDIT_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditLV, EM_SETLIMITTEXT, 3, 0);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_LV), FALSE);
    hwndUpDownLV = CreateWindowEx(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_LV, 
            NULL, NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_LV), FALSE);
    SendMessageW(hwndUpDownLV, UDM_SETBUDDY, (WPARAM)hwndEditLV, 0);
    SendMessageW(hwndUpDownLV, UDM_SETRANGE, 0, MAKELPARAM(100, 1)); // range 1-100
    // SendMessageW(hwndUpDownLV, UDM_SETPOS, 0, MAKELPARAM(1, 0)); // init val 1
    hwndStaticSex = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_SEX][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            100, 330, 40, 20, hwndParent, (HMENU)IDC_STATIC_SEX,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_SEX), FALSE);
    hwndComboBoxSex =  CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            140, 330, 60, 60, hwndParent, (HMENU)IDC_COMBOBOX_SEX,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), FALSE);
    for(int i = 0; i < SF_SEX_COUNT; i++){
        SendMessageW(hwndComboBoxSex, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_SEX[i][Hack_Status.App_Language]);
    }
    hwndStaticEXP = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            205, 330, 40, 20, hwndParent, (HMENU)IDC_STATIC_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_EXP), FALSE);
    hwndEditEXP = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            245, 330, 70, 20, hwndParent, (HMENU)IDC_EDIT_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditEXP, EM_SETLIMITTEXT, 9, 0);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_EXP), FALSE);
    hwndButtonApplyExp = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            315, 330, 60, 20, hwndParent, (HMENU)IDC_BUTTON_APPLY_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP), FALSE);

    hwndStaticProf = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_PROF][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            20, 360, 60, 20, hwndParent, (HMENU)IDC_STATIC_PROF,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF), FALSE);
    hwndComboBoxProf = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            90, 360, 100, 100, hwndParent, (HMENU)IDC_COMBOBOX_PROF,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), FALSE);
    SendMessageW(hwndComboBoxProf, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[5][Hack_Status.App_Language]);
    SendMessageW(hwndComboBoxProf, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[6][Hack_Status.App_Language]);
    SendMessageW(hwndComboBoxProf, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[9][Hack_Status.App_Language]);
    SendMessageW(hwndComboBoxProf, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[16][Hack_Status.App_Language]);
    hwndStaticProfToBe = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_PROF_TO_BE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            200, 360, 60, 20, hwndParent, (HMENU)IDC_STATIC_PROF_TO_BE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE), FALSE);
    hwndComboBoxProfToBe = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            270, 360, 100, 80, hwndParent, (HMENU)IDC_COMBOBOX_PROF_TO_BE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), FALSE);
    SendMessageW(hwndComboBoxProfToBe, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[5][Hack_Status.App_Language]);
    SendMessageW(hwndComboBoxProfToBe, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[6][Hack_Status.App_Language]);
    SendMessageW(hwndComboBoxProfToBe, CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[9][Hack_Status.App_Language]);
    
    hwndStaticCompanionLV = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_COMPANION_LV][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            5, 390, 60, 20, hwndParent, (HMENU)IDC_STATIC_COMPANION_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV), FALSE);
    hwndEditCompanionLV = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            65, 390, 40, 20, hwndParent, (HMENU)IDC_EDIT_COMPANION_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditCompanionLV, EM_SETLIMITTEXT, 2, 0);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV), FALSE);
    hwndUpDownCompanionLV = CreateWindowEx(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_COMPANION_LV, 
            NULL, NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV), FALSE);
    SendMessageW(hwndUpDownCompanionLV, UDM_SETBUDDY, (WPARAM)hwndEditCompanionLV, 0);
    SendMessageW(hwndUpDownCompanionLV, UDM_SETRANGE, 0, MAKELPARAM(35, 1));
    hwndStaticCompanionID = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_COMPANION_ID][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            110, 390, 50, 20, hwndParent, (HMENU)IDC_STATIC_COMPANION_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID), FALSE);
    hwndComboBoxCompanionID =  CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            160, 390, 80, 120, hwndParent, (HMENU)IDC_COMBOBOX_COMPANION_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), FALSE);
    for(int i = 0; i < SF_COMPANION_COUNT; i++){
        SendMessageW(hwndComboBoxCompanionID, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_COMP[i][Hack_Status.App_Language]);
    }


    hwndStaticCompanionEXP = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_COMPANION_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            245, 390, 55, 20, hwndParent, (HMENU)IDC_STATIC_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP), FALSE);
    hwndEditCompanionEXP = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 390, 35, 20, hwndParent, (HMENU)IDC_EDIT_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditCompanionEXP, EM_SETLIMITTEXT, 3, 0);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP), FALSE);
    hwndButtonApplyCompanionExp = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            335, 390, 40, 20, hwndParent, (HMENU)IDC_BUTTON_APPLY_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), FALSE);



    hwndButtonChangeLanguage = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_CHANGE_LANG][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            10, 430, 375, 20, hwndParent, (HMENU)IDC_BUTTON_CHANGE_LANG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
}

// shift index content
void ShowTabContents(HWND hwndTab, int iPageOld, int iPageNew){
    HWND hwndParent = GetParent(hwndTab);
    switch(iPageOld){
    case 0:
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),       SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME),           SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE),            SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE),          SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE),            SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME),         SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME),           SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME),   SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_LV),                  SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_LV),                    SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_LV),                  SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_SEX),                 SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX),               SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_EXP),                 SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_EXP),                   SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP),           SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF),                SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE),          SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE),        SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV),        SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV),          SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV),        SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID),        SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID),      SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP),       SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP),         SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), SW_HIDE);

        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_CHANGE_LANG),         SW_HIDE);
        break;
    default:
        break;
    }
    switch(iPageNew){
    case 0:
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),       SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME),           SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE),            SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE),          SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE),            SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME),         SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME),           SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME),   SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_LV),                  SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_LV),                    SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_LV),                  SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_SEX),                 SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX),               SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_EXP),                 SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_EXP),                   SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP),           SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF),                SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE),          SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE),        SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV),        SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV),          SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV),        SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID),        SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID),      SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP),       SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP),         SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), SW_SHOW);

        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_CHANGE_LANG),       SW_SHOW);
        break;
    default:
        break;
    }

        // tab 0
    }
void UseCustomFont(HWND hwndTab, HFONT hCustomFont){
    HWND hwndParent = GetParent(hwndTab);
    SendMessageW(GetDlgItem(hwndParent, IDC_TABCONTROL),                 WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),       WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME),           WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE),            WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE),          WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE),            WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME),         WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME),           WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME),   WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_LV),                  WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_LV),                    WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_UPDOWN_LV),                  WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_SEX),                 WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX),               WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_EXP),                 WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_EXP),                   WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP),           WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_PROF),                WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE),          WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE),        WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV),        WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV),          WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV),        WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID),        WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID),      WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP),       WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP),         WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), WM_SETFONT, (WPARAM)hCustomFont, TRUE);

    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_CHANGE_LANG),         WM_SETFONT, (WPARAM)hCustomFont, TRUE);
}
void SwitchOpenGameControl(HWND hwndTab, BOOL isAble){
        // Disable open game button after binding game.
        // Re-enable after the Hack need to re-bind game.
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),        isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION), isAble);
}
void ChangeLanguage(void){
    Hack_Status.App_Language = (Hack_Status.App_Language+1) % AVAILABLE_LANGUAGE_COUNT;
        
        // wnd name
    extern HWND hwnd;
    // HWND hwnd = GetForegroundWindow();
    SetWindowTextW(hwnd, APP_WSTR[AWSTR_WNDNAME][Hack_Status.App_Language]);
    
        // menu name
    extern HMENU hMenuBar;
    // HMENU hMenuBar = GetMenu(hwnd);
    HMENU hOptionMenu = GetSubMenu(hMenuBar, 0); 
    ModifyMenuW(hMenuBar, 0, MF_BYPOSITION | MF_STRING, (UINT_PTR)hOptionMenu, 
            APP_WSTR[AWSTR_MENU_OPTION][Hack_Status.App_Language]);
    ModifyMenuW(hOptionMenu, 0, MF_BYPOSITION | MF_STRING, IDM_OPTION_HIDE, 
            APP_WSTR[AWSTR_MENU_HIDE][Hack_Status.App_Language]);
    ModifyMenuW(hOptionMenu, 1, MF_BYPOSITION | MF_STRING, IDM_OPTION_EXIT, 
            APP_WSTR[AWSTR_MENU_EXIT][Hack_Status.App_Language]);

    HMENU hAboutMenu = GetSubMenu(hMenuBar, 1);
    ModifyMenuW(hMenuBar, 1, MF_BYPOSITION | MF_STRING, (UINT_PTR)hAboutMenu, 
            APP_WSTR[AWSTR_MENU_ABOUT][Hack_Status.App_Language]);
    ModifyMenuW(hAboutMenu, 0, MF_BYPOSITION | MF_STRING, IDM_ABOUT_HELP, 
            APP_WSTR[AWSTR_MENU_HELP][Hack_Status.App_Language]);
    ModifyMenuW(hAboutMenu, 1, MF_BYPOSITION | MF_STRING, IDM_ABOUT_ABOUTAPP, 
            APP_WSTR[AWSTR_MENU_ABOUTAPP][Hack_Status.App_Language]);

        // tab name
    extern HWND hwndTab;
    TCITEMW tie;
    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_INIT][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 0, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_WALLHACK][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 1, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_ASSIST][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 2, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_MAGIC][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 3, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_QUEST][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 4, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_1][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 5, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_2][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 6, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_3][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 7, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_4][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 8, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_5][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_SETITEMW, 9, (LPARAM)&tie);

    HWND hwndParent = GetParent(hwndTab);

        // log new help
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
            APP_WSTR[AWSTR_APP_INIT_HELP][Hack_Status.App_Language], TRUE);
    
        // tab 0
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_OPENSF][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_OPENSF][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_BIND_GAME][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_BIND_GAME][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_GAMEMODE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_GAMEMODE][Hack_Status.App_Language]);
    switch (Hack_Status.Game_Mode){
    case 0:
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_GAMEMODE_SINGLE][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_GAMEMODE_SINGLE][Hack_Status.App_Language]);
        break;
    case 1: case 2:
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_GAMEMODE_ONLINE][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_GAMEMODE_ONLINE][Hack_Status.App_Language]);
        break;
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_ONLINEROLE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_ONLINEROLE][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_PLAYER_NAME][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_PLAYER_NAME][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_SEX), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_SEX][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_SEX][Hack_Status.App_Language]);
    __int32 Sex = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), 
            CB_GETCURSEL, 0, 0); 
    for(int i = 0; i < SF_SEX_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), CB_DELETESTRING,
                0, 0);
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_SEX[i][Hack_Status.App_Language]);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), CB_SETCURSEL, Sex, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_EXP), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_EXP][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_EXP][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_PROF), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_PROF][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_PROF][Hack_Status.App_Language]);
    __int32 Prof = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
            CB_GETCURSEL, 0, 0); 
    for(int i = 0; i < SF_PROF_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_DELETESTRING,
                0, 0);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[5][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[6][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[9][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[16][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_SETCURSEL, Prof, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_PROF_TO_BE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_PROF_TO_BE][Hack_Status.App_Language]);
    __int32 ProfToBe = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
            CB_GETCURSEL, 0, 0); 
    for(int i = 0; i < SF_PROF_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_DELETESTRING,
                0, 0);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[5][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[6][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[9][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[16][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_SETCURSEL, ProfToBe, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_COMPANION_LV][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_COMPANION_LV][Hack_Status.App_Language]);


    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_COMPANION_ID][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_COMPANION_ID][Hack_Status.App_Language]);
    __int32 CompanionID = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), 
            CB_GETCURSEL, 0, 0); 
    for(int i = 0; i < SF_COMPANION_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), CB_DELETESTRING,
                0, 0);
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_COMP[i][Hack_Status.App_Language]);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), 
            CB_SETCURSEL, CompanionID, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_COMPANION_EXP][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_COMPANION_EXP][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language]);


            


    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_CHANGE_LANG), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_CHANGE_LANG][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_CHANGE_LANG][Hack_Status.App_Language]);
}
