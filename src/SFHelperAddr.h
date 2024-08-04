#include <Windows.h>


#ifndef _SF_HELPER_ADDR
#define _SF_HELPER_ADDR

#define ADDRENGCHT(x) ((x)-((ULONG_PTR)0x5B0))
#define ADDRENGCHN(x) ((x)-((ULONG_PTR)0x518))
#define ADDRENGJPN(x) ((x)-((ULONG_PTR)0x400))
#define ADDRENGKOR(x) ((x)-((ULONG_PTR)0x5B0))

#ifndef _SF_ADDR_STATS_OFFSET
#define _SF_ADDR_STATS_OFFSET
/*
 * the STATS, stands for STATUS_SERIES is a set of linear continuous address,
 * which stores a range of global variables (and pointers) (4 bytes).
 *
 * It determined things like whether the Mini-Map is shown,
 * whether player use walk/run, whether player is using tele gates...
 * Since their memory is continuous, we just to need to store the base addr
 * and the offsets.
 *
 * the memory before STATS is LARGE field of 0x00
 *
 * Base addr of STATS varies in different Game Lang/Versions.
 * like in ENG it is 0x8CDF4, but in CHT it is 0x8C844.
 * I store base addr in an array (Addr_STATS_Base),
 * and use #define statements to record the offsets.
 * 
 * usage: ( "ShadowFlare.exe" + Addr_STATS_Base[SF_Version] + Offset )
 * 
 * ! IMPORTANT: To see detail/ effect of each addr, 
 * Please check my "SF Addr Table.xlsx".
 */
// suffix "_P" indicates a pointer.
#define STATS_CAMERA_HORIZONTAL_ORIGIN          0x00
#define STATS_CAMERA_VERTICAL_ORIGIN            0x04
#define STATS_CAMERA_HORIZONTAL_LENGTH          0x08
#define STATS_CAMERA_VERTICAL_LENGTH            0x0C

#define STATS_IMPORTANT_POINTER_1_P             0x10
#define STATS_IMPORTANT_POINTER_2_P             0x14
#define STATS_IMPORTANT_POINTER_3_P             0x18
#define STATS_IMPORTANT_POINTER_4_P             0x1C
#define STATS_IMPORTANT_POINTER_5_P             0x20
#define STATS_IMPORTANT_POINTER_6_P             0x24
 
#define STATS_HP_ANIMATION_INDICATOR            0x28
#define STATS_MP_ANIMATION_INDICATOR            0x2C
#define STATS_WEIGHT_BAR_INDICATOR              0x30
#define STATS_WEIGHT_BAR_IS_ANIMATING           0x34
#define STATS_LEVEL_NUM_FLASHING                0x38
#define STATS_TO_WAREHOUSE_ANIMATION_INDICATOR  0x3C

#define STATS_POINTER_HOLDING_ITEM_P            0x40
 
#define STATS_TAB_STATUS                        0x44
#define STATS_TAB_ITEM                          0x48
#define STATS_TAB_MAGIC                         0x4C
#define STATS_TAB_SHOP                          0x50
#define STATS_TAB_WAREHOUSE                     0x54
#define STATS_TAB_GIANTWAREHOUSE                0x58
#define STATS_TAB_TELEPORT_GATES                0x5C
#define STATS_TAB_QUEST                         0x60
#define STATS_TAB_HELP                          0x64
#define STATS_TAB_ESC_MENU                      0x68
#define STATS_TAB_OUTFIT_CUSTOMIZE              0x6C
#define STATS_TAB_MINIMAP                       0x70
#define STATS_TAB_SPECIAL_ITEM                  0x74
#define STATS_TAB_BLACKJACK                     0x78

#define STATS_ESC_MENU_FLASHING                 0x7C
#define STATS_STATUS_FLASHING                   0x80
#define STATS_ITEM_FLASHING                     0x84

#define STATS_PLAYER_IS_AT_DUNGEON              0x88
#define STATS_WALK_RUN                          0x8C

// ----UNKNOWN----                              0x90

#define STATS_PAUSE_GAME                        0x94
#define STATS_RELOAD_SAVEFILE_TRIGGER           0x98
#define STATS_TO_TITLE_NO_SAVING                0x9C

