#ifndef _SF_HELPER_RESOURCE
#define _SF_HELPER_RESOURCE

#ifndef _SF_PROFESSION_CODE
#define _SF_PROFESSION_CODE
#define P_C_GUNNER      0x00
#define P_C_THIFE       0x01
#define P_C_NINJA       0x02
#define P_C_SAVAGE      0x03
#define P_C_ASSASSIN    0x04
#define P_C_HUNTER      0x05
#define P_C_SWORDMAN    0x06
#define P_C_WARRIOR     0x07
#define P_C_BLACKMAGE   0x08
#define P_C_WITCH       0x09
#define P_C_SPELLSWORD  0x0A
#define P_C_KNIGHT      0x0B
#define P_C_SAGE        0x0C
#define P_C_MONK        0x0D
#define P_C_SAMURAI     0x0E
#define P_C_SAINTKNIGHT 0x0F
#define P_C_MERCENARY   0x10
#endif // _SF_PROFESSION_CODE

#ifndef _SF_SCENARIO
#define _SF_SCENARIO
    // EP1
#define S_REMOTE_TOWN                         0
#define S_NEAR_THE_REMOTE_TOWN                1
#define S_WASTELAND_OF_HESITATION             3
#define S_IRON_BORDERLINE                     4
#define S_FROZEN_FOREST                       5
#define S_WASTELAND_OF_PILLARS                6
#define S_DUSTY_RUINS_B1F_B2F             10000
#define S_DUSTY_RUINS_B3F                 10001
#define S_DUSTY_RUINS_B4F                 10002
#define S_DUSTY_RUINS_B5F                 10003
#define S_DUSTY_RUINS_ROOM_OF_JUDGMENT    10004
#define S_DUSTY_RUINS_CONTINUED_ROOM      10005
#define S_COLD_SVALT_TOWN               1000000
#define S_NEAR_COLD_SVALT_TOWN          1000001
#define S_VAPOROUS_FOREST               1000002
#define S_HANGED_MENS_FOREST            1000003
#define S_SEA_OF_TREES                  1000004
#define S_COLD_RUINS_B1F                1020000
#define S_COLD_RUINS_B2F_B3F_SMALL_ROOM 1020001
#define S_COLD_RUINS_BOTTOM_FLOOR       1020002
#define S_PURGATORY_OF_JUDGMENTS_B1F    1030000
#define S_PURGATORY_OF_JUDGMENTS_B2F    1030001
#define S_PURGATORY_OF_JUDGMENTS_RIGHT_WRONG_ROOM 1030002
#define S_REMAINS_OF_REINCARNATION_ENTRANCE       1040000
#define S_REMAINS_OF_REINCARNATION_1F_TO_3F       1040001
#define S_REMAINS_OF_REINCARNATION_BIG_HALL       1040002
#define S_IMMORTAL_REMAINS_B1F                    1050000
#define S_IMMORTAL_REMAINS_B2F                    1050001
#define S_IMMORTAL_REMAINS_HEATED_HALL            1050002

