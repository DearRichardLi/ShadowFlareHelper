#include <windows.h>
#include <locale.h>
#include <string.h>
#include <CommCtrl.h>

#include "SFHelperStd.h"
#include "SFHelperException.h"
#include "SFHelperWindows.h"
#include "SFHelperLanguage.h"
#include "SFHelperResource.h"

extern LPCWSTR APP_VERSION;

extern const Version GameVersions[SF_VERSION_COUNT];
extern Hack_Statu_Info Hack_Status;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SEX[APP_WSTR_SEX_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_PROF[APP_WSTR_PROF_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_COMP[APP_WSTR_COMP_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_TELEPORT_PRESET[APP_WSTR_TELEPORT_PRESET_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SCENARIO[APP_WSTR_SCENARIO_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_MAGIC[APP_WSTR_MAGIC_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_QUEST[APP_WSTR_QUEST_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_TELEPORT_GATE[APP_WSTR_TELEPORT_GATE_COUNT][AVAILABLE_LANGUAGE_COUNT];

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
    AppendMenuW(hAboutMenu, MF_STRING, IDM_ABOUT_ADDRESS, APP_WSTR[AWSTR_MENU_ADDRESS][Hack_Status.App_Language]);

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
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_G_WAREHOUSE][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 5, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_TELEPORT_GATE][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 6, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_1][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 7, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_2][Hack_Status.App_Language];
    SendMessageW(hwndTab, TCM_INSERTITEMW, 8, (LPARAM)&tie);
    tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_STATUS_3][Hack_Status.App_Language];
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
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_SFHELPER_ADDRESS][Hack_Status.App_Language], TRUE);
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
    hwndComboBoxCompanionID = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            160, 390, 90, 120, hwndParent, (HMENU)IDC_COMBOBOX_COMPANION_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    for(__int32 i = 0; i < SF_COMPANION_COUNT; i++){
        SendMessageW(hwndComboBoxCompanionID, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_COMP[i][Hack_Status.App_Language]);
    }
    hwndStaticCompanionEXP = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_COMPANION_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            255, 390, 55, 20, hwndParent, (HMENU)IDC_STATIC_COMPANION_EXP,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditCompanionEXP = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            310, 390, 25, 20, hwndParent, (HMENU)IDC_EDIT_COMPANION_EXP,
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
            hwndStaticMapGateID, hwndEditMapGateID,
            hwndStaticMoveDistance, hwndEditMoveDistance, hwndUpDownMoveDistance,
            hwndStaticMoveDelay, hwndEditMoveDelay, hwndUpDownMoveDelay,
            hwndStaticTeleport, hwndComboBoxTeleportPreset,
            hwndStaticTeleportMapID, hwndComboBoxTeleportMapName, hwndEditTeleportMapID,
            hwndGroupBoxGateOrXY, hwndButtonRadioGate, hwndButtonRadioXY,
            hwndStaticTeleportGateID, hwndEditTeleportGateID, hwndStaticTeleportGateWarn,
            hwndStaticTeleportX, hwndEditTeleportX, hwndStaticTeleportY, hwndEditTeleportY,
            hwndButtonTeleport;
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

    hwndStaticMapGateID = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAP_GATE_ID][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 250, 50, 20, hwndParent, (HMENU)IDC_STATIC_MAP_GATE_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMapGateID = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER | ES_READONLY, 
            65, 250, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAP_GATE_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticMoveDistance = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MOVE_DISTANCE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            115, 250, 80, 20, hwndParent, (HMENU)IDC_STATIC_MOVE_DISTANCE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMoveDistance = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            195, 250, 50, 20, hwndParent, (HMENU)IDC_EDIT_MOVE_DISTANCE,
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
            245, 250, 80, 20, hwndParent, (HMENU)IDC_STATIC_MOVE_DELAY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMoveDelay = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            325, 250, 50, 20, hwndParent, (HMENU)IDC_EDIT_MOVE_DELAY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMoveDelay, EM_SETLIMITTEXT, 4, 0);
    hwndUpDownMoveDelay = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MOVE_DELAY, 
            NULL, NULL);
    SendMessageW(hwndUpDownMoveDelay, UDM_SETBUDDY, (WPARAM)hwndEditMoveDelay, 0);
    SendMessageW(hwndUpDownMoveDelay, UDM_SETRANGE, 0, MAKELPARAM(9999, 1));

    hwndStaticTeleport = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_TELEPORT][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 280, 50, 20, hwndParent, (HMENU)IDC_STATIC_TELEPORT,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndComboBoxTeleportPreset = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            65, 280, 310, 190, hwndParent, (HMENU)IDC_COMBOBOX_TELEPORT_PRESET,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    for(__int32 i = 0; i < TELEPORT_PRESET_COUNT; i++){
        SendMessageW(hwndComboBoxTeleportPreset, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_TELEPORT_PRESET[i][Hack_Status.App_Language]);
    }

    hwndStaticTeleportMapID = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_TELEPORT_MAP_ID][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 310, 50, 20, hwndParent, (HMENU)IDC_STATIC_TELEPORT_MAP_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndComboBoxTeleportMapName = CreateWindowExW(0, L"COMBOBOX", 
            NULL, 
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL,
            65, 310, 250, 160, hwndParent, (HMENU)IDC_COMBOBOX_TELEPORT_MAP_NAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    for(__int32 i = 0; i < SCENARIO_COUNT; i++){
        SendMessageW(hwndComboBoxTeleportMapName, CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_SCENARIO[i][Hack_Status.App_Language]);
    }
    hwndEditTeleportMapID = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER | ES_READONLY, 
            315, 310, 60, 20, hwndParent, (HMENU)IDC_EDIT_TELEPORT_MAP_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditTeleportMapID, EM_SETLIMITTEXT, 8, 0);

    hwndGroupBoxGateOrXY = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_GATEORXY][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            15, 340, 360, 80, hwndParent, (HMENU)IDC_GROUPBOX_GATE_OR_XY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonRadioGate = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_R_GATE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
            20, 360, 100, 20, hwndParent, (HMENU)IDC_BUTTON_RADIO_GATE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonRadioXY = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_R_XY][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
            20, 390, 100, 20, hwndParent, (HMENU)IDC_BUTTON_RADIO_XY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticTeleportGateID = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_TELEPORT_GATE_ID][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            120, 360, 50, 20, hwndParent, (HMENU)IDC_STATIC_TELEPORT_GATE_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditTeleportGateID = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            170, 360, 30, 20, hwndParent, (HMENU)IDC_EDIT_TELEPORT_GATE_ID,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticTeleportGateWarn = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_TELEPORT_GATE_WARN][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            200, 360, 170, 20, hwndParent, (HMENU)IDC_STATIC_TELEPORT_GATE_WARN,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticTeleportX = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_TELEPORT_X][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            120, 390, 50, 20, hwndParent, (HMENU)IDC_STATIC_TELEPORT_X,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditTeleportX = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            170, 390, 70, 20, hwndParent, (HMENU)IDC_EDIT_TELEPORT_X,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticTeleportY = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_TELEPORT_Y][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            240, 390, 50, 20, hwndParent, (HMENU)IDC_STATIC_TELEPORT_Y,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL); 
    hwndEditTeleportY = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            290, 390, 70, 20, hwndParent, (HMENU)IDC_EDIT_TELEPORT_Y,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonTeleport = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_TELEPORT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 430, 355, 20, hwndParent, (HMENU)IDC_BUTTON_TELEPORT,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
}