// ----UNKNOWN----                              0xA0

#define STATS_TWINKLING_POINTS_TIMER            0xA4
#define STATS_CLOSE_BUTTON_STATUS               0xA8
#define STATS_CLOSE_BUTTON_TIMER                0xAC

// ----UNKNOWN----                              0xB0
// ----UNKNOWN----                              0xB4
// ----UNKNOWN----                              0xB8

#define STATS_TELEGATE_IS_UNLOCKED_P            0xBC

// ----UNKNOWN----                              0xC0

#define STATS_QUEST_IS_UNLOCKED_P               0xC4

// ----UNKNOWN_P----                            0xC8
// ----UNKNOWN----                              0xCC

#define STATS_NPC_DIALOG_IS_UNLOCKED_P          0xD0
#endif // _SF_ADDR_STATS_OFFSET

#ifndef _SF_ADDR_CHARACTER_ATTRIBUTE_OFFSET
#define _SF_ADDR_CHARACTER_ATTRIBUTE_OFFSET
// suffix "_P" indicates a pointer.
#define CA_GAME_MODE                            0x00
#define CA_CLIENT_INDEX                         0x04
// ----UNKNOWN----                              0x08
// ----UNKNOWN----                              0x0C // same as 0x04
#define CA_PLAYER_NAME                          0x10 // length: 20bytes
// ----UNKNOWN----                              0x24
#define CA_PLAYER_SEX                           0x28
#define CA_PROFESSION                           0x2C
#define CA_PROFESSION_TO_BE                     0x30
#define CA_LV                                   0x34
#define CA_ATK_SPD                              0x38
#define CA_WALK_SPD                             0x3C
#define CA_HP_LIMIT                             0x40
#define CA_HP_LIMIT_SEX_ORI_VALUE               0x44
#define CA_MP_LIMIT                             0x48
#define CA_MP_LIMIT_SEX_ORI_VALUE               0x4C
#define CA_STRENGTH                             0x50
#define CA_ATK                                  0x54
#define CA_DEF                                  0x58
#define CA_HIT_RATE                             0x5C
#define CA_EVASION_RATE                         0x60
#define CA_M_ATK                                0x64
#define CA_M_DEF                                0x68
#define CA_M_HIT_RATE                           0x6C
#define CA_M_EVASION_RATE                       0x70
#define CA_ATTRIBUTE_GREEN_POINT_X              0x74
#define CA_ATTRIBUTE_GREEN_POINT_Y              0x78
// ----UNKNOWN----                              0x7C - 0xBC
#define CA_KILL_COUNTER_TOTAL                   0xC0
#define CA_KILL_COUNTER_ONE_HAND_SWORD          0xC4
#define CA_KILL_COUNTER_AXE                     0xC8
// ----UNKNOWN----                              0xCC
#define CA_KILL_COUNTER_TWO_HAND_SWORD          0xD0
// ----UNKNOWN----                              0xD4
#define CA_KILL_COUNTER_BOW                     0xD8
// ----UNKNOWN----                              0xDC
// ----UNKNOWN----                              0xE0
#define CA_KILL_COUNTER_MAGIC                   0xE4
#define CA_PLAYER_EXP                           0xE8
// ----UNKNOWN----                              0xEC - 0x14C
#define CA_COMPANION_ID                        0x150
#define CA_COMPANION_LV                        0x154
#define CA_COMPANION_EXP                       0x158
#define CA_COMPANION_REVIVE_TIMER              0x15C
#define CA_LANDMINE_POSSESS_LIMIT              0x160
#define CA_EXTRA_LANDMINE_LIMIT                0x164
#define CA_EXTRA_MAGIC_LV                      0x168
#define CA_CHANT_SPD                           0x16C

