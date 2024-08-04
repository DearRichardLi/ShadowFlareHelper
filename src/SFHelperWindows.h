#include <windows.h>
#include <stdio.h>
#include <string.h>

#ifndef _SF_HELPER_WINDOWS
#define _SF_HELPER_WINDOWS

    // Control ID
// 0x1 - 0xFF: Menu
// #define MAINMENU           0x0
#define IDM_OPTION_HIDE    0x1
#define IDM_OPTION_EXIT    0x2
#define IDM_ABOUT_HELP     0x3
#define IDM_ABOUT_ABOUTAPP 0x4
// 0x50 - 0x51 : Tray Bar Icon
#define IDI_ICON      0x50
#define IDI_ICONSM    0x51
// 0x100 - 0x1FF: Tab control, tab 0
#define IDC_TABCONTROL                 0x100
#define IDC_BUTTON_OPENSF              0x101
#define IDC_COMBOBOX_GAMEVERSION       0x102
#define IDC_BUTTON_BIND_GAME           0x103
#define IDC_EDIT_INIT_LOG              0x104
#define IDC_STATIC_GAMEMODE            0x105
#define IDC_EDIT_GAMEMODE              0x106
#define IDC_STATIC_ONLINEROLE          0x107
#define IDC_EDIT_ONLINEROLE            0x108
#define IDC_STATIC_PLAYER_NAME         0x109
#define IDC_EDIT_PLAYER_NAME           0x10A
#define IDC_BUTTON_APPLY_PLAYER_NAME   0x10B
#define IDC_STATIC_LV                  0x10C
#define IDC_EDIT_LV                    0x10D
#define IDC_UPDOWN_LV                  0x10E
#define IDC_STATIC_SEX                 0x10F
#define IDC_COMBOBOX_SEX               0x110
#define IDC_STATIC_EXP                 0x111
#define IDC_EDIT_EXP                   0x112
#define IDC_BUTTON_APPLY_EXP           0x113
#define IDC_STATIC_PROF                0x114
#define IDC_COMBOBOX_PROF              0x115
#define IDC_STATIC_PROF_TO_BE          0x116
#define IDC_COMBOBOX_PROF_TO_BE        0x117
#define IDC_STATIC_COMPANION_LV        0x118
#define IDC_EDIT_COMPANION_LV          0x119
#define IDC_UPDOWN_COMPANION_LV        0x11A
#define IDC_STATIC_COMPANION_ID        0x11B
#define IDC_COMBOBOX_COMPANION_ID      0x11C
#define IDC_STATIC_COMPANION_EXP       0x11D
#define IDC_EDIT_COMPANION_EXP         0x11E
#define IDC_BUTTON_APPLY_COMPANION_EXP 0x11F

#define IDC_BUTTON_CHANGE_LANG   0x1FF

// 0x200 - 0x2FF: tab 1


// 0x300 - 0x3FF: tab 2

    // Windows Message type ID (must not duplicate with sys WM)
#define WM_TRAYICON (WM_USER + 1)

    // 10 tabs in current version
#define APP_TAB_COUNT     10

void SetTheme(void);
void SetDefaultLanguage(void);
void CreateFonts_CH_EN(HFONT* hFontCH, HFONT* hFontEN);
void ClearText(HWND hwnd);
void AppendText(HWND hwnd, LPCWSTR newText, BOOL lineFeed);
void InitIcon(void);
void InitTrayBarData(HWND hwnd);
void CreateMenuBar(void);
void CreateTabControl(HWND hwnd, LPARAM lParam);
void CreateTab0(void);
void ShowTabContents(HWND hwndTab, int iPageOld, int iPageNew);
void UseCustomFont(HWND hwndTab, HFONT hCustomFont);
void SwitchOpenGameControl(HWND hwndTab, BOOL isAble);
void ChangeLanguage(void);

#endif /* SFHelperWindows.h */