#define S_FOREST_AREA_1                      2000000
#define S_FOREST_AREA_2                      2000001
#define S_MINE__FOREST                       2010000
#define S_KANFORE_MINING_TOWN                2100000
#define S_FOREST_OF_FOUR_LEAVES              2100001
#define S_FOREST_OF_CLAWS                    2100002
#define S_FOREST_OF_SILENCE                  2100003
#define S_CROSS_AGORA                        2100004
#define S_FOREST_OF_SPRITS                   2100005
#define S_FOREST_OF_KNIGHTS_MISERY           2100006
#define S_TOWER_OF_THE_WIZARD_1F_TO_10F      2110000
#define S_FORT_OF_THIEVES                    2120000
#define S_BACK_STREET_OF_THE_FORT_OF_THIEVES 2120001
#define S_COAL_MINE__FOREST_OF_FOUR_LEAVES   2130000
#define S_COAL_MINE__FOREST_OF_SPRITS        2140000
#define S_FANANN_VILLAGE_OF_ELVES            2200000
#define S_BUTTERFLY_HILL                     2200001
#define S_FOREST_OF_WESLEY                   2200002
#define S_DRAGON_ROAD                        2200003
#define S_LABYRINTH_OF_MAUVE                 2200004
#define S_NEAR_THE_POWER_SUPPLY_FACILITY     2200005
#define S_MINING_TUNNEL_OF_YUGUNOS_B1F       2210000
#define S_MINING_TUNNEL_OF_YUGUNOS_B2F       2210001
#define S_MINING_TUNNEL_OF_YUGUNOS_B3F       2210002
#define S_MINING_TUNNEL_OF_YUGUNOS_B4F       2210003
#define S_MINING_TUNNEL_OF_YUGUNOS_B5F       2210004
#define S_UNDERGROUND_PASSAGE_B1F            2220000
#define S_UNDERGROUND_PASSAGE_B2F            2220001
#define S_FORT_OF_THE_POWER_SUPPLY           2230000
#define S_CAVE_B1F__BUTTERFLY_HILL           2240000
#define S_CAVE_B2F                           2240001
#define S_WESLEY_CAVE                        2250000
#define S_CARAVAN                            2999999

#define S_THE_WILDS_OF_DEATH_AND_DARKNESS             3000101
#define S_VALLEY_OF_DYING_PEOPLE                      3000201
#define S_LUNAFULD_BEACH                              3000202
#define S_ALTERIA                                     3000203
#define S_GOLAS_DESERT                                3000301
#define S_HILL_OF_HEAVEN                              3000302
#define S_THE_ROAD_OF_ATONEMENT                       3000303
#define S_GORONABURB                                  3000304
#define S_THE_GULF_OF_LUCENTIA                        3000305
#define S_THE_PLAIN_OF_DIALOSE                        3000306
#define S_THE_WILDS_OF_RYUMYAKU                       3000307
#define S_FOREST_OF_ILBARNA                           3000402
#define S_SOUTH_LOSMANS                               3000403
#define S_EAST_LOSMANS                                3000404
#define S_GUNGSTONWALD                                3000405
#define S_WEST_ANTALUSIA                              3000406
#define S_THE_FOOT_OF_MT_TEDORON                      3000407
#define S_THE_MOLDONA_PENINSULA                       3000503
#define S_MESRALD_BURIAL_GROUNDS                      3000505
#define S_SOUTH_ANTALUSIA                             3000506
#define S_EAST_ANTALUSIA                              3000507
#define S_EAST_OF_THE_REMAINS_OF_THE_DEAD             3010000
#define S_WEST_OF_THE_REMAINS_OF_THE_DEAD             3010001
#define S_SOUTH_OF_THE_REMAINS_OF_THE_DEAD            3010002
#define S_NORTH_OF_THE_REMAINS_OF_THE_DEAD            3010003
#define S_THE_REMAINS_OF_THE_DEAD_CENTRAL_ROOM        3010004
#define S_TOWER_OF_NAZZLE_1F                          3020000
#define S_TOWER_OF_NAZZLE_2F                          3020001
#define S_TOWER_OF_NAZZLE_3F                          3020002
#define S_TOWER_OF_NAZZLE_4F                          3020003
#define S_TOWER_OF_NAZZLE_5F                          3020004
#define S_UNDERGROUND_CAVE_OF_A_CHURCH                3030000
#define S_RUINS_OF_CARN__MESRALD_BURIAL_GROUNDS       3040000
#define S_RUINS_OF_DALS__MESRALD_BURIAL_GROUNDS       3050000
#define S_COLDEA_CAVE__MESRALD_BURIAL_GROUNDS         3060000
#define S_WHAM_CAVE__MESRALD_BURIAL_GROUNDS           3070000
#define S_THE_RUINS_OF_THE_LAKE__THE_PLAIN_OF_DIALOSE 3080000
#define S_THE_REMAINS_OF_HEARTBEAT                    3090000
#define S_GORE_CAVE__GUNGSTONWALD                     3100000
#define S_TOWER_OF_LICARN_1F                          3110000
#define S_TOWER_OF_LICARN_2F                          3110001
#define S_TOWER_OF_LICARN_3F                          3110002
#define S_TOWER_OF_LICARN_4F                          3110003
#define S_TOWER_OF_LICARN_5F                          3110004
#define S_DRAGON_CAVE__FOREST_OF_ILBARNA              3120000
#define S_PONERO_CAVE__THE_MOLDONA_PENINSULA          3130000
#define S_ANCIENT_RUINS_B1F                           3140000
#define S_ANCIENT_RUINS_B2F                           3140001
#define S_THE_RUINS_OF_GOLDO__THE_ROAD_OF_ATONEMENT   3150000
#define S_MERIA_RUIN__GORONABURB                      3160000
#define S_BIDAL_RUIN__GOLAS_DESERT                    3170000
#define S_THE_RUINS_OF_LUKUNA__GOLAS_DESERT           3180000
#define S_THE_RUINS_OF_DRON__GOLAS_DESERT             3190000
#define S_WOG_CAVE__VALLEY_OF_DYING_PEOPLE            3200000
#define S_UNDERGROUND_PASSAGE__VALLEY_OF_DYING_PEOPLE 3210000
#define S_THE_RUINS_OF_ZERES__LUNAFULD_BEACH          3220000
#define S_MOUR_CAVE__LUNAFULD_BEACH                   3230000
#define S_DARK_ELVES_HIDING_PLACE                     3240000
#define S_SOUTH_CAMP_OF_YUGUNOS                       3900000
#define S_A_TOWN_OF_ANTALUSIA                         3900001
#define S_TOWN_OF_CALADO                              3900002
#define S_TOWN_OF_LOSMANS                             3900003
#define S_PONSE_VILLAGE_OF_DWARVES                    3900004
#define S_SENAS_SMALL_SHRINE                          3900005

