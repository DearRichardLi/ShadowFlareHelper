#include <Windows.h>

#ifndef _SF_HELPER_LANGUAGE
#define _SF_HELPER_LANGUAGE

#define AVAILABLE_LANGUAGE_COUNT 3 // CHT, CHS, ENG
#define APP_LANG_CHT             0
#define APP_LANG_CHS             1
#define APP_LANG_ENG             2
#define APP_DEFAULT_LANGUAGE     APP_LANG_CHT // CHT

#define APP_WSTR_STRINGS_COUNT         160
    // 0 wndName
#define AWSTR_WNDNAME                    0
    // 1 - 9 Menu Items
#define AWSTR_MENU_OPTION                1
#define AWSTR_MENU_ABOUT                 2
#define AWSTR_MENU_HIDE                  3
#define AWSTR_MENU_EXIT                  4
#define AWSTR_MENU_HELP                  5
#define AWSTR_MENU_ABOUTAPP              6
#define AWSTR_MENU_ADDRESS               7
    // 10 - 29 Tab Name
#define AWSTR_TAB_INIT                  10
#define AWSTR_TAB_WALLHACK              11
#define AWSTR_TAB_ASSIST                12
#define AWSTR_TAB_MAGIC                 13
#define AWSTR_TAB_QUEST                 14
#define AWSTR_TAB_G_WAREHOUSE           15
#define AWSTR_TAB_TELEPORT_GATE         16
#define AWSTR_TAB_STATUS_1              17
#define AWSTR_TAB_STATUS_2              18
#define AWSTR_TAB_STATUS_3              19
    // 30 - 79 hint string
#define AWSTR_APP_INIT_HELP             31
#define AWSTR_APP_WALLHACK_HELP         32
#define AWSTR_APP_LOG_TO_FILE_FAIL      33
#define AWSTR_APP_SF_RUNNING            34
#define AWSTR_APP_SFEXE_NOT_FOUND       35
#define AWSTR_APP_SFEXE_FOUND           36
#define AWSTR_APP_GET_SFWND_FAIL        37
#define AWSTR_APP_GET_TID_FAIL          38
#define AWSTR_APP_GET_PID_FAIL          39
#define AWSTR_APP_GET_HANDLE_FAIL       40
#define AWSTR_APP_GET_MODULE_FAIL       41
#define AWSTR_APP_GET_SFWND_SUC         42
#define AWSTR_APP_GET_TID_SUC           43
#define AWSTR_APP_GET_PID_SUC           44
#define AWSTR_APP_GET_HANDLE_SUC        45
#define AWSTR_APP_GET_MODULE_SUC        46
#define AWSTR_APP_SF_BASE_ADDR          47
#define AWSTR_APP_SF_BIND_SUC           48
#define AWSTR_APP_READ_MEMORY_FAIL      49
#define AWSTR_APP_WRITE_MEMORY_FAIL     50
#define AWSTR_APP_HINT_ONLINE_RISKY     51
#define AWSTR_APP_PERMISSION_DENIED     52
#define AWSTR_APP_STRING_OVERFLOW       53
#define AWSTR_APP_HINT_RELOAD_SAVEFILE  54
#define AWSTR_APP_KEYBOARD_HOOK_FAIL    55
#define AWSTR_APP_CREATE_THREAD_FAIL    56
#define AWSTR_APP_JOIN_THREAD_FAIL      57
#define AWSTR_APP_HOOK_ON               58
#define AWSTR_APP_HOOK_OFF              59
#define AWSTR_APP_SF_CLOSED             60
#define AWSTR_APP_SF_LOGOUT             61
#define AWSTR_APP_SF_NOT_LOGIN          62
#define AWSTR_APP_REFRESH_ON            63
#define AWSTR_APP_REFRESH_OFF           64
#define AWSTR_APP_HINT_ASSIST           65
#define AWSTR_APP_CURSOR_NULL           66
#define AWSTR_APP_BE_RICH_NOT_MONEY     67

#define AWSTR_APP_SFHELPER_ADDRESS      79
    // 80 - 99 text on controls
#define AWSTR_CTL_B_CHANGE_LANG         80
#define AWSTR_CTL_B_OPENSF              81
#define AWSTR_CTL_B_BIND_GAME           82
#define AWSTR_CTL_B_REFRESH             83
#define AWSTR_CTL_S_REFRESH_DELAY       84
#define AWSTR_CTL_S_GAMEMODE            85
#define AWSTR_CTL_E_GAMEMODE_SINGLE     86
#define AWSTR_CTL_E_GAMEMODE_ONLINE     87
#define AWSTR_CTL_S_ONLINEROLE          88
#define AWSTR_CTL_S_PLAYER_NAME         89
#define AWSTR_CTL_B_APPLY               90
#define AWSTR_CTL_S_LV                  91
#define AWSTR_CTL_S_SEX                 92
#define AWSTR_CTL_S_EXP                 93
#define AWSTR_CTL_S_PROF                94
#define AWSTR_CTL_S_PROF_TO_BE          95
#define AWSTR_CTL_S_COMPANION_LV        96
#define AWSTR_CTL_S_COMPANION_ID        97
#define AWSTR_CTL_S_COMPANION_EXP       98

