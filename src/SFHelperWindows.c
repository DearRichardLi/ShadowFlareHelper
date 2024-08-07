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
    __int32 defaultHeight = 15;
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
    __int32 oldTextlen = GetWindowTextLengthW(hwnd);
    size_t newTextLen = wcslen(newText);
    __int32 extLen = lineFeed == TRUE? 2 : 0;     // windows use \r\n to do line-feed, hence 2 WCHARs
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
            hwndButtonRefresh,
            hwndStaticRefreshDelay, hwndEditRefreshDelay, hwndUpDownRefreshDelay,
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
    for(__int32 i = 0; i < SF_VERSION_COUNT; i++){
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
            15, 60, 370, 170, hwndParent, (HMENU)IDC_EDIT_INIT_LOG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    AppendText(hwndEditInitLog, L"Version: ", FALSE);
    AppendText(hwndEditInitLog, APP_VERSION, TRUE);
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_INIT_HELP][Hack_Status.App_Language], TRUE);

    hwndButtonRefresh = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_REFRESH][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 240, 185, 20, hwndParent, (HMENU)IDC_BUTTON_REFRESH, 
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticRefreshDelay = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_REFRESH_DELAY][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            200, 240, 120, 20, hwndParent, (HMENU)IDC_STATIC_REFRESH_DELAY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditRefreshDelay = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            320, 240, 55, 20, hwndParent, (HMENU)IDC_EDIT_REFRESH_DELAY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditRefreshDelay, EM_SETLIMITTEXT, 4, 0);
    hwndUpDownRefreshDelay = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_REFRESH_DELAY, 
            NULL, NULL);
    SendMessageW(hwndUpDownRefreshDelay, UDM_SETBUDDY, (WPARAM)hwndEditRefreshDelay, 0);
    SendMessageW(hwndUpDownRefreshDelay, UDM_SETRANGE, 0, MAKELPARAM(9999, 10));

    hwndStaticGameMode = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_GAMEMODE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            20, 270, 80, 20, hwndParent, (HMENU)IDC_STATIC_GAMEMODE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditGameMode = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_READONLY | ES_CENTER, 
            110, 270, 80, 20, hwndParent, (HMENU)IDC_EDIT_GAMEMODE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticOnlineRole = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_ONLINEROLE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            210, 270, 80, 20, hwndParent, (HMENU)IDC_STATIC_ONLINEROLE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditOnlineRole = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_READONLY | ES_CENTER, 
            295, 270, 80, 20, hwndParent, (HMENU)IDC_EDIT_ONLINEROLE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndStaticPlayerName = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_PLAYER_NAME][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            20, 300, 80, 20, hwndParent, (HMENU)IDC_STATIC_PLAYER_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditPlayerName = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER, 
            110, 300, 180, 20, hwndParent, (HMENU)IDC_EDIT_PLAYER_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonApplyPlayerName = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            300, 300, 75, 20, hwndParent, (HMENU)IDC_BUTTON_APPLY_PLAYER_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticLV = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_LV][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            5, 330, 40, 20, hwndParent, (HMENU)IDC_STATIC_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditLV = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            45, 330, 50, 20, hwndParent, (HMENU)IDC_EDIT_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditLV, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownLV = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_LV, 
            NULL, NULL);
    SendMessageW(hwndUpDownLV, UDM_SETBUDDY, (WPARAM)hwndEditLV, 0);
    // range 1-100
    SendMessageW(hwndUpDownLV, UDM_SETRANGE, 0, MAKELPARAM(100, 1)); 
    // init val 1
    // SendMessageW(hwndUpDownLV, UDM_SETPOS, 0, MAKELPARAM(1, 0)); 
    hwndStaticSex = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_SEX][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            100, 330, 40, 20, hwndParent, (HMENU)IDC_STATIC_SEX,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndComboBoxSex =  CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            140, 330, 60, 60, hwndParent, (HMENU)IDC_COMBOBOX_SEX,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    for(__int32 i = 0; i < SF_SEX_COUNT; i++){
        SendMessageW(hwndComboBoxSex, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_SEX[i][Hack_Status.App_Language]);
    }
    hwndStaticEXP = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            205, 330, 40, 20, hwndParent, (HMENU)IDC_STATIC_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditEXP = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            245, 330, 70, 20, hwndParent, (HMENU)IDC_EDIT_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditEXP, EM_SETLIMITTEXT, 9, 0);
    hwndButtonApplyExp = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            315, 330, 60, 20, hwndParent, (HMENU)IDC_BUTTON_APPLY_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticProf = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_PROF][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 360, 60, 20, hwndParent, (HMENU)IDC_STATIC_PROF,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndComboBoxProf = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            85, 360, 105, 100, hwndParent, (HMENU)IDC_COMBOBOX_PROF,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
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
    hwndComboBoxProfToBe = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            270, 360, 105, 80, hwndParent, (HMENU)IDC_COMBOBOX_PROF_TO_BE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
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
    hwndEditCompanionLV = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            65, 390, 40, 20, hwndParent, (HMENU)IDC_EDIT_COMPANION_LV,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditCompanionLV, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownCompanionLV = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_COMPANION_LV, 
            NULL, NULL);
    SendMessageW(hwndUpDownCompanionLV, UDM_SETBUDDY, (WPARAM)hwndEditCompanionLV, 0);
    SendMessageW(hwndUpDownCompanionLV, UDM_SETRANGE, 0, MAKELPARAM(35, 1));
    hwndStaticCompanionID = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_COMPANION_ID][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            110, 390, 50, 20, hwndParent, (HMENU)IDC_STATIC_COMPANION_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndComboBoxCompanionID =  CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            160, 390, 80, 120, hwndParent, (HMENU)IDC_COMBOBOX_COMPANION_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    for(__int32 i = 0; i < SF_COMPANION_COUNT; i++){
        SendMessageW(hwndComboBoxCompanionID, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_COMP[i][Hack_Status.App_Language]);
    }
    hwndStaticCompanionEXP = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_COMPANION_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            245, 390, 55, 20, hwndParent, (HMENU)IDC_STATIC_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditCompanionEXP = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 390, 35, 20, hwndParent, (HMENU)IDC_EDIT_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditCompanionEXP, EM_SETLIMITTEXT, 3, 0);
    hwndButtonApplyCompanionExp = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_APPLY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            335, 390, 40, 20, hwndParent, (HMENU)IDC_BUTTON_APPLY_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonChangeLanguage = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_CHANGE_LANG][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 430, 355, 20, hwndParent, (HMENU)IDC_BUTTON_CHANGE_LANG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
}
void CreateTab1(void){
    extern HWND hwndTab;
    extern HWND hwndButtonHook, hwndStaticHookStatus, hwndEditHookStatus,
            hwndEditHookLog,
            hwndStaticMapID, hwndEditMapID, 
            hwndStaticX, hwndEditX, hwndStaticY, hwndEditY, 
            hwndEditMapName,
            hwndStaticMoveDistance, hwndEditMoveDistance, hwndUpDownMoveDistance,
            hwndStaticMoveDelay, hwndEditMoveDelay, hwndUpDownMoveDelay;
    HWND hwndParent = GetParent(hwndTab);

    hwndButtonHook = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_HOOK][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 30, 180, 20, hwndParent, (HMENU)IDC_BUTTON_HOOK,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticHookStatus = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_HOOK_STATUS][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            210, 30, 80, 20, hwndParent, (HMENU)IDC_STATIC_HOOK_STATUS,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditHookStatus =  CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_READONLY, 
            300, 30, 75, 20, hwndParent, (HMENU)IDC_EDIT_HOOK_STATUS,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndEditHookLog = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | WS_VISIBLE | ES_READONLY,
            15, 60, 370, 100, hwndParent, (HMENU)IDC_EDIT_HOOK_LOG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    AppendText(hwndEditHookLog, APP_WSTR[AWSTR_APP_WALLHACK_HELP][Hack_Status.App_Language], TRUE);


    hwndStaticMapID = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAP_ID][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 170, 50, 20, hwndParent, (HMENU)IDC_STATIC_MAP_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditMapID = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER | ES_READONLY, 
            65, 170, 70, 20, hwndParent, (HMENU)IDC_EDIT_MAP_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticX = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_X][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            135, 170, 50, 20, hwndParent, (HMENU)IDC_STATIC_X,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditX = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER | ES_READONLY, 
            185, 170, 70, 20, hwndParent, (HMENU)IDC_EDIT_X,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticY = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_Y][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            255, 170, 50, 20, hwndParent, (HMENU)IDC_STATIC_Y,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditY = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER | ES_READONLY, 
            305, 170, 70, 20, hwndParent, (HMENU)IDC_EDIT_Y,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndEditMapName = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | WS_VISIBLE | ES_READONLY,
            15, 200, 370, 40, hwndParent, (HMENU)IDC_EDIT_MAP_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticMoveDistance = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MOVE_DISTANCE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            25, 250, 100, 20, hwndParent, (HMENU)IDC_STATIC_MOVE_DISTANCE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMoveDistance = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            125, 250, 70, 20, hwndParent, (HMENU)IDC_EDIT_MOVE_DISTANCE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMoveDistance, EM_SETLIMITTEXT, 4, 0);
    hwndUpDownMoveDistance = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MOVE_DISTANCE, 
            NULL, NULL);
    SendMessageW(hwndUpDownMoveDistance, UDM_SETBUDDY, (WPARAM)hwndEditMoveDistance, 0);
    SendMessageW(hwndUpDownMoveDistance, UDM_SETRANGE, 0, MAKELPARAM(9999, 1));


    hwndStaticMoveDelay = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MOVE_DELAY][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            205, 250, 100, 20, hwndParent, (HMENU)IDC_STATIC_MOVE_DELAY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMoveDelay = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            305, 250, 70, 20, hwndParent, (HMENU)IDC_EDIT_MOVE_DELAY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMoveDelay, EM_SETLIMITTEXT, 4, 0);
    hwndUpDownMoveDelay = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MOVE_DELAY, 
            NULL, NULL);
    SendMessageW(hwndUpDownMoveDelay, UDM_SETBUDDY, (WPARAM)hwndEditMoveDelay, 0);
    SendMessageW(hwndUpDownMoveDelay, UDM_SETRANGE, 0, MAKELPARAM(9999, 1));


    





}

