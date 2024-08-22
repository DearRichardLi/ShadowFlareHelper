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
#define IDM_ABOUT_ADDRESS  0x5
// 0x50 - 0x51 : Tray Bar Icon
#define IDI_ICON      0x50
#define IDI_ICONSM    0x51
// 0x100 - 0x1FF: Tab control, tab 0, Init
#define IDC_TABCONTROL                  0x100
#define IDC_BUTTON_OPENSF               0x101
#define IDC_COMBOBOX_GAMEVERSION        0x102
#define IDC_BUTTON_BIND_GAME            0x103
#define IDC_EDIT_INIT_LOG               0x104
#define IDC_BUTTON_REFRESH              0x105
#define IDC_STATIC_REFRESH_DELAY        0x106
#define IDC_EDIT_REFRESH_DELAY          0x107
#define IDC_UPDOWN_REFRESH_DELAY        0x108
#define IDC_STATIC_GAMEMODE             0x109
#define IDC_EDIT_GAMEMODE               0x10A
#define IDC_STATIC_ONLINEROLE           0x10B
#define IDC_EDIT_ONLINEROLE             0x10C
#define IDC_STATIC_PLAYER_NAME          0x10D
#define IDC_EDIT_PLAYER_NAME            0x10E
#define IDC_BUTTON_APPLY_PLAYER_NAME    0x10F
#define IDC_STATIC_LV                   0x110
#define IDC_EDIT_LV                     0x111
#define IDC_UPDOWN_LV                   0x112
#define IDC_STATIC_SEX                  0x113
#define IDC_COMBOBOX_SEX                0x114
#define IDC_STATIC_EXP                  0x115
#define IDC_EDIT_EXP                    0x116
#define IDC_BUTTON_APPLY_EXP            0x117
#define IDC_STATIC_PROF                 0x118
#define IDC_COMBOBOX_PROF               0x119
#define IDC_STATIC_PROF_TO_BE           0x11A
#define IDC_COMBOBOX_PROF_TO_BE         0x11B
#define IDC_STATIC_COMPANION_LV         0x11C
#define IDC_EDIT_COMPANION_LV           0x11D
#define IDC_UPDOWN_COMPANION_LV         0x11E
#define IDC_STATIC_COMPANION_ID         0x11F
#define IDC_COMBOBOX_COMPANION_ID       0x120
#define IDC_STATIC_COMPANION_EXP        0x121
#define IDC_EDIT_COMPANION_EXP          0x122
#define IDC_BUTTON_APPLY_COMPANION_EXP  0x123
#define IDC_BUTTON_CHANGE_LANG          0x124
// 0x200 - 0x2FF: tab 1, WallHack
#define IDC_BUTTON_HOOK                 0x200
#define IDC_STATIC_HOOK_STATUS          0x201
#define IDC_EDIT_HOOK_STATUS            0x202
#define IDC_EDIT_HOOK_LOG               0x203
#define IDC_STATIC_MAP_ID               0x204
#define IDC_EDIT_MAP_ID                 0x205
#define IDC_STATIC_X                    0x206
#define IDC_EDIT_X                      0x207
#define IDC_STATIC_Y                    0x208
#define IDC_EDIT_Y                      0x209
#define IDC_EDIT_MAP_NAME               0x20A
#define IDC_STATIC_MAP_GATE_ID          0x20B
#define IDC_EDIT_MAP_GATE_ID            0x20C
#define IDC_STATIC_MOVE_DISTANCE        0x20D
#define IDC_EDIT_MOVE_DISTANCE          0x20E
#define IDC_UPDOWN_MOVE_DISTANCE        0x20F
#define IDC_STATIC_MOVE_DELAY           0x210
#define IDC_EDIT_MOVE_DELAY             0x211
#define IDC_UPDOWN_MOVE_DELAY           0x212
#define IDC_STATIC_TELEPORT             0x213
#define IDC_COMBOBOX_TELEPORT_PRESET    0x214
#define IDC_STATIC_TELEPORT_MAP_ID      0x215
#define IDC_COMBOBOX_TELEPORT_MAP_NAME  0x216
#define IDC_EDIT_TELEPORT_MAP_ID        0x217
#define IDC_GROUPBOX_GATE_OR_XY         0x218
#define IDC_BUTTON_RADIO_GATE           0x219
#define IDC_BUTTON_RADIO_XY             0x21A
#define IDC_STATIC_TELEPORT_GATE_ID     0x21B
#define IDC_EDIT_TELEPORT_GATE_ID       0x21C
#define IDC_STATIC_TELEPORT_GATE_WARN   0x21D
#define IDC_STATIC_TELEPORT_X           0x21E
#define IDC_EDIT_TELEPORT_X             0x21F
#define IDC_STATIC_TELEPORT_Y           0x220
#define IDC_EDIT_TELEPORT_Y             0x221
#define IDC_BUTTON_TELEPORT             0x222
// 0x300 - 0x3FF: tab 2, Assist
#define IDC_BUTTON_OPEN_WAREHOUSE       0x300
#define IDC_BUTTON_OPEN_G_WAREHOUSE     0x301
#define IDC_BUTTON_OPEN_CUSTOM_OUTFIT   0x302
#define IDC_BUTTON_PAUSE_GAME           0x303
#define IDC_BUTTON_INFINITE_POWER       0x304
#define IDC_BUTTON_COMPANION_REVIVE     0x305
#define IDC_BUTTON_EXTRA_LANDMINE       0x306
#define IDC_BUTTON_EXTRA_LANDMINE_POWER 0x307
#define IDC_BUTTON_BE_RICH              0x308
#define IDC_BUTTON_NO_MONSTER           0x309
#define IDC_BUTTON_MAGIC_LV_TO_30       0x30A
#define IDC_BUTTON_CRAZY_SPEED          0x30B
#define IDC_BUTTON_GOD_MODE             0x30C
#define IDC_BUTTON_EXTEND_ATK_RANGE     0x30D
#define IDC_EDIT_ASSIST_LOG             0x30E
#define IDC_BUTTON_REVIVE_ENEMY         0x30F
#define IDC_BUTTON_SUICIDE              0x310
// 0x400 - 0x4FF: tab 3, Magic
#define IDC_STATIC_MAGIC_NAME_1         0x400
#define IDC_STATIC_MAGIC_LV_1           0x401
#define IDC_STATIC_MAGIC_EXP_1          0x402
#define IDC_STATIC_MAGIC_NAME_2         0x403
#define IDC_STATIC_MAGIC_LV_2           0x404
#define IDC_STATIC_MAGIC_EXP_2          0x405
#define IDC_GROUPBOX_MAGIC_PAGE_1       0x406
#define IDC_GROUPBOX_MAGIC_PAGE_2       0x407
#define IDC_GROUPBOX_MAGIC_PAGE_3       0x408
#define IDC_GROUPBOX_MAGIC_PAGE_4       0x409
#define IDC_BUTTON_MAGIC_1              0x40A
#define IDC_EDIT_MAGIC_LV_1             0x40B
#define IDC_UPDOWN_MAGIC_LV_1           0x40C
#define IDC_EDIT_MAGIC_EXP_1            0x40D
#define IDC_UPDOWN_MAGIC_EXP_1          0x40E
#define IDC_BUTTON_MAGIC_2              0x40F
#define IDC_EDIT_MAGIC_LV_2             0x410
#define IDC_UPDOWN_MAGIC_LV_2           0x411
#define IDC_EDIT_MAGIC_EXP_2            0x412
#define IDC_UPDOWN_MAGIC_EXP_2          0x413
#define IDC_BUTTON_MAGIC_3              0x414
#define IDC_EDIT_MAGIC_LV_3             0x415
#define IDC_UPDOWN_MAGIC_LV_3           0x416
#define IDC_EDIT_MAGIC_EXP_3            0x417
#define IDC_UPDOWN_MAGIC_EXP_3          0x418
#define IDC_BUTTON_MAGIC_4              0x419
#define IDC_EDIT_MAGIC_LV_4             0x41A
#define IDC_UPDOWN_MAGIC_LV_4           0x41B
#define IDC_EDIT_MAGIC_EXP_4            0x41C
#define IDC_UPDOWN_MAGIC_EXP_4          0x41D
#define IDC_BUTTON_MAGIC_5              0x41E
#define IDC_EDIT_MAGIC_LV_5             0x41F
#define IDC_UPDOWN_MAGIC_LV_5           0x420
#define IDC_EDIT_MAGIC_EXP_5            0x421
#define IDC_UPDOWN_MAGIC_EXP_5          0x422
#define IDC_BUTTON_MAGIC_6              0x423
#define IDC_EDIT_MAGIC_LV_6             0x424
#define IDC_UPDOWN_MAGIC_LV_6           0x425
#define IDC_EDIT_MAGIC_EXP_6            0x426
#define IDC_UPDOWN_MAGIC_EXP_6          0x427
#define IDC_BUTTON_MAGIC_7              0x428
#define IDC_EDIT_MAGIC_LV_7             0x429
#define IDC_UPDOWN_MAGIC_LV_7           0x42A
#define IDC_EDIT_MAGIC_EXP_7            0x42B
#define IDC_UPDOWN_MAGIC_EXP_7          0x42C
#define IDC_BUTTON_MAGIC_8              0x42D
#define IDC_EDIT_MAGIC_LV_8             0x42E
#define IDC_UPDOWN_MAGIC_LV_8           0x42F
#define IDC_EDIT_MAGIC_EXP_8            0x430
#define IDC_UPDOWN_MAGIC_EXP_8          0x431
#define IDC_BUTTON_MAGIC_9              0x432
#define IDC_EDIT_MAGIC_LV_9             0x433
#define IDC_UPDOWN_MAGIC_LV_9           0x434
#define IDC_EDIT_MAGIC_EXP_9            0x435
#define IDC_UPDOWN_MAGIC_EXP_9          0x436
#define IDC_BUTTON_MAGIC_10             0x437
#define IDC_EDIT_MAGIC_LV_10            0x438
#define IDC_UPDOWN_MAGIC_LV_10          0x439
#define IDC_EDIT_MAGIC_EXP_10           0x43A
#define IDC_UPDOWN_MAGIC_EXP_10         0x43B
#define IDC_BUTTON_MAGIC_11             0x43C
#define IDC_EDIT_MAGIC_LV_11            0x43D
#define IDC_UPDOWN_MAGIC_LV_11          0x43E
#define IDC_EDIT_MAGIC_EXP_11           0x43F
#define IDC_UPDOWN_MAGIC_EXP_11         0x440
#define IDC_BUTTON_MAGIC_12             0x441
#define IDC_EDIT_MAGIC_LV_12            0x442
#define IDC_UPDOWN_MAGIC_LV_12          0x443
#define IDC_EDIT_MAGIC_EXP_12           0x444
#define IDC_UPDOWN_MAGIC_EXP_12         0x445
#define IDC_BUTTON_MAGIC_13             0x446
#define IDC_EDIT_MAGIC_LV_13            0x447
#define IDC_UPDOWN_MAGIC_LV_13          0x448
#define IDC_EDIT_MAGIC_EXP_13           0x449
#define IDC_UPDOWN_MAGIC_EXP_13         0x44A
#define IDC_BUTTON_MAGIC_14             0x44B
#define IDC_EDIT_MAGIC_LV_14            0x44C
#define IDC_UPDOWN_MAGIC_LV_14          0x44D
#define IDC_EDIT_MAGIC_EXP_14           0x44E
#define IDC_UPDOWN_MAGIC_EXP_14         0x44F
#define IDC_BUTTON_MAGIC_15             0x450
#define IDC_EDIT_MAGIC_LV_15            0x451
#define IDC_UPDOWN_MAGIC_LV_15          0x452
#define IDC_EDIT_MAGIC_EXP_15           0x453
#define IDC_UPDOWN_MAGIC_EXP_15         0x454
#define IDC_BUTTON_MAGIC_16             0x455
#define IDC_EDIT_MAGIC_LV_16            0x456
#define IDC_UPDOWN_MAGIC_LV_16          0x457
#define IDC_EDIT_MAGIC_EXP_16           0x458
#define IDC_UPDOWN_MAGIC_EXP_16         0x459
#define IDC_BUTTON_MAGIC_17             0x45A
#define IDC_EDIT_MAGIC_LV_17            0x45B
#define IDC_UPDOWN_MAGIC_LV_17          0x45C
#define IDC_EDIT_MAGIC_EXP_17           0x45D
#define IDC_UPDOWN_MAGIC_EXP_17         0x45E
#define IDC_BUTTON_MAGIC_18             0x45F
#define IDC_EDIT_MAGIC_LV_18            0x460
#define IDC_UPDOWN_MAGIC_LV_18          0x461
#define IDC_EDIT_MAGIC_EXP_18           0x462
#define IDC_UPDOWN_MAGIC_EXP_18         0x463
#define IDC_BUTTON_MAGIC_19             0x464
#define IDC_EDIT_MAGIC_LV_19            0x465
#define IDC_UPDOWN_MAGIC_LV_19          0x466
#define IDC_EDIT_MAGIC_EXP_19           0x467
#define IDC_UPDOWN_MAGIC_EXP_19         0x468
#define IDC_BUTTON_MAGIC_20             0x469
#define IDC_EDIT_MAGIC_LV_20            0x46A
#define IDC_UPDOWN_MAGIC_LV_20          0x46B
#define IDC_EDIT_MAGIC_EXP_20           0x46C
#define IDC_UPDOWN_MAGIC_EXP_20         0x46D
#define IDC_BUTTON_MAGIC_21             0x46E
#define IDC_EDIT_MAGIC_LV_21            0x46F
#define IDC_UPDOWN_MAGIC_LV_21          0x470
#define IDC_EDIT_MAGIC_EXP_21           0x471
#define IDC_UPDOWN_MAGIC_EXP_21         0x472
#define IDC_BUTTON_MAGIC_22             0x473
#define IDC_EDIT_MAGIC_LV_22            0x474
#define IDC_UPDOWN_MAGIC_LV_22          0x475
#define IDC_EDIT_MAGIC_EXP_22           0x476
#define IDC_UPDOWN_MAGIC_EXP_22         0x477
// 0x500 - 0x5FF: tab 4, Quest
#define IDC_STATIC_QUEST_COL_1          0x500
#define IDC_STATIC_QUEST_COL_2          0x501
#define IDC_STATIC_QUEST_COL_3          0x502
#define IDC_STATIC_QUEST_COL_4          0x503
#define IDC_GROUPBOX_QUEST_PAGE_1       0x504
#define IDC_GROUPBOX_QUEST_PAGE_2       0x505
#define IDC_BUTTON_QUEST_1              0x506
#define IDC_BUTTON_QUEST_2              0x507
#define IDC_BUTTON_QUEST_3              0x508
#define IDC_BUTTON_QUEST_4              0x509
#define IDC_BUTTON_QUEST_5              0x50A
#define IDC_BUTTON_QUEST_6              0x50B
#define IDC_BUTTON_QUEST_7              0x50C
#define IDC_BUTTON_QUEST_8              0x50D
#define IDC_BUTTON_QUEST_9              0x50E
#define IDC_BUTTON_QUEST_10             0x50F
#define IDC_BUTTON_QUEST_11             0x510
#define IDC_BUTTON_QUEST_12             0x511
#define IDC_BUTTON_QUEST_13             0x512
#define IDC_BUTTON_QUEST_14             0x513
#define IDC_BUTTON_QUEST_15             0x514
#define IDC_BUTTON_QUEST_16             0x515
#define IDC_BUTTON_QUEST_17             0x516
#define IDC_BUTTON_QUEST_18             0x517
#define IDC_BUTTON_QUEST_19             0x518
#define IDC_BUTTON_QUEST_20             0x519
#define IDC_BUTTON_QUEST_21             0x51A
#define IDC_BUTTON_QUEST_22             0x51B
#define IDC_BUTTON_QUEST_23             0x51C
#define IDC_BUTTON_QUEST_24             0x51D
#define IDC_BUTTON_QUEST_25             0x51E
#define IDC_BUTTON_QUEST_26             0x51F
#define IDC_BUTTON_QUEST_27             0x520
#define IDC_BUTTON_QUEST_28             0x521
#define IDC_BUTTON_QUEST_29             0x522
#define IDC_BUTTON_QUEST_30             0x523
#define IDC_BUTTON_QUEST_31             0x524
#define IDC_BUTTON_QUEST_32             0x525
#define IDC_BUTTON_QUEST_33             0x526
#define IDC_BUTTON_QUEST_34             0x527
#define IDC_BUTTON_QUEST_35             0x528
#define IDC_BUTTON_QUEST_36             0x529
#define IDC_BUTTON_QUEST_37             0x52A
#define IDC_BUTTON_QUEST_38             0x52B
#define IDC_BUTTON_QUEST_39             0x52C
#define IDC_BUTTON_QUEST_40             0x52D
#define IDC_BUTTON_QUEST_41             0x52E
#define IDC_BUTTON_QUEST_42             0x52F
#define IDC_BUTTON_QUEST_43             0x530
#define IDC_BUTTON_QUEST_44             0x531
#define IDC_BUTTON_QUEST_45             0x532
#define IDC_BUTTON_QUEST_46             0x533
#define IDC_BUTTON_QUEST_47             0x534
#define IDC_BUTTON_QUEST_48             0x535
// 0x600 - 0x6FF: tab 5, G Warehouse
#define IDC_BUTTON_OPEN_G_WAREHOUSE_2   0x600
#define IDC_GROUPBOX_G_WAREHOUSE        0x601
#define IDC_BUTTON_G_WAREHOUSE_1        0x602
#define IDC_BUTTON_G_WAREHOUSE_2        0x603
#define IDC_BUTTON_G_WAREHOUSE_3        0x604
#define IDC_BUTTON_G_WAREHOUSE_4        0x605
#define IDC_BUTTON_G_WAREHOUSE_5        0x606
#define IDC_BUTTON_G_WAREHOUSE_6        0x607
#define IDC_BUTTON_G_WAREHOUSE_7        0x608
#define IDC_BUTTON_G_WAREHOUSE_8        0x609
#define IDC_BUTTON_G_WAREHOUSE_9        0x60A
#define IDC_BUTTON_G_WAREHOUSE_10       0x60B
#define IDC_STATIC_G_WAREHOUSE_INDEX    0x60C
#define IDC_EDIT_G_WAREHOUSE_INDEX      0x60D
#define IDC_UPDOWN_G_WAREHOUSE_INDEX    0x60E
#define IDC_EDIT_G_WAREHOUSE_LOG        0x60F




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
void CreateTab1(void);
void CreateTab2(void);
void CreateTab3(void);
void CreateTab4(void);
void CreateTab5(void);
void ShowTabContents(HWND hwndTab, __int32 iPageOld, __int32 iPageNew);
void UseCustomFont(HWND hwndTab, HFONT hCustomFont);
void SwitchBindGameControl(HWND hwndTab, BOOL isAble);
void SwitchRefreshControl(HWND hwndTab, BOOL isAble);
void SwitchTeleportModeControl(HWND hwndTab, BOOL isAble);
void ChangeLanguage(void);

#endif /* SFHelperWindows.h */