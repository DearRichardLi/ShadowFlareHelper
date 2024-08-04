#include <Windows.h>

#ifndef _SF_HELPER_LANGUAGE
#define _SF_HELPER_LANGUAGE

#define AVAILABLE_LANGUAGE_COUNT 3 // CHT, CHS, ENG
#define APP_LANG_CHT             0
#define APP_LANG_CHS             1
#define APP_LANG_ENG             2
#define APP_DEFAULT_LANGUAGE     APP_LANG_CHT // CHT

#define APP_WSTR_STRINGS_COUNT   128
    // 0 wndName
#define AWSTR_WNDNAME         0
    // 1 - 9 Menu Items
#define AWSTR_MENU_OPTION     1
#define AWSTR_MENU_ABOUT      2
#define AWSTR_MENU_HIDE       3
#define AWSTR_MENU_EXIT       4
#define AWSTR_MENU_HELP       5
#define AWSTR_MENU_ABOUTAPP   6
    // 10 - 29 Tab Name
#define AWSTR_TAB_INIT       10
#define AWSTR_TAB_WALLHACK   11
#define AWSTR_TAB_ASSIST     12
#define AWSTR_TAB_MAGIC      13
#define AWSTR_TAB_QUEST      14
#define AWSTR_TAB_STATUS_1   15
#define AWSTR_TAB_STATUS_2   16
#define AWSTR_TAB_STATUS_3   17
#define AWSTR_TAB_STATUS_4   18
#define AWSTR_TAB_STATUS_5   19
    // 30 - 79 hint string
#define AWSTR_APP_INIT_HELP            31
#define AWSTR_APP_WALLHACK_HELP        32
#define AWSTR_APP_LOG_TO_FILE_FAIL     33
#define AWSTR_APP_SF_RUNNING           34
#define AWSTR_APP_SFEXE_NOT_FOUND      35
#define AWSTR_APP_SFEXE_FOUND          36
#define AWSTR_APP_GET_SFWND_FAIL       37
#define AWSTR_APP_GET_TID_FAIL         38
#define AWSTR_APP_GET_PID_FAIL         39
#define AWSTR_APP_GET_HANDLE_FAIL      40
#define AWSTR_APP_GET_MODULE_FAIL      41
#define AWSTR_APP_GET_SFWND_SUC        42
#define AWSTR_APP_GET_TID_SUC          43
#define AWSTR_APP_GET_PID_SUC          44
#define AWSTR_APP_GET_HANDLE_SUC       45
#define AWSTR_APP_GET_MODULE_SUC       46
#define AWSTR_APP_SF_BASE_ADDR         47
#define AWSTR_APP_SF_BIND_SUC          48
#define AWSTR_APP_READ_MEMORY_FAIL     49
#define AWSTR_APP_WRITE_MEMORY_FAIL    50
#define AWSTR_APP_HINT_ONLINE_RISKY    51
#define AWSTR_APP_PERMISSION_DENIED    52
#define AWSTR_APP_STRING_OVERFLOW      53
#define AWSTR_APP_HINT_RELOAD_SAVEFILE 54

    // 80 - 99 text on controls
#define AWSTR_CTL_B_CHANGE_LANG        80
#define AWSTR_CTL_B_OPENSF             81
#define AWSTR_CTL_B_BIND_GAME          82
#define AWSTR_CTL_S_GAMEMODE           83
#define AWSTR_CTL_E_GAMEMODE_SINGLE    84
#define AWSTR_CTL_E_GAMEMODE_ONLINE    85
#define AWSTR_CTL_S_ONLINEROLE         86
#define AWSTR_CTL_S_PLAYER_NAME        87
#define AWSTR_CTL_B_APPLY              88
#define AWSTR_CTL_S_LV                 89
#define AWSTR_CTL_S_SEX                90
#define AWSTR_CTL_S_EXP                91
#define AWSTR_CTL_S_PROF               92
#define AWSTR_CTL_S_PROF_TO_BE         93
#define AWSTR_CTL_S_COMPANION_LV       94
#define AWSTR_CTL_S_COMPANION_ID       95
#define AWSTR_CTL_S_COMPANION_EXP      96


#define APP_WSTR_SEX_COUNT      2
#define AWSTR_SEX_FEMALE        0
#define AWSTR_SEX_MALE          1

#define APP_WSTR_PROF_COUNT    17
#define AWSTR_PROF_GUNNER       0
#define AWSTR_PROF_THIFE        1
#define AWSTR_PROF_NINJA        2
#define AWSTR_PROF_SAVAGE       3
#define AWSTR_PROF_ASSASSIN     4
#define AWSTR_PROF_HUNTER       5
#define AWSTR_PROF_SWORDMAN     6
#define AWSTR_PROF_WARRIOR      7
#define AWSTR_PROF_BLACKMAGE    8
#define AWSTR_PROF_WITCH        9
#define AWSTR_PROF_SPELLSWORD  10
#define AWSTR_PROF_KNIGHT      11
#define AWSTR_PROF_SAGE        12
#define AWSTR_PROF_MONK        13
#define AWSTR_PROF_SAMURAI     14
#define AWSTR_PROF_SAINTKNIGHT 15
#define AWSTR_PROF_MERCENARY   16

#define APP_WSTR_COMP_COUNT     6
#define AWSTR_COMP_KERBEROS     0
#define AWSTR_COMP_GRAVITY      1
#define AWSTR_COMP_DUNE         2
#define AWSTR_COMP_FANG         3
#define AWSTR_COMP_HARLEY       4
#define AWSTR_COMP_HAWK         5




#endif /* SFHelperLanguage.h */