#define CA_PLAYER_NAME_2                       0x170 // length: 20bytes
// ----UNKNOWN----                             0x184
#define CA_PLAYER_SEX_2                        0x188
#define CA_PROFESSION_2                        0x18C
#define CA_PROFESSION_TO_BE_2                  0x190
#define CA_LV_2                                0x194
#define CA_ATK_SPD_2                           0x198
#define CA_WALK_SPD_2                          0x19C
#define CA_HP_LIMIT_2                          0x1A0
#define CA_HP                                  0x1A4
#define CA_MP_LIMIT_2                          0x1A8
#define CA_MP                                  0x1AC
#define CA_STRENGTH_2                          0x1B0
#define CA_ATK_2                               0x1B4
#define CA_DEF_2                               0x1B8
#define CA_HIT_RATE_2                          0x1BC
#define CA_EVASION_RATE_2                      0x1C0
#define CA_M_ATK_2                             0x1C4
#define CA_M_DEF_2                             0x1C8
#define CA_M_HIT_RATE_2                        0x1CC
#define CA_M_EVASION_RATE_2                    0x1D0
#define CA_ATTRIBUTE_X                         0x1D4
#define CA_ATTRIBUTE_Y                         0x1D8
// ----UNKNOWN----                             0x1DC - 0x21C
// ----UNKNOWN----                             0x220 - 0x2AC
#define CA_COMPANION_ID_2                      0x2B0
#define CA_COMPANION_LV_2                      0x2B4
#define CA_COMPANION_EXP_2                     0x2B8
#define CA_COMPANION_REVIVE_TIMER_2            0x2BC
#define CA_LANDMINE_POSSESS_LIMIT_2            0x2C0
#define CA_EXTRA_LANDMINE_LIMIT_2              0x2C4
#define CA_EXTRA_MAGIC_LV_2                    0x2C8
#define CA_CHANT_SPD_2                         0x2CC