#define S_WEST_CALADO                      4000000
#define S_GARWOOD_SWAMP                    4000001
#define S_LABYRINTH_OF_THE_LAKE            4000002
#define S_DRAGON_FOREST                    4000003
#define S_DEMONS_FOREST                    4000004
#define S_ORPHE_BEACH                      4000005
#define S_FOREST_OF_POISON                 4000006
#define S_FOREST_OF_GOLIATE                4000007
#define S_FANTASY_ROAD                     4000008
#define S_FOREST_OF_DEATH                  4000009
#define S_THE_ANCIENT_INSTITUTE            4010000
#define S_THE_RUINS_OF_KASHUGAL            4020000
#define S_TUNNEL_UNDER_THE_LAKE            4030000
#define S_RUINS_OF_EXORCISM                4040000
#define S_GOLIATES_MANSION_B1F             4050000
#define S_GOLIATES_MANSION_B2F             4050001
#define S_GOLIATES_MANSION_B3F             4020002
#define S_THE_ROAD_OF_THE_NETHERWORLD_B1F  4060000
#define S_THE_ROAD_OF_THE_NETHERWORLD_B2F  4060001
#define S_THE_ROAD_OF_THE_NETHERWORLD_B3F  4060002
#define S_DEVILS_CASTLE_1F                 4060003
#define S_DEVILS_CASTLE_2F                 4060004
#define S_DEVILS_CASTLE_3F                 4060005
#define S_DEVILS_CASTLE_4F                 4060006
#define S_THE_CAVE_OF_RUINS_B1F            4070000
#define S_THE_CAVE_OF_RUINS_B2F            4070001
#define S_SENAS_TOWER_1F                   4080000
#define S_SENAS_TOWER_2F                   4080001
#define S_SENAS_TOWER_3F                   4080002
#define S_SENAS_TOWER_4F                   4080003
#define S_SENAS_TOWER_5F                   4080004
#define S_TOWER_OF_REBELLION_1F                           4090000
#define S_TOWER_OF_REBELLION_2F                           4090001
#define S_TOWER_OF_REBELLION_3F                           4090002
#define S_TOWER_OF_REBELLION_4F                           4090003
#define S_THE_RUINS_OF_THE_WISE__GORONABURB               4100000
#define S_THE_RUINS_OF_REMOTENESS__MESRALD_BURIAL_GROUNDS 4110000
#define S_FORT_OF_DEMON_B1F                               4120000
#define S_FORT_OF_DEMON_B2F                               4120001
#define S_FOREST_OF_MADNESS                               4130000
#define S_DINOSAUR_CAVE__FANTASY_ROAD                     4140000
#define S_WEST_GATE_OF_CALADO                             4900000
#define S_BERINI_VILLAGE                                  4900001
#define S_ENTO_VILLAGE                                    4900002
#define S_RUINS_OF_BERINI_VILLAGE                         4900003