void CreateTab2(void){
    extern HWND hwndTab;
    extern HWND hwndButtonOpenWarehouse, hwndButtonOpenGiantWarehouse, 
            hwndButtonOpenCustomOutfit, hwndButtonPauseGame,
            hwndButtonInfinitePower, hwndButtonCompanionRevive,
            hwndButtonExtraLandmine, hwndButtonExtraLandminePower,
            hwndButtonBeRich, hwndButtonNoMonsterDisplay,
            hwndButtonMagicLVto30, hwndButtonCrazySpeed,
            hwndButtonGodMode, hwndButtonExtendAtkRange,
            hwndEditAssistLog,
            hwndButtonReviveEnemy,
            hwndButtonSuicide;
    HWND hwndParent = GetParent(hwndTab);
    
    hwndButtonOpenWarehouse = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_OPEN_WAREHOUSE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 30, 170, 20, hwndParent, (HMENU)IDC_BUTTON_OPEN_WAREHOUSE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonOpenGiantWarehouse = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_OPEN_G_WAREHOUSE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 30, 165, 20, hwndParent, (HMENU)IDC_BUTTON_OPEN_G_WAREHOUSE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonOpenCustomOutfit = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_OPEN_CUSTOM_OUTFIT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 70, 170, 20, hwndParent, (HMENU)IDC_BUTTON_OPEN_CUSTOM_OUTFIT,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonPauseGame = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_PAUSE_GAME][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 70, 165, 20, hwndParent, (HMENU)IDC_BUTTON_PAUSE_GAME,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonInfinitePower = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_INFINITE_POWER][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 110, 170, 20, hwndParent, (HMENU)IDC_BUTTON_INFINITE_POWER,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonCompanionRevive = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_COMP_REVIVE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 110, 165, 20, hwndParent, (HMENU)IDC_BUTTON_COMPANION_REVIVE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonExtraLandmine = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_EX_LANDMINE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 150, 170, 20, hwndParent, (HMENU)IDC_BUTTON_EXTRA_LANDMINE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonExtraLandminePower = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_EX_LANDMINE_POWER][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 150, 165, 20, hwndParent, (HMENU)IDC_BUTTON_EXTRA_LANDMINE_POWER,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonBeRich = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_BE_RICH][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 190, 170, 20, hwndParent, (HMENU)IDC_BUTTON_BE_RICH,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonNoMonsterDisplay = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_NO_MONSTER][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 190, 165, 20, hwndParent, (HMENU)IDC_BUTTON_NO_MONSTER,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonMagicLVto30 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_MAGIC_TO_30][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 230, 170, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_LV_TO_30,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonCrazySpeed = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_CRAZY_SPEED][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 230, 165, 20, hwndParent, (HMENU)IDC_BUTTON_CRAZY_SPEED,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonGodMode = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_GOD_MODE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 270, 170, 20, hwndParent, (HMENU)IDC_BUTTON_GOD_MODE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonExtendAtkRange = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_EXTEND_ATK_RANGE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            210, 270, 165, 20, hwndParent, (HMENU)IDC_BUTTON_EXTEND_ATK_RANGE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndEditAssistLog = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | WS_VISIBLE | ES_READONLY,
            15, 305, 370, 80, hwndParent, (HMENU)IDC_EDIT_ASSIST_LOG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    AppendText(hwndEditAssistLog, APP_WSTR[AWSTR_APP_HINT_ASSIST][Hack_Status.App_Language], TRUE);

    hwndButtonReviveEnemy = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_REVIVE_ENEMY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 400, 355, 20, hwndParent, (HMENU)IDC_BUTTON_REVIVE_ENEMY,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonSuicide = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_SUICIDE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 430, 355, 20, hwndParent, (HMENU)IDC_BUTTON_SUICIDE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
}
void CreateTab3(void){
    extern HWND hwndTab;
    extern HWND hwndStaticMagicName1, hwndStaticMagicLV1, hwndStaticMagicEXP1,
            hwndStaticMagicName2, hwndStaticMagicLV2, hwndStaticMagicEXP2,
            hwndGroupBoxMagicPage1,  hwndGroupBoxMagicPage2,  hwndGroupBoxMagicPage3, hwndGroupBoxMagicPage4,
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
    HWND hwndParent = GetParent(hwndTab);
    hwndStaticMagicName1 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAGIC_NAME][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 30, 95, 20, hwndParent, (HMENU)IDC_STATIC_MAGIC_NAME_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticMagicLV1 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAGIC_LV][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            110, 30, 35, 20, hwndParent, (HMENU)IDC_STATIC_MAGIC_LV_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticMagicEXP1 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAGIC_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            145, 30, 45, 20, hwndParent, (HMENU)IDC_STATIC_MAGIC_EXP_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticMagicName2 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAGIC_NAME][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            205, 30, 95, 20, hwndParent, (HMENU)IDC_STATIC_MAGIC_NAME_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticMagicLV2 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAGIC_LV][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            300, 30, 35, 20, hwndParent, (HMENU)IDC_STATIC_MAGIC_LV_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticMagicEXP2 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_MAGIC_EXP][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            335, 30, 45, 20, hwndParent, (HMENU)IDC_STATIC_MAGIC_EXP_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndGroupBoxMagicPage1 = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_1][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            10, 50, 185, 200, hwndParent, (HMENU)IDC_GROUPBOX_MAGIC_PAGE_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndGroupBoxMagicPage2 = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_2][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            200, 50, 185, 200, hwndParent, (HMENU)IDC_GROUPBOX_MAGIC_PAGE_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndGroupBoxMagicPage3 = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_3][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            10, 250, 185, 200, hwndParent, (HMENU)IDC_GROUPBOX_MAGIC_PAGE_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndGroupBoxMagicPage4 = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_4][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            200, 250, 185, 200, hwndParent, (HMENU)IDC_GROUPBOX_MAGIC_PAGE_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonMagic1 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_TRANSPORT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 70, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV1 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 70, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV1, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV1 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_1, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV1, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV1, 0);
    SendMessageW(hwndUpDownMagicLV1, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP1 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 70, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP1, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP1 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_1, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP1, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP1, 0);
    SendMessageW(hwndUpDownMagicEXP1, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic2 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_FIRE_BALL][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 100, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV2 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 100, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV2, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV2 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_2, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV2, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV2, 0);
    SendMessageW(hwndUpDownMagicLV2, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP2 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 100, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP2, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP2 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_2, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP2, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP2, 0);
    SendMessageW(hwndUpDownMagicEXP2, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic3 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_ICE_BOLT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 130, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV3 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 130, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV3, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV3 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_3, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV3, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV3, 0);
    SendMessageW(hwndUpDownMagicLV3, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP3 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 130, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP3, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP3 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_3, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP3, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP3, 0);
    SendMessageW(hwndUpDownMagicEXP3, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic4 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_PLASMA][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 160, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV4 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 160, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV4, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV4 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_4, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV4, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV4, 0);
    SendMessageW(hwndUpDownMagicLV4, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP4 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 160, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP4, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP4 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_4, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP4, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP4, 0);
    SendMessageW(hwndUpDownMagicEXP4, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic5 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_HELL_FIRE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 190, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_5,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV5 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 190, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_5,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV5, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV5 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_5, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV5, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV5, 0);
    SendMessageW(hwndUpDownMagicLV5, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP5 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 190, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_5,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP5, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP5 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_5, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP5, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP5, 0);
    SendMessageW(hwndUpDownMagicEXP5, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic6 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_ICE_BLAST][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 220, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_6,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV6 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 220, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_6,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV6, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV6 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_6, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV6, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV6, 0);
    SendMessageW(hwndUpDownMagicLV6, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP6 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 220, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_6,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP6, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP6 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_6, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP6, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP6, 0);
    SendMessageW(hwndUpDownMagicEXP6, UDM_SETRANGE, 0, MAKELPARAM(999, 0));

    hwndButtonMagic7 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_HEAL][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 70, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_7,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV7 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 70, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_7,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV7, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV7 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_7, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV7, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV7, 0);
    SendMessageW(hwndUpDownMagicLV7, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP7 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 70, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_7,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP7, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP7 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_7, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP7, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP7, 0);
    SendMessageW(hwndUpDownMagicEXP7, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic8 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_MOON][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 100, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_8,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV8 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 100, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_8,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV8, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV8 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_8, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV8, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV8, 0);
    SendMessageW(hwndUpDownMagicLV8, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP8 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 100, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_8,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP8, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP8 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_8, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP8, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP8, 0);
    SendMessageW(hwndUpDownMagicEXP8, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic9 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_BERSERKER][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 130, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_9,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV9 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 130, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_9,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV9, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV9 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_9, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV9, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV9, 0);
    SendMessageW(hwndUpDownMagicLV9, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP9 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 130, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_9,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP9, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP9 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_9, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP9, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP9, 0);
    SendMessageW(hwndUpDownMagicEXP9, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic10 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_ENERGY_SHIELD][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 160, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_10,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV10 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 160, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_10,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV10, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV10 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_10, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV10, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV10, 0);
    SendMessageW(hwndUpDownMagicLV10, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP10 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 160, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_10,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP10, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP10 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_10, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP10, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP10, 0);
    SendMessageW(hwndUpDownMagicEXP10, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic11 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_EARTH_SPEAR][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 190, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_11,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV11 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 190, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_11,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV11, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV11 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_11, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV11, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV11, 0);
    SendMessageW(hwndUpDownMagicLV11, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP11 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 190, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_11,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP11, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP11 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_11, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP11, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP11, 0);
    SendMessageW(hwndUpDownMagicEXP11, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic12 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_FLAME_STRIKE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 220, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_12,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV12 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 220, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_12,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV12, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV12 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_12, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV12, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV12, 0);
    SendMessageW(hwndUpDownMagicLV12, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP12 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 220, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_12,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP6, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP12 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_12, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP12, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP12, 0);
    SendMessageW(hwndUpDownMagicEXP12, UDM_SETRANGE, 0, MAKELPARAM(999, 0));

    hwndButtonMagic13 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_DREAD_DEATHSCYTHE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 270, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_13,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV13 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 270, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_13,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV13, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV13 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_13, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV13, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV13, 0);
    SendMessageW(hwndUpDownMagicLV13, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP13 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 270, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_13,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP13, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP13 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_13, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP13, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP13, 0);
    SendMessageW(hwndUpDownMagicEXP13, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic14 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_LIGHTNING_STORM][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 300, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_14,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV14 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 300, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_14,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV14, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV14 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_14, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV14, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV14, 0);
    SendMessageW(hwndUpDownMagicLV14, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP14 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 300, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_14,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP14, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP14 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_14, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP14, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP14, 0);
    SendMessageW(hwndUpDownMagicEXP14, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic15 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_MEDUSA][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 330, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_15,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV15 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 330, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_15,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV15, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV15 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_15, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV15, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV15, 0);
    SendMessageW(hwndUpDownMagicLV15, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP15 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 330, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_15,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP15, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP15 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_15, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP15, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP15, 0);
    SendMessageW(hwndUpDownMagicEXP15, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic16 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_SONIC_BLADE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 360, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_16,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV16 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 360, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_16,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV16, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV16 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_16, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV16, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV16, 0);
    SendMessageW(hwndUpDownMagicLV16, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP16 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 360, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_16,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP16, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP16 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_16, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP16, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP16, 0);
    SendMessageW(hwndUpDownMagicEXP16, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic17 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_MUD_JAVELIN][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 390, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_17,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV17 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 390, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_17,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV17, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV17 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_17, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV17, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV17, 0);
    SendMessageW(hwndUpDownMagicLV17, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP17 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 390, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_17,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP17, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP17 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_17, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP17, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP17, 0);
    SendMessageW(hwndUpDownMagicEXP17, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic18 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_IDENTIFY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 420, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_18,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV18 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            110, 420, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_18,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV18, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV18 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_18, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV18, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV18, 0);
    SendMessageW(hwndUpDownMagicLV18, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP18 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            145, 420, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_18,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP18, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP18 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_18, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP18, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP18, 0);
    SendMessageW(hwndUpDownMagicEXP18, UDM_SETRANGE, 0, MAKELPARAM(999, 0));

    hwndButtonMagic19 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_MAGIC_SHIELD][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 270, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_19,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV19 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 270, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_19,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV19, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV19 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_19, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV19, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV19, 0);
    SendMessageW(hwndUpDownMagicLV19, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP19 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 270, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_19,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP19, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP19 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_19, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP19, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP19, 0);
    SendMessageW(hwndUpDownMagicEXP19, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic20 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_COUNTER_BURST][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 300, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_20,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV20 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 300, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_20,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV20, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV20 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_20, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV20, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV20, 0);
    SendMessageW(hwndUpDownMagicLV20, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP20 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 300, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_20,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP20, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP20 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_20, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP20, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP20, 0);
    SendMessageW(hwndUpDownMagicEXP20, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic21 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_EXPLOSION][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 330, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_21,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV21 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 330, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_21,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV21, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV21 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_21, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV21, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV21, 0);
    SendMessageW(hwndUpDownMagicLV21, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP21 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 330, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_21,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP21, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP21 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_21, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP21, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP21, 0);
    SendMessageW(hwndUpDownMagicEXP21, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
    hwndButtonMagic22 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_MAGIC[AWSTR_MAGIC_ELEMENTAL_STRIKE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 360, 95, 20, hwndParent, (HMENU)IDC_BUTTON_MAGIC_22,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditMagicLV22 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 360, 35, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_LV_22,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicLV22, EM_SETLIMITTEXT, 2, 0);
    hwndUpDownMagicLV22 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_LV_22, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicLV22, UDM_SETBUDDY, (WPARAM)hwndEditMagicLV22, 0);
    SendMessageW(hwndUpDownMagicLV22, UDM_SETRANGE, 0, MAKELPARAM(20, 1));
    hwndEditMagicEXP22 = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            335, 360, 45, 20, hwndParent, (HMENU)IDC_EDIT_MAGIC_EXP_22,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditMagicEXP22, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownMagicEXP22 = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_MAGIC_EXP_22, 
            NULL, NULL);
    SendMessageW(hwndUpDownMagicEXP22, UDM_SETBUDDY, (WPARAM)hwndEditMagicEXP22, 0);
    SendMessageW(hwndUpDownMagicEXP22, UDM_SETRANGE, 0, MAKELPARAM(999, 0));
}
void CreateTab4(void){
    extern HWND hwndTab;
    extern HWND hwndStaticQuestCol1, hwndStaticQuestCol2, hwndStaticQuestCol3, hwndStaticQuestCol4,
            hwndGroupBoxQuestPage1,  hwndGroupBoxQuestPage2,
            hwndButtonQuest1,  hwndButtonQuest2,  hwndButtonQuest3,  hwndButtonQuest4,
            hwndButtonQuest5,  hwndButtonQuest6,  hwndButtonQuest7,  hwndButtonQuest8,
            hwndButtonQuest9,  hwndButtonQuest10, hwndButtonQuest11, hwndButtonQuest12,
            hwndButtonQuest13, hwndButtonQuest14, hwndButtonQuest15, hwndButtonQuest16,
            hwndButtonQuest17, hwndButtonQuest18, hwndButtonQuest19, hwndButtonQuest20,
            hwndButtonQuest21, hwndButtonQuest22, hwndButtonQuest23, hwndButtonQuest24,
            hwndButtonQuest25, hwndButtonQuest26, hwndButtonQuest27, hwndButtonQuest28,
            hwndButtonQuest29, hwndButtonQuest30, hwndButtonQuest31, hwndButtonQuest32,
            hwndButtonQuest33, hwndButtonQuest34, hwndButtonQuest35, hwndButtonQuest36,
            hwndButtonQuest37, hwndButtonQuest38, hwndButtonQuest39, hwndButtonQuest40,
            hwndButtonQuest41, hwndButtonQuest42, hwndButtonQuest43, hwndButtonQuest44,
            hwndButtonQuest45, hwndButtonQuest46, hwndButtonQuest47, hwndButtonQuest48;
    HWND hwndParent = GetParent(hwndTab);
    
    hwndStaticQuestCol1 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_QUEST_COL_1][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            15, 30, 85, 20, hwndParent, (HMENU)IDC_STATIC_QUEST_COL_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticQuestCol2 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_QUEST_COL_2][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            105, 30, 85, 20, hwndParent, (HMENU)IDC_STATIC_QUEST_COL_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticQuestCol3 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_QUEST_COL_3][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            205, 30, 85, 20, hwndParent, (HMENU)IDC_STATIC_QUEST_COL_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndStaticQuestCol4 = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_QUEST_COL_4][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            295, 30, 85, 20, hwndParent, (HMENU)IDC_STATIC_QUEST_COL_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndGroupBoxQuestPage1 = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_QUEST_PAGE_1][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            10, 50, 185, 400, hwndParent, (HMENU)IDC_GROUPBOX_QUEST_PAGE_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndGroupBoxQuestPage2 = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_QUEST_PAGE_2][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            200, 50, 185, 400, hwndParent, (HMENU)IDC_GROUPBOX_QUEST_PAGE_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonQuest1 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_DEFEAT_THE_RED_GOBLIN][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 70, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest2 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_TAKE_BACK_MALSES_GEM][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 100, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest3 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_TAKE_BACK_SYRIAS_SPIRIT_STONE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 130, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest4 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SWEEP_THE_MONSTERS_IN_THE_DUSTY_RUINS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 160, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest5 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_TAKE_BACK_ROSANNAS_MEMORABLE_RUBY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 190, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_5,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest6 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_ERRAND_FOR_GEDO][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 220, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_6,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest7 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SWEEP_THE_MONSTERS_IN_THE_COLD_RUINS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 270, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_7,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest8 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SCOUT_THE_PURGATORY_OF_JUDGMENTS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 300, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_8,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest9 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SCOUT_THE_REMAINS_OF_REINCARNATION][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 330, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_9,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest10 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SCOUT_THE_CONTINUING_LAND][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 360, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_10,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest11 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SCOUT_THE_IMMORTAL_REMAINS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 390, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_11,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest12 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_DESTROY_THIEVES_STAYING_SE_OF_KANFORE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            15, 420, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_12,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonQuest13 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_HEAD_FOR_THE_MINING_TUNNEL_OF_YUGUNOS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 70, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_13,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest14 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_MEET_WITH_THE_WIZARD_KIRUSHUTAT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 100, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_14,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest15 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_TAKE_BACK_THE_SEAL_CRYSTAL][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 130, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_15,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest16 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_RETAKE_THE_SECURITY_CONTROL_FACILITY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 160, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_16,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest17 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_RECAPTURE_THE_POWER_SUPPLY_FACILITY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 190, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_17,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest18 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_DEFEAT_THE_DRAGONS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 220, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_18,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest19 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_KILL_THE_TARANTULAS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 270, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_19,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest20 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SEARCH_DEVALIOS_HIDDEN_WAREHOUSE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 300, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_20,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest21 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SWEEP_VICINITY_OF_S_CAMP_OF_YUGUNOS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 330, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_21,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest22 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_THE_SACRED_RELIC_SACRED_WING][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 360, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_22,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest23 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_THE_SACRED_RELIC_ANGELS_HAIR][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 390, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_23,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest24 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_DELIVER_THE_BISHOP_BERINIS_REPORT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            105, 420, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_24,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonQuest25 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_EXPLORE_THE_REMAINS_OF_HEARTBEAT][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 70, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_25,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest26 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_EXAMINE_THE_PLUMBING][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 100, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_26,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest27 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_TRUTH_BEHIND_DEATH_OF_THE_ELF_RANGERS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 130, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_27,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest28 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_MEET_WITH_SAINT_KNIGHT_LICARN][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 160, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_28,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest29 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_BREAK_THROUGH_THE_TOWER_OF_LICARN][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 190, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_29,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest30 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_THE_SACRED_RELIC_ANGELS_NAIL][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 220, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_30,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest31 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_RESEARCH_THE_ANCIENT_RUINS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 270, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_31,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest32 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_AN_ANTIDOTE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 300, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_32,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest33 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_PUNITIVE_EXPEDITION_AGAINST_JURG][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 330, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_33,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest34 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_ERRANDS_FOR_MRS_MORRIS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 360, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_34,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest35 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_TAKE_BACK_THE_STOLEN_TEARS_OF_OBERON][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 390, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_35,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest36 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_FIND_THE_ANCIENT_SHORT_SWORD][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            205, 420, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_36,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndButtonQuest37 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_THE_SACRED_RELIC_ANGELS_MEMORY][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 70, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_37,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest38 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_DELIVER_THE_SACRED_RELICS_TO_ST_SENA][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 100, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_38,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest39 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_THE_BLUE_AND_GREEN_ORBS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 130, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_39,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest40 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_FIND_MR_MRS_JURGS_REMEMBRANCE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 160, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_40,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest41 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GET_THE_RED_ORB][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 190, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_41,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest42 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_RECAPTURE_THE_RUINS_OF_EXORCISM][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 220, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_42,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest43 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_HEAD_FOR_GOLIATES_MANSION][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 270, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_43,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest44 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_BEAT_THE_DEVIL_DIGNOSIS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 300, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_44,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest45 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_A_WISE_MAN_IN_RUINS_OF_THE_WISE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 330, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_45,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest46 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_LET_THE_JURG_PARTY_SURRENDER][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 360, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_46,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest47 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_SUBJECTION_OF_THE_FORT_OF_DEMONS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 390, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_47,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonQuest48 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR_QUEST[AWSTR_QUEST_GO_TO_THE_FOREST_OF_MADNESS][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            295, 420, 85, 20, hwndParent, (HMENU)IDC_BUTTON_QUEST_48,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
}
void CreateTab5(void){
    extern HWND hwndTab;
    extern HWND hwndButtonOpenGiantWarehouse2, 
            hwndGroupBoxGiantWarehouse,
            hwndButtonGiantWarehouse1, hwndButtonGiantWarehouse2,
            hwndButtonGiantWarehouse3, hwndButtonGiantWarehouse4,
            hwndButtonGiantWarehouse5, hwndButtonGiantWarehouse6,
            hwndButtonGiantWarehouse7, hwndButtonGiantWarehouse8,
            hwndButtonGiantWarehouse9, hwndButtonGiantWarehouse10,
            hwndStaticGiantWarehouseIndex,
            hwndEditGiantWarehouseIndex, hwndUpDownGiantWarehouseIndex,
            hwndEditGiantWarehouseLog;
    HWND hwndParent = GetParent(hwndTab);
    hwndButtonOpenGiantWarehouse2 = CreateWindowExW(0, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_B_OPEN_G_WAREHOUSE][Hack_Status.App_Language], 
            WS_CHILD | WS_VISIBLE,
            20, 30, 355, 20, hwndParent, (HMENU)IDC_BUTTON_OPEN_G_WAREHOUSE_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndGroupBoxGiantWarehouse = CreateWindowExW(WS_EX_CONTROLPARENT, L"BUTTON", 
            APP_WSTR[AWSTR_CTL_G_G_WAREHOUSE][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            10, 50, 375, 50, hwndParent, (HMENU)IDC_GROUPBOX_G_WAREHOUSE,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    
    hwndButtonGiantWarehouse1 = CreateWindowExW(0, L"BUTTON", 
            L"1", 
            WS_CHILD | WS_VISIBLE,
            30, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_1,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse2 = CreateWindowExW(0, L"BUTTON", 
            L"2", 
            WS_CHILD | WS_VISIBLE,
            65, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_2,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse3 = CreateWindowExW(0, L"BUTTON", 
            L"3", 
            WS_CHILD | WS_VISIBLE,
            100, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_3,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse4 = CreateWindowExW(0, L"BUTTON", 
            L"4", 
            WS_CHILD | WS_VISIBLE,
            135, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_4,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse5 = CreateWindowExW(0, L"BUTTON", 
            L"5", 
            WS_CHILD | WS_VISIBLE,
            170, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_5,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse6 = CreateWindowExW(0, L"BUTTON", 
            L"6", 
            WS_CHILD | WS_VISIBLE,
            205, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_6,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse7 = CreateWindowExW(0, L"BUTTON", 
            L"7", 
            WS_CHILD | WS_VISIBLE,
            240, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_7,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse8 = CreateWindowExW(0, L"BUTTON", 
            L"8", 
            WS_CHILD | WS_VISIBLE,
            275, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_8,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse9 = CreateWindowExW(0, L"BUTTON", 
            L"9", 
            WS_CHILD | WS_VISIBLE,
            310, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_9,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndButtonGiantWarehouse10 = CreateWindowExW(0, L"BUTTON", 
            L"10", 
            WS_CHILD | WS_VISIBLE,
            345, 70, 25, 20, hwndParent, (HMENU)IDC_BUTTON_G_WAREHOUSE_10,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);

    hwndStaticGiantWarehouseIndex = CreateWindowExW(0, L"STATIC", 
            APP_WSTR[AWSTR_CTL_S_G_WAREHOUSE_INDEX][Hack_Status.App_Language], 
            WS_VISIBLE | WS_CHILD | ES_CENTER,
            20, 110, 280, 20, hwndParent, (HMENU)IDC_STATIC_G_WAREHOUSE_INDEX,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    hwndEditGiantWarehouseIndex = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | WS_VISIBLE | ES_CENTER | ES_NUMBER, 
            300, 110, 75, 20, hwndParent, (HMENU)IDC_EDIT_G_WAREHOUSE_INDEX,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    SendMessageW(hwndEditGiantWarehouseIndex, EM_SETLIMITTEXT, 3, 0);
    hwndUpDownGiantWarehouseIndex = CreateWindowExW(0, UPDOWN_CLASSW, 
            NULL,
            WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ALIGNRIGHT,
            0, 0, 0, 0, hwndParent, (HMENU)IDC_UPDOWN_G_WAREHOUSE_INDEX, 
            NULL, NULL);
    SendMessageW(hwndUpDownGiantWarehouseIndex, UDM_SETBUDDY, (WPARAM)hwndEditGiantWarehouseIndex, 0);
    SendMessageW(hwndUpDownGiantWarehouseIndex, UDM_SETRANGE, 0, MAKELPARAM(479, 0));

    hwndEditGiantWarehouseLog = CreateWindowExW(0, L"EDIT", 
            L"", 
            WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | WS_VISIBLE | ES_READONLY,
            15, 140, 370, 160, hwndParent, (HMENU)IDC_EDIT_G_WAREHOUSE_LOG,
            (HINSTANCE)GetWindowLongPtrW(hwndTab, GWLP_HINSTANCE), NULL);
    AppendText(hwndEditGiantWarehouseLog, APP_WSTR[AWSTR_APP_HINT_G_WAREHOUSE][Hack_Status.App_Language], TRUE);

}
// shift index content
void ShowTabContents(HWND hwndTab, __int32 iPageOld, __int32 iPageNew){
    HWND hwndParent = GetParent(hwndTab);
    switch(iPageOld){
    case 0:
        for(__int32 i = IDC_BUTTON_OPENSF; i <= IDC_BUTTON_CHANGE_LANG; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_HIDE);
        }
        break;
    case 1:
        for(__int32 i = IDC_BUTTON_HOOK; i <= IDC_BUTTON_TELEPORT; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_HIDE);
        }
        break;
    case 2:
        for(__int32 i = IDC_BUTTON_OPEN_WAREHOUSE; i <= IDC_BUTTON_SUICIDE; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_HIDE);
        }
        break;
    case 3:
        for(__int32 i = IDC_STATIC_MAGIC_NAME_1; i <= IDC_UPDOWN_MAGIC_EXP_22; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_HIDE);
        }
        break;
    case 4:
        for(__int32 i = IDC_STATIC_QUEST_COL_1; i <= IDC_BUTTON_QUEST_48; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_HIDE);
        }
        break;
    case 5:
        for(__int32 i = IDC_BUTTON_OPEN_G_WAREHOUSE_2; i <= IDC_EDIT_G_WAREHOUSE_LOG; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_HIDE);
        }
        break;
    default:
        break;
    }
    switch(iPageNew){
    case 0:
        for(__int32 i = IDC_BUTTON_OPENSF; i <= IDC_BUTTON_CHANGE_LANG; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_SHOW);
        }
        break;
    case 1:
        for(__int32 i = IDC_BUTTON_HOOK; i <= IDC_BUTTON_TELEPORT; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_SHOW);
        }
        break;
    case 2:
        for(__int32 i = IDC_BUTTON_OPEN_WAREHOUSE; i <= IDC_BUTTON_SUICIDE; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_SHOW);
        }
        break;
    case 3:
        for(__int32 i = IDC_STATIC_MAGIC_NAME_1; i <= IDC_UPDOWN_MAGIC_EXP_22; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_SHOW);
        }
        break;
    case 4:
        for(__int32 i = IDC_STATIC_QUEST_COL_1; i <= IDC_BUTTON_QUEST_48; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_SHOW);
        }
        break;
    case 5:
        for(__int32 i = IDC_BUTTON_OPEN_G_WAREHOUSE_2; i <= IDC_EDIT_G_WAREHOUSE_LOG; i++){
            ShowWindow(GetDlgItem(hwndParent, i), SW_SHOW);
        }
        break;
    default:
        break;
    }

    }
void UseCustomFont(HWND hwndTab, HFONT hCustomFont){
    HWND hwndParent = GetParent(hwndTab);
    // tab 0, Init
    for(__int32 i = IDC_TABCONTROL; i <= IDC_BUTTON_CHANGE_LANG; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    }
    // tab 1, WallHack
    for(__int32 i = IDC_BUTTON_HOOK; i <= IDC_BUTTON_TELEPORT; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    }
    // tab 2, Assist
    for(__int32 i = IDC_BUTTON_OPEN_WAREHOUSE; i <= IDC_BUTTON_SUICIDE; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    }
    // tab 3, Magic
    for(__int32 i = IDC_STATIC_MAGIC_NAME_1; i <= IDC_UPDOWN_MAGIC_EXP_22; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    }
    // tab 4, Quest
    for(__int32 i = IDC_STATIC_QUEST_COL_1; i <= IDC_BUTTON_QUEST_48; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    }
    // tab 5, G Warehouse
    for(__int32 i = IDC_BUTTON_OPEN_G_WAREHOUSE_2; i <= IDC_EDIT_G_WAREHOUSE_LOG; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETFONT, (WPARAM)hCustomFont, TRUE);
    }

}
void SwitchBindGameControl(HWND hwndTab, BOOL isAble){
        // Disable open game button after binding game.
        // Re-enable after the Hack need to re-bind game.
    HWND hwndParent = GetParent(hwndTab);
    // tab 0, Init
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_OPENSF),              !isAble);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION),       !isAble);
    for(__int32 i = IDC_BUTTON_REFRESH; i <= IDC_BUTTON_APPLY_COMPANION_EXP; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }
    // tab 1, WallHack
    for(__int32 i = IDC_BUTTON_HOOK; i <= IDC_EDIT_HOOK_STATUS; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }
    for(__int32 i = IDC_STATIC_MAP_ID; i <= IDC_BUTTON_TELEPORT; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }
    // tab 2, Assist
    for(__int32 i = IDC_BUTTON_OPEN_WAREHOUSE; i <= IDC_BUTTON_SUICIDE; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }
    // tab 3, Magic
    if(isAble == FALSE){
        for(__int32 i = 0; i < SF_MAGIC_COUNT * 5; i++){
            EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_MAGIC_1 + i),  isAble);
        }
    }
    // tab 4, Quest
    for(__int32 i = IDC_BUTTON_QUEST_1; i <= IDC_BUTTON_QUEST_48; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }
    // tab 5, G Warehouse
    for(__int32 i = IDC_BUTTON_OPEN_G_WAREHOUSE_2; i <= IDC_EDIT_G_WAREHOUSE_LOG; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }

}
void SwitchRefreshControl(HWND hwndTab, BOOL isAble){
        // When Refresh thread is on, disable EDIT Controls
    HWND hwndParent = GetParent(hwndTab);
    for(__int32 i = IDC_EDIT_REFRESH_DELAY; i <= IDC_BUTTON_APPLY_COMPANION_EXP; i++){
        EnableWindow(GetDlgItem(hwndParent, i), !isAble);
    }
}
void SwitchTeleportModeControl(HWND hwndTab, BOOL isAble){
        // When change teleport mode, switch control disables.
    HWND hwndParent = GetParent(hwndTab);
    for(__int32 i = IDC_STATIC_TELEPORT_GATE_ID; i <= IDC_STATIC_TELEPORT_GATE_WARN; i++){
        EnableWindow(GetDlgItem(hwndParent, i), !isAble);
    }
    for(__int32 i = IDC_STATIC_TELEPORT_X; i <= IDC_EDIT_TELEPORT_Y; i++){
        EnableWindow(GetDlgItem(hwndParent, i), isAble);
    }    
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
    ModifyMenuW(hAboutMenu, 2, MF_BYPOSITION | MF_STRING, IDM_ABOUT_ADDRESS, 
            APP_WSTR[AWSTR_MENU_ADDRESS][Hack_Status.App_Language]);

        // tab name
    extern HWND hwndTab;
    TCITEMW tie;
    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    for(__int32 i = 0; i <= 9; i++){
        tie.pszText = (LPWSTR)APP_WSTR[AWSTR_TAB_INIT + i][Hack_Status.App_Language];
        SendMessageW(hwndTab, TCM_SETITEMW, i, (LPARAM)&tie);
    }

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
            -1, (LPARAM)APP_WSTR_PROF[P_C_HUNTER][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[P_C_SWORDMAN][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[P_C_WITCH][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[P_C_MERCENARY][Hack_Status.App_Language]);
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
            -1, (LPARAM)APP_WSTR_PROF[P_C_HUNTER][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[P_C_SWORDMAN][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), CB_INSERTSTRING, 
            -1, (LPARAM)APP_WSTR_PROF[P_C_WITCH][Hack_Status.App_Language]);
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
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MAP_GATE_ID), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MAP_GATE_ID][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MAP_GATE_ID][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DISTANCE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MOVE_DISTANCE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MOVE_DISTANCE][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MOVE_DELAY), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MOVE_DELAY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MOVE_DELAY][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_TELEPORT), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_TELEPORT][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_TELEPORT][Hack_Status.App_Language]);
    __int32 PresetIndex = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), 
            CB_GETCURSEL, 0, 0);
    for(__int32 i = 0; i < TELEPORT_PRESET_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), CB_DELETESTRING,
                0, 0);
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_TELEPORT_PRESET[i][Hack_Status.App_Language]);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), 
            CB_SETCURSEL, PresetIndex, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_TELEPORT_MAP_ID), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_TELEPORT_MAP_ID][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_TELEPORT_MAP_ID][Hack_Status.App_Language]);
    __int32 MapIndex = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), 
            CB_GETCURSEL, 0, 0); 
    for(__int32 i = 0; i < SCENARIO_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), CB_DELETESTRING,
                0, 0);
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), CB_INSERTSTRING, 
                -1, (LPARAM)APP_WSTR_SCENARIO[i][Hack_Status.App_Language]);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), 
            CB_SETCURSEL, MapIndex, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_GROUPBOX_GATE_OR_XY), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_G_GATEORXY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_G_GATEORXY][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_GATE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_R_GATE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_R_GATE][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_XY), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_R_XY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_R_XY][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_TELEPORT_GATE_ID), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_TELEPORT_GATE_ID][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_TELEPORT_GATE_ID][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_TELEPORT_GATE_WARN), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_TELEPORT_GATE_WARN][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_TELEPORT_GATE_WARN][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_TELEPORT), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_TELEPORT][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_TELEPORT][Hack_Status.App_Language]);
    
        // tab 2, Assist
    for(__int32 i = 0; i <= 0xD; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_OPEN_WAREHOUSE + i), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_OPEN_WAREHOUSE + i][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_B_OPEN_WAREHOUSE + i][Hack_Status.App_Language]);
    }
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_ASSIST_LOG), 
            APP_WSTR[AWSTR_APP_HINT_ASSIST][Hack_Status.App_Language], TRUE);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_REVIVE_ENEMY), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_REVIVE_ENEMY][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_REVIVE_ENEMY][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_SUICIDE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_SUICIDE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_SUICIDE][Hack_Status.App_Language]);
    
        // tab 3, Magic
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MAGIC_NAME_1), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MAGIC_NAME][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MAGIC_NAME][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_MAGIC_NAME_2), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_MAGIC_NAME][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_MAGIC_NAME][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_GROUPBOX_MAGIC_PAGE_1), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_1][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_1][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_GROUPBOX_MAGIC_PAGE_2), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_2][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_2][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_GROUPBOX_MAGIC_PAGE_3), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_3][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_3][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_GROUPBOX_MAGIC_PAGE_4), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_4][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_G_MAGIC_PAGE_4][Hack_Status.App_Language]);
    for(__int32 i = 0; i < SF_MAGIC_COUNT; i++){
        SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_MAGIC_1 + i * 5), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR_MAGIC[AWSTR_MAGIC_TRANSPORT + i][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR_MAGIC[AWSTR_MAGIC_TRANSPORT + i][Hack_Status.App_Language]);
    }
        // tab 4, Quest
    for(__int32 i = IDC_STATIC_QUEST_COL_1; i <= IDC_GROUPBOX_QUEST_PAGE_2; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_QUEST_COL_1 + i - IDC_STATIC_QUEST_COL_1][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_S_QUEST_COL_1 + i - IDC_STATIC_QUEST_COL_1][Hack_Status.App_Language]);
    }
    for(__int32 i = IDC_BUTTON_QUEST_1; i <= IDC_BUTTON_QUEST_48; i++){
        SendMessageW(GetDlgItem(hwndParent, i), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR_QUEST[AWSTR_QUEST_DEFEAT_THE_RED_GOBLIN + i - IDC_BUTTON_QUEST_1][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR_QUEST[AWSTR_QUEST_DEFEAT_THE_RED_GOBLIN + i - IDC_BUTTON_QUEST_1][Hack_Status.App_Language]);
    }
        // tab 5, G Warehouse
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_OPEN_G_WAREHOUSE_2), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_B_OPEN_G_WAREHOUSE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_B_OPEN_G_WAREHOUSE][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_GROUPBOX_G_WAREHOUSE), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_G_G_WAREHOUSE][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_G_G_WAREHOUSE][Hack_Status.App_Language]);
    SendMessageW(GetDlgItem(hwndParent, IDC_STATIC_G_WAREHOUSE_INDEX), WM_SETTEXT, 
            (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_S_G_WAREHOUSE_INDEX][Hack_Status.App_Language]), 
            (LPARAM)APP_WSTR[AWSTR_CTL_S_G_WAREHOUSE_INDEX][Hack_Status.App_Language]);
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_G_WAREHOUSE_LOG), 
            APP_WSTR[AWSTR_APP_HINT_G_WAREHOUSE][Hack_Status.App_Language], TRUE);
}