#define CA_IS_OPERATABLE                       0x2D0
// ----UNKNOWN----                             0x2D4
#define CA_MONSTER_DISPLAY_AND_AI              0x2D8
#define CA_IS_MOVEABLE                         0x2DC
#define CA_PLAYER_POSITION_X                   0x2E0
#define CA_PLAYER_POSITION_Y                   0x2E4
// ----UNKNOWN----                             0x2E8 - 0x2FC
#define CA_REAL_SPEED_WALK                     0x300
#define CA_REAL_SPEED_RUN                      0x304
#define CA_PLAYER_MODEL_SHAKE_TIMER            0x308
#define CA_PLAYER_MOVE_TIMER                   0x30C
// ----UNKNOWN----                             0x310
#define CA_PLAYER_CURRENT_MOTION               0x314
#define CA_PLAYER_NEXT_MOTION                  0x318
#define CA_PLAYER_DIRECTION                    0x31C
// ----UNKNOWN----                             0x320
// ----UNKNOWN----                             0x324
#define CA_LANDMINE_POSSESS                    0x328
// ----UNKNOWN----                             0x32C - 0x3DC
#define CA_CURRENT_MAP_RESOURCE_P              0x3E0
// ----UNKNOWN----                             0x3E4 - 0x3EC
#define CA_CLICK_TO_MOVE_RANGE                 0x3F0
#define CA_PICKUP_AND_ATK_RANGE                0x3F4
#define CA_MOUSE_KEYBOARD_LISTENER_P           0x3F8
#define CA_MOUSE_CURSOR_COORDINATE_X           0x3FC
#define CA_MOUSE_CURSOR_COORDINATE_Y           0x400
// ----UNKNOWN----                             0x404 - 0x438
#define CA_LOADSCREEN_TRIGGER                  0x43C
#define CA_MAP_ID                              0x440
#define CA_MAP_GATE_ID                         0x444
#define CA_TRANSPORT_POSITION_X                0x448
#define CA_TRANSPORT_POSITION_Y                0x44C
// ----UNKNOWN----                             0x450 - 0x454
#define CA_TRANSPORT_ATTRIBUTES_P              0x458
// ----UNKNOWN----                             0x45C - 0x4E4
#define CA_PLAYER_HELM_P                       0x4E8
#define CA_PLAYER_CLOTH_P                      0x4EC
#define CA_PLAYER_SHOE_P                       0x4F0
#define CA_PLAYER_WEAPON_1_P                   0x4F4
#define CA_PLAYER_SHEILD_1_P                   0x4F8
#define CA_PLAYER_ACCESSORY_1_P                0x4FC
#define CA_PLAYER_ACCESSORY_2_P                0x500
#define CA_PLAYER_ACCESSORY_3_P                0x504
#define CA_PLAYER_ACCESSORY_4_P                0x508
#define CA_PLAYER_WEAPON_2_P                   0x50C
#define CA_PLAYER_SHEILD_2_P                   0x510
#define CA_PLAYER_BAG_ITEM_P                   0x514
#define CA_PLAYER_TABLET_P                     0x518
#define CA_PLAYER_WAREHOUSE_P                  0x51C
#define CA_PLAYER_G_WAREHOUSE_1_P              0x520
#define CA_PLAYER_G_WAREHOUSE_2_P              0x524
#define CA_PLAYER_G_WAREHOUSE_3_P              0x528
#define CA_PLAYER_G_WAREHOUSE_4_P              0x52C
#define CA_PLAYER_G_WAREHOUSE_5_P              0x530
#define CA_PLAYER_G_WAREHOUSE_6_P              0x534
#define CA_PLAYER_G_WAREHOUSE_7_P              0x538
#define CA_PLAYER_G_WAREHOUSE_8_P              0x53C
#define CA_PLAYER_G_WAREHOUSE_9_P              0x540
#define CA_PLAYER_G_WAREHOUSE_10_P             0x544
#define CA_PLAYER_G_WAREHOUSE_11_P             0x548
#define CA_PLAYER_G_WAREHOUSE_12_P             0x54C
#define CA_PLAYER_G_WAREHOUSE_13_P             0x550
#define CA_PLAYER_G_WAREHOUSE_14_P             0x554
#define CA_G_WAREHOUSE_CURRENT_PAGE            0x558
#define CA_G_WAREHOUSE_1_UNLOCK                0x55C
#define CA_G_WAREHOUSE_2_UNLOCK                0x560
#define CA_G_WAREHOUSE_3_UNLOCK                0x564
#define CA_G_WAREHOUSE_4_UNLOCK                0x568
#define CA_G_WAREHOUSE_5_UNLOCK                0x56C
#define CA_G_WAREHOUSE_6_UNLOCK                0x570
#define CA_G_WAREHOUSE_7_UNLOCK                0x574
#define CA_G_WAREHOUSE_8_UNLOCK                0x578
#define CA_G_WAREHOUSE_9_UNLOCK                0x57C
#define CA_G_WAREHOUSE_10_UNLOCK               0x580
// ----UNUSED FLAGS----                        0x584 - 0xC9C
#define CA_STAY_IN_CURRENT_MAP_TIMER           0xCA0
// ----DUPLICATED PLAYER POSITION XY----       0xCA4 - 0x1240
// ----UNKNOWN----                            0x1244 - 0x126C
#define CA_PLAYER_DIRECTION_RBUTTON_ATK       0x1270
#define CA_MOUSE_RBUTTON_CURSOR_COORDINATE_X  0x1274
#define CA_MOUSE_RBUTTON_CURSOR_COORDINATE_Y  0x1278
#define CA_PLAYER_CURRENT_MAGIC_ID            0x127C
// ----UNKNOWN----                            0x1280 - 0x1284
#define CA_PLAYER_IS_USING_WEAPON             0x1288
// ----UNKNOWN----                            0x128C - 0x143C
#define CA_MAGIC_TRANSPORT                    0x1440
#define CA_MAGIC_FIRE_BALL                    0x1444
#define CA_MAGIC_ICE_BOLT                     0x1448
#define CA_MAGIC_PLASMA                       0x144C
#define CA_MAGIC_HELL_FIRE                    0x1450
#define CA_MAGIC_ICE_BLAST                    0x1454
#define CA_MAGIC_HEAL                         0x1458
#define CA_MAGIC_MOON                         0x145C
#define CA_MAGIC_BERSERKER                    0x1460
#define CA_MAGIC_ENERGY_SHIELD                0x1464
#define CA_MAGIC_EARTH_SPEAR                  0x1468
#define CA_MAGIC_FLAME_STRIKE                 0x146C
#define CA_MAGIC_DREAD_DEATHSCYTHE            0x1470
#define CA_MAGIC_LIGHTNING_STORM              0x1474
#define CA_MAGIC_MEDUSA                       0x1478
#define CA_MAGIC_SONIC_BLADE                  0x147C
#define CA_MAGIC_MUD_JAVELIN                  0x1480
#define CA_MAGIC_IDENTIFY                     0x1484
#define CA_MAGIC_MAGIC_SHIELD                 0x1488
#define CA_MAGIC_COUNTER_BURST                0x148C
#define CA_MAGIC_EXPLOSION                    0x1490
#define CA_MAGIC_ELEMENTAL_STRIKE             0x1494
#define CA_MAGIC_TRANSPORT_LV                 0x1498
#define CA_MAGIC_FIRE_BALL_LV                 0x149C
#define CA_MAGIC_ICE_BOLT_LV                  0x14A0
#define CA_MAGIC_PLASMA_LV                    0x14A4
#define CA_MAGIC_HELL_FIRE_LV                 0x14A8
#define CA_MAGIC_ICE_BLAST_LV                 0x14AC
#define CA_MAGIC_HEAL_LV                      0x14B0
#define CA_MAGIC_MOON_LV                      0x14B4
#define CA_MAGIC_BERSERKER_LV                 0x14B8
#define CA_MAGIC_ENERGY_SHIELD_LV             0x14BC
#define CA_MAGIC_EARTH_SPEAR_LV               0x14C0
#define CA_MAGIC_FLAME_STRIKE_LV              0x14C4
#define CA_MAGIC_DREAD_DEATHSCYTHE_LV         0x14C8
#define CA_MAGIC_LIGHTNING_STORM_LV           0x14CC
#define CA_MAGIC_MEDUSA_LV                    0x14D0
#define CA_MAGIC_SONIC_BLADE_LV               0x14D4
#define CA_MAGIC_MUD_JAVELIN_LV               0x14D8
#define CA_MAGIC_IDENTIFY_LV                  0x14DC
#define CA_MAGIC_MAGIC_SHIELD_LV              0x14E0
#define CA_MAGIC_COUNTER_BURST_LV             0x14E4
#define CA_MAGIC_EXPLOSION_LV                 0x14E8
#define CA_MAGIC_ELEMENTAL_STRIKE_LV          0x14EC
#define CA_MAGIC_TRANSPORT_EXP                0x14F0
#define CA_MAGIC_FIRE_BALL_EXP                0x14F4
#define CA_MAGIC_ICE_BOLT_EXP                 0x14F8
#define CA_MAGIC_PLASMA_EXP                   0x14FC
#define CA_MAGIC_HELL_FIRE_EXP                0x1500
#define CA_MAGIC_ICE_BLAST_EXP                0x1504
#define CA_MAGIC_HEAL_EXP                     0x1508
#define CA_MAGIC_MOON_EXP                     0x150C
#define CA_MAGIC_BERSERKER_EXP                0x1510
#define CA_MAGIC_ENERGY_SHIELD_EXP            0x1514
#define CA_MAGIC_EARTH_SPEAR_EXP              0x1518
#define CA_MAGIC_FLAME_STRIKE_EXP             0x151C
#define CA_MAGIC_DREAD_DEATHSCYTHE_EXP        0x1520
#define CA_MAGIC_LIGHTNING_STORM_EXP          0x1524
#define CA_MAGIC_MEDUSA_EXP                   0x1528
#define CA_MAGIC_SONIC_BLADE_EXP              0x152C
#define CA_MAGIC_MUD_JAVELIN_EXP              0x1530
#define CA_MAGIC_IDENTIFY_EXP                 0x1534
#define CA_MAGIC_MAGIC_SHIELD_EXP             0x1538
#define CA_MAGIC_COUNTER_BURST_EXP            0x153C
#define CA_MAGIC_EXPLOSION_EXP                0x1540
#define CA_MAGIC_ELEMENTAL_STRIKE_EXP         0x1544
// ----UNKNOWN----                            0x1548 - 0x154C
#define CA_POWER_KILL_COUNTER                 0x1550
#define CA_POWER_REMAINING_TIMER              0x1554
#define CA_POWER_PASTED_TIME_TIMER            0x1558
// ----UNKNOWN----                            0x155C - 0x159C
#define CA_COMPANION_IS_ACTIVE                0x15A0
#endif // _SF_ADDR_CHARACTER_ATTRIBUTE_OFFSET


#endif /* SFHelperAddr.h */