#define S_ROAD_TO_A_TOWER           99000000
#define S_TOWER_OF_ORDEAL           99000001
#define S_TOWER_OF_ORDEAL_1F        99000002
#define S_TOWER_OF_ORDEAL_2F        99000003
#define S_TOWER_OF_ORDEAL_3F        99000004
#define S_TOWER_OF_ORDEAL_4F        99000005
#define S_TOWER_OF_ORDEAL_5F        99000006
#define S_TOWER_OF_ORDEAL_6F        99000007
#define S_TOWER_OF_ORDEAL_7F        99000008
#define S_TOWER_OF_ORDEAL_8F        99000009
#define S_TOWER_OF_ORDEAL_9F        99000010
#define S_TOWER_OF_ORDEAL_10F       99000011
#define S_TOWER_OF_ORDEAL_11F       99000012
#define S_TOWER_OF_ORDEAL_12F       99000013
#define S_TOWER_OF_ORDEAL_13F       99000014
#define S_TOWER_OF_ORDEAL_14F       99000015
#define S_TOWER_OF_ORDEAL_15F       99000016
#define S_TOWER_OF_ORDEAL_16F       99000017
#define S_TOWER_OF_ORDEAL_17F       99000018
#define S_TOWER_OF_ORDEAL_18F       99000019
#define S_TOWER_OF_ORDEAL_19F       99000020
#define S_TOWER_OF_ORDEAL_20F       99000021
#define S_TOWER_OF_ORDEAL_21F       99000022
#define S_TOWER_OF_ORDEAL_TOP_FLOOR 99000023
#define S_TOWER_OF_ORDEAL_ANNEX_1F          99000024
#define S_TOWER_OF_ORDEAL_ANNEX_2F          99000025
#define S_TOWER_OF_ORDEAL_ANNEX_3F          99000026
#define S_TOWER_OF_ORDEAL_ANNEX_4F          99000027
#define S_TOWER_OF_ORDEAL_ANNEX_5F          99000028
#define S_TOWER_OF_ORDEAL_ANNEX_6F          99000029
#define S_TOWER_OF_ORDEAL_ANNEX_7F          99000030
#define S_TOWER_OF_ORDEAL_ANNEX_8F          99000031
#define S_TOWER_OF_ORDEAL_ANNEX_9F          99000032
#define S_TOWER_OF_ORDEAL_ANNEX_10F         99000033
#define S_TOWER_OF_ORDEAL_ANNEX_11F         99000034
#define S_TOWER_OF_ORDEAL_ANNEX_12F         99000035
#define S_TOWER_OF_ORDEAL_ANNEX_13F         99000036
#define S_TOWER_OF_ORDEAL_ANNEX_TOP_FLOOR   99000037
#define TELEPORT_PRESET_COUNT                    104
#endif // _SF_SCENARIO


#ifndef _SF_TELEPORT_PRESET
#define _SF_TELEPORT_PRESET
typedef struct _Teleport_Preset_Info{
    __int32 Map_ID;
    __int32 Gate_ID;
    __int32 X;
    __int32 Y;
} Teleport_Preset_Info;



#endif // _SF_TELEPORT_PRESET


#endif /* SFHelperResource.h */