#define AWSTR_CTL_B_HOOK                99
#define AWSTR_CTL_S_HOOK_STATUS        100
#define AWSTR_CTL_E_HOOK_STATUS_ON     101
#define AWSTR_CTL_E_HOOK_STATUS_OFF    102
#define AWSTR_CTL_S_MAP_ID             103
#define AWSTR_CTL_S_X                  104
#define AWSTR_CTL_S_Y                  105
#define AWSTR_CTL_S_MAP_GATE_ID        106
#define AWSTR_CTL_S_MOVE_DISTANCE      107
#define AWSTR_CTL_S_MOVE_DELAY         108
#define AWSTR_CTL_S_TELEPORT           109
#define AWSTR_CTL_S_TELEPORT_MAP_ID    110   
#define AWSTR_CTL_G_GATEORXY           111
#define AWSTR_CTL_B_R_GATE             112
#define AWSTR_CTL_B_R_XY               113
#define AWSTR_CTL_S_TELEPORT_GATE_ID   114
#define AWSTR_CTL_S_TELEPORT_GATE_WARN 115
#define AWSTR_CTL_S_TELEPORT_X         116
#define AWSTR_CTL_S_TELEPORT_Y         117
#define AWSTR_CTL_B_TELEPORT           118

#define AWSTR_CTL_B_OPEN_WAREHOUSE     119
#define AWSTR_CTL_B_OPEN_G_WAREHOUSE   120
#define AWSTR_CTL_B_OPEN_CUSTOM_OUTFIT 121
#define AWSTR_CTL_B_PAUSE_GAME         122
#define AWSTR_CTL_B_INFINITE_POWER     123
#define AWSTR_CTL_B_COMP_REVIVE        124
#define AWSTR_CTL_B_EX_LANDMINE        125
#define AWSTR_CTL_B_EX_LANDMINE_POWER  126
#define AWSTR_CTL_B_BE_RICH            127
#define AWSTR_CTL_B_NO_MONSTER         128
#define AWSTR_CTL_B_MAGIC_TO_30        129
#define AWSTR_CTL_B_CRAZY_SPEED        130
#define AWSTR_CTL_B_GOD_MODE           131
#define AWSTR_CTL_B_EXTEND_ATK_RANGE   132
#define AWSTR_CTL_B_REVIVE_ENEMY       133
#define AWSTR_CTL_B_SUICIDE            134

#define AWSTR_CTL_S_MAGIC_NAME         135
#define AWSTR_CTL_S_MAGIC_LV           136
#define AWSTR_CTL_S_MAGIC_EXP          137
#define AWSTR_CTL_G_TAB_1              138
#define AWSTR_CTL_G_TAB_2              139
#define AWSTR_CTL_G_TAB_3              140
#define AWSTR_CTL_G_TAB_4              141


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

#define APP_WSTR_TELEPORT_PRESET_COUNT  104

#define APP_WSTR_SCENARIO_COUNT         209

#define APP_WSTR_MAGIC_COUNT             22
#define AWSTR_MAGIC_TRANSPORT             0
#define AWSTR_MAGIC_FIRE_BALL             1
#define AWSTR_MAGIC_ICE_BOLT              2
#define AWSTR_MAGIC_PLASMA                3
#define AWSTR_MAGIC_HELL_FIRE             4
#define AWSTR_MAGIC_ICE_BLAST             5
#define AWSTR_MAGIC_HEAL                  6
#define AWSTR_MAGIC_MOON                  7
#define AWSTR_MAGIC_BERSERKER             8
#define AWSTR_MAGIC_ENERGY_SHIELD         9
#define AWSTR_MAGIC_EARTH_SPEAR          10
#define AWSTR_MAGIC_FLAME_STRIKE         11
#define AWSTR_MAGIC_DREAD_DEATHSCYTHE    12
#define AWSTR_MAGIC_LIGHTNING_STORM      13
#define AWSTR_MAGIC_MEDUSA               14
#define AWSTR_MAGIC_SONIC_BLADE          15
#define AWSTR_MAGIC_MUD_JAVELIN          16
#define AWSTR_MAGIC_IDENTIFY             17
#define AWSTR_MAGIC_MAGIC_SHIELD         18
#define AWSTR_MAGIC_COUNTER_BURST        19
#define AWSTR_MAGIC_EXPLOSION            20
#define AWSTR_MAGIC_ELEMENTAL_STRIKE     21


#define APP_WSTR_TELEPORT_GATE_COUNT     51

#endif /* SFHelperLanguage.h */