// shift index content
void ShowTabContents(HWND hwndTab, __int32 iPageOld, __int32 iPageNew){
    HWND hwndParent = GetParent(hwndTab);
    switch(iPageOld){
    case 0:
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),       SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME),           SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_REFRESH),             SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_REFRESH_DELAY),       SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY),         SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_REFRESH_DELAY),       SW_HIDE);
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
    case 1:
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_HOOK),                SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_HOOK_STATUS),         SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS),           SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_HOOK_LOG),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_MAP_ID),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MAP_ID),                SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_X),                   SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_X),                     SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_Y),                   SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_Y),                     SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MAP_NAME),              SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DISTANCE),       SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DISTANCE),         SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MOVE_DISTANCE),       SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DELAY),          SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DELAY),            SW_HIDE);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MOVE_DELAY),          SW_HIDE);
        

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
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_REFRESH),             SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_REFRESH_DELAY),       SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY),         SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_REFRESH_DELAY),       SW_SHOW);
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
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_CHANGE_LANG),         SW_SHOW);
        break;
    case 1:
        ShowWindow(GetDlgItem(hwndParent, IDC_BUTTON_HOOK),                SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_HOOK_STATUS),         SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS),           SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_HOOK_LOG),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_MAP_ID),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MAP_ID),                SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_X),                   SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_X),                     SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_Y),                   SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_Y),                     SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MAP_NAME),              SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DISTANCE),       SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DISTANCE),         SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MOVE_DISTANCE),       SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DELAY),          SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DELAY),            SW_SHOW);
        ShowWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MOVE_DELAY),          SW_SHOW);
        
        break;
    default:
        break;
    }

    }
void UseCustomFont(HWND hwndTab, HFONT hCustomFont){
    HWND hwndParent = GetParent(hwndTab);
    // tab 0, Init
    SendMessageW(GetDlgItem(hwndParent, IDC_TABCONTROL),                 WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),       WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME),           WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_REFRESH),            WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_REFRESH_DELAY),       WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY),         WM_SETFONT, (WPARAM)hCustomFont, TRUE);
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
    // tab 1, WallHack
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_HOOK),                WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_HOOK_STATUS),         WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS),           WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_HOOK_LOG),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MAP_ID),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_MAP_ID),                WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_X),                   WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_X),                     WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_Y),                   WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_Y),                     WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_MAP_NAME),              WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DISTANCE),       WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DISTANCE),         WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DELAY),          WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DELAY),            WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    

}
void SwitchOpenGameControl(HWND hwndTab, BOOL isAble){
        // Disable open game button after binding game.
        // Re-enable after the Hack need to re-bind game.
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),             !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),      !isAble);
    // EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME),            isAble);
    // EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG),               isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_REFRESH),              isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_REFRESH_DELAY),        isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY),          isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_REFRESH_DELAY),        isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE),             isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE),               isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE),           isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE),             isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME),          isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME),            isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME),    isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_LV),                   isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_LV),                     isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_LV),                   isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_SEX),                  isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX),                isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_EXP),                  isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_EXP),                    isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP),            isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF),                 isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF),               isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE),           isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE),         isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV),         isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV),           isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV),         isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID),         isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID),       isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP),        isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP),          isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP),  isAble);
    // EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_CHANGE_LANG),          isAble);
    
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_HOOK),                 isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_HOOK_STATUS),          isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS),            isAble);
    // EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_HOOK_LOG),               isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_MAP_ID),               isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAP_ID),                 isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_X),                    isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_X),                      isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_Y),                    isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_Y),                      isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAP_ID),                 isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DISTANCE),        isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DISTANCE),          isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MOVE_DISTANCE),        isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DELAY),           isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DELAY),             isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MOVE_DELAY),           isAble);
    
}
void SwitchRefreshControl(HWND hwndTab, BOOL isAble){
        // When Refresh thread is on, disable EDIT Controls
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY),         !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_REFRESH_DELAY),       !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME),           !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME),   !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_LV),                    !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_LV),                  !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX),               !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_EXP),                   !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP),           !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF),              !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE),        !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV),          !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV),        !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID),      !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP),         !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), !isAble);
    


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

        // tab 0, Init
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_OPENSF][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_OPENSF][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_BIND_GAME), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_BIND_GAME][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_BIND_GAME][Hack_Status.App_Language]);
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
            APP_WSTR[AWSTR_APP_INIT_HELP][Hack_Status.App_Language], TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_REFRESH), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_REFRESH][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_REFRESH][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_REFRESH_DELAY), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_REFRESH_DELAY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_REFRESH_DELAY][Hack_Status.App_Language]);
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
    default:
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
    for(__int32 i = 0; i < SF_SEX_COUNT; i++){
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
    for(__int32 i = 0; i < SF_PROF_COUNT; i++){
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
    for(__int32 i = 0; i < SF_PROF_COUNT; i++){
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
    for(__int32 i = 0; i < SF_COMPANION_COUNT; i++){
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

        // tab 1, WallHack
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_HOOK), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_HOOK][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_HOOK][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_HOOK_STATUS), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_HOOK_STATUS][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_HOOK_STATUS][Hack_Status.App_Language]);
    switch (Hack_Status.isGlobal_Keyboard_Hooked){
    case 0:
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_OFF][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_OFF][Hack_Status.App_Language]);
        break;
    case 1:
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_ON][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_ON][Hack_Status.App_Language]);
        break;
    default:
        break;
    }
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_HOOK_LOG), 
            APP_WSTR[AWSTR_APP_WALLHACK_HELP][Hack_Status.App_Language], TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MAP_ID), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MAP_ID][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MAP_ID][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_X), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_X][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_X][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_Y), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_Y][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_Y][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DISTANCE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MOVE_DISTANCE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MOVE_DISTANCE][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DELAY), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MOVE_DELAY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MOVE_DELAY][Hack_Status.App_Language]);
    
    
}
