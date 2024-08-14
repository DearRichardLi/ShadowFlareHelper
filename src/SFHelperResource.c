#include <windows.h>
#include "SFHelperResource.h"
#include "SFHelperStd.h"

const Teleport_Preset_Info Teleport_Preset[TELEPORT_PRESET_COUNT] = {
      { // 0 
    S_NEAR_THE_REMOTE_TOWN,
    -1,
    97000, -4600
    }, { // 1 
    S_IRON_BORDERLINE,
    -1,
    67600, 16400
    }, { // 2 
    S_WASTELAND_OF_PILLARS,
    -1,
    22000, -16300
    }, { // 3 
    S_DUSTY_RUINS_CONTINUED_ROOM,
    -1,
    93000, 19000
    }, { // 4 
    S_DUSTY_RUINS_ROOM_OF_JUDGMENT,
    0,
    0, 0
    }, { // 5 
    S_NEAR_COLD_SVALT_TOWN,
    -1,
    80000, -11000
    }, { // 6 
    S_REMOTE_TOWN,
    -1,
    88800, 1300
    }, { // 7 
    S_COLD_RUINS_BOTTOM_FLOOR,
    0,
    0, 0
    }, { // 8 
    S_PURGATORY_OF_JUDGMENTS_RIGHT_WRONG_ROOM,
    1,
    0, 0
    }, { // 9 
    S_REMAINS_OF_REINCARNATION_BIG_HALL,
    1,
    0, 0
    }, { // 10 
    S_SEA_OF_TREES,
    0,
    0, 0
    }, { // 11 
    S_IMMORTAL_REMAINS_HEATED_HALL,
    1,
    0, 0
    }, { // 12 
    S_CARAVAN,
    0,
    0, 0
    }, { // 13 
    S_KANFORE_MINING_TOWN,
    50,
    0, 0
    }, { // 14 
    S_FOREST_OF_CLAWS,
    -1,
    43700, -5100
    }, { // 15 
    S_CROSS_AGORA,
    3,
    0, 0
    }, { // 16 
    S_TOWER_OF_THE_WIZARD_1F_TO_10F,
    -1,
    36000, 2000
    }, { // 17 
    S_FOREST_OF_KNIGHTS_MISERY,
    -1,
    43000, 14300
    }, { // 18 
    S_FOREST_OF_KNIGHTS_MISERY,
    2,
    0, 0
    }, { // 19 
    S_FORT_OF_THIEVES,
    2,
    0, 0
    }, { // 20 
    S_MINING_TUNNEL_OF_YUGUNOS_B2F,
    -1,
    17000, -200
    }, { // 21 
    S_UNDERGROUND_PASSAGE_B2F,
    -1,
    13700, 7200
    }, { // 22 
    S_UNDERGROUND_PASSAGE_B2F,
    -1,
    21800, -1800
    }, { // 23 
    S_MINING_TUNNEL_OF_YUGUNOS_B4F,
    -1,
    42800, -400
    }, { // 24 
    S_NEAR_THE_POWER_SUPPLY_FACILITY,
    -1,
    35000, -5000
    }, { // 25 
    S_FORT_OF_THE_POWER_SUPPLY,
    -1,
    26000, 9000
    }, { // 26 
    S_MINING_TUNNEL_OF_YUGUNOS_B5F,
    -1,
    20000, -3000
    }, { // 27 
    S_FOREST_OF_SILENCE,
    0,
    0, 0
    }, { // 28 
    S_FOREST_OF_SILENCE,
    -1,
    35500, -6000
    }, { // 29 
    S_WESLEY_CAVE,
    -1,
    18000, -4500
    }, { // 30 
    S_SOUTH_CAMP_OF_YUGUNOS,
    50,
    0, 0
    }, { // 31 
    S_THE_FOOT_OF_MT_TEDORON,
    -1,
    50000, -8000
    }, { // 32 
    S_TOWER_OF_NAZZLE_1F,
    -1,
    95000, -3000
    }, { // 33 
    S_A_TOWN_OF_ANTALUSIA,
    50,
    0, 0
    }, { // 34 
    S_TOWER_OF_NAZZLE_5F,
    -1,
    16000, 3500
    }, { // 35 
    S_UNDERGROUND_CAVE_OF_A_CHURCH,
    -1,
    7000, 1700
    }, { // 36 
    S_EAST_LOSMANS,
    -1,
    12000, 2500
    }, { // 37 
    S_THE_REMAINS_OF_HEARTBEAT,
    -1,
    25000, 9000
    }, { // 38 
    S_THE_GULF_OF_LUCENTIA,
    -1,
    59000, 20000
    }, { // 39 
    S_TOWN_OF_LOSMANS,
    -1,
    17000, 6600
    }, { // 40 
    S_TOWN_OF_LOSMANS,
    -1,
    30600, 8000
    }, { // 41 
    S_TOWER_OF_LICARN_1F,
    -1,
    15200, 1000
    }, { // 42 
    S_TOWER_OF_LICARN_5F,
    -1,
    15000, 0
    }, { // 43 
    S_DRAGON_CAVE__FOREST_OF_ILBARNA,
    -1,
    20000, 4500
    }, { // 44 
    S_ANCIENT_RUINS_B2F,
    -1,
    22000, 7000
    }, { // 45 
    S_PONSE_VILLAGE_OF_DWARVES,
    -1,
    12500, 2500
    }, { // 46 
    S_PONERO_CAVE__THE_MOLDONA_PENINSULA,
    -1,
    16000, -4000
    }, { // 47 
    S_SENAS_SMALL_SHRINE,
    -1,
    21500, 2000
    }, { // 48 
    S_THE_REMAINS_OF_THE_DEAD_CENTRAL_ROOM,
    -1,
    18500, 2000
    }, { // 49 
    S_TOWN_OF_LOSMANS,
    -1,
    26000, 7500
    }, { // 50 
    S_A_TOWN_OF_ANTALUSIA,
    -1,
    11000, 6200
    }, { // 51 
    S_TOWN_OF_CALADO,
    -1,
    13000, 800
    }, { // 52 
    S_PONSE_VILLAGE_OF_DWARVES,
    -1,
    11000, -2500
    }, { // 53 
    S_A_TOWN_OF_ANTALUSIA,
    -1,
    7000, 1500
    }, { // 54 
    S_FANANN_VILLAGE_OF_ELVES,
    -1,
    13000, -800
    }, { // 55 
    S_TOWN_OF_CALADO,
    -1,
    11500. -5500
    }, { // 56 
    S_DARK_ELVES_HIDING_PLACE,
    -1,
    12000, 1000
    }, { // 57 
    S_PONSE_VILLAGE_OF_DWARVES,
    -1,
    17000, 0
    }, { // 58 
    S_THE_WILDS_OF_DEATH_AND_DARKNESS,
    -1,
    24000, 4500
    }, { // 59 
    S_THE_RUINS_OF_ZERES__LUNAFULD_BEACH,
    -1,
    15500, 500
    }, { // 60 
    S_THE_RUINS_OF_LUKUNA__GOLAS_DESERT,
    -1,
    15500, -1500
    }, { // 61 
    S_LUNAFULD_BEACH,
    -1,
    64000, 7500
    }, { // 62 
    S_COLDEA_CAVE__MESRALD_BURIAL_GROUNDS,
    -1,
    23500, 6500
    }, { // 63 
    S_RUINS_OF_CARN__MESRALD_BURIAL_GROUNDS,
    -1,
    24500, -10500
    }, { // 64 
    S_GUNGSTONWALD,
    -1,
    40500, 5500
    }, { // 65 
    S_THE_ROAD_OF_ATONEMENT,
    -1,
    29500, 2500
    }, { // 66 
    S_THE_RUINS_OF_GOLDO__THE_ROAD_OF_ATONEMENT,
    -1,
    16500, 3000
    }, { // 67 
    S_THE_PLAIN_OF_DIALOSE,
    -1,
    58200, -5500
    }, { // 68 
    S_MERIA_RUIN__GORONABURB,
    -1,
    15500, -1700
    }, { // 69 
    S_THE_RUINS_OF_THE_LAKE__THE_PLAIN_OF_DIALOSE,
    -1,
    22500, -10300
    }, { // 70 
    S_SOUTH_ANTALUSIA,
    -1,
    58000, 9500
    }, { // 71 
    S_TOWN_OF_LOSMANS,
    -1,
    21000, -4000
    }, { // 72 
    S_TOWN_OF_CALADO,
    -1,
    9000, 4000
    }, { // 73 
    S_A_TOWN_OF_ANTALUSIA,
    -1,
    12000, 1500
    }, { // 74 
    S_PONSE_VILLAGE_OF_DWARVES,
    -1,
    16500, 13500
    }, { // 75 
    S_WHAM_CAVE__MESRALD_BURIAL_GROUNDS,
    -1,
    22500, 0
    }, { // 76 
    S_WEST_GATE_OF_CALADO,
    0,
    0, 0
    }, { // 77 
    S_THE_ANCIENT_INSTITUTE,
    -1,
    17000, 8500
    }, { // 78 
    S_THE_RUINS_OF_KASHUGAL,
    -1,
    22500, 2000
    }, { // 79 
    S_BERINI_VILLAGE,
    -1,
    11200, 1200
    }, { // 80 
    S_RUINS_OF_BERINI_VILLAGE,
    -1,
    22500, 2800
    }, { // 81 
    S_THE_CAVE_OF_RUINS_B2F,
    -1,
    9500, -300
    }, { // 82 
    S_SENAS_TOWER_5F,
    -1,
    1500, 3200
    }, { // 83 
    S_RUINS_OF_EXORCISM,
    -1,
    23000, -12500
    }, { // 84 
    S_FOREST_OF_DEATH,
    1,
    0, 0
    }, { // 85 
    S_GOLIATES_MANSION_B3F,
    -1,
    25000, 6500
    }, { // 86 
    S_DEVILS_CASTLE_4F,
    0,
    0, 0
    }, { // 87 
    S_PONSE_VILLAGE_OF_DWARVES,
    -1,
    10000, 1500
    }, { // 88 
    S_PONSE_VILLAGE_OF_DWARVES,
    -1,
    22300, 9000
    }, { // 89 
    S_THE_RUINS_OF_THE_WISE__GORONABURB,
    -1,
    7000, -400
    }, { // 90 
    S_TOWER_OF_REBELLION_4F,
    -1,
    17600, 3100
    }, { // 91 
    S_RUINS_OF_BERINI_VILLAGE,
    -1,
    22500, 2800
    }, { // 92 
    S_FOREST_OF_POISON,
    -1,
    48200, -11000
    }, { // 93 
    S_A_TOWN_OF_ANTALUSIA,
    -1,
    15200, 100
    }, { // 94 
    S_THE_RUINS_OF_REMOTENESS__MESRALD_BURIAL_GROUNDS,
    -1,
    17500, -200
    }, { // 95 
    S_FORT_OF_DEMON_B1F,
    -1,
    18000, -8500
    }, { // 96 
    S_FORT_OF_DEMON_B2F,
    -1,
    14500, 5500
    }, { // 97 
    S_REMOTE_TOWN,
    -1,
    88800, 1500
    }, { // 98 
    S_COLD_SVALT_TOWN,
    -1,
    91500, 2500
    }, { // 99 
    S_KANFORE_MINING_TOWN,
    -1,
    13900, 3700
    }, { // 100 
    S_FANANN_VILLAGE_OF_ELVES,
    -1,
    11800, 2400
    }, { // 101 
    S_TOWER_OF_ORDEAL_TOP_FLOOR,
    -1,
    12800, -1300
    }, { // 102 
    S_TOWER_OF_ORDEAL_ANNEX_13F,
    0,
    0, 0
    }, { // 103 
    S_TOWER_OF_ORDEAL_ANNEX_TOP_FLOOR,
    0,
    0, 0
    }
};

const __int32 Scenario_Map_ID[SCENARIO_COUNT] = {
             0
    ,        1
    ,        3
    ,        4
    ,        5
    ,        6
    ,    10000
    ,    10001
    ,    10002
    ,    10003
    ,    10004
    ,    10005
    ,  1000000
    ,  1000001
    ,  1000002
    ,  1000003
    ,  1000004
    ,  1020000
    ,  1020001
    ,  1020002
    ,  1030000
    ,  1030001
    ,  1030002
    ,  1040000
    ,  1040001
    ,  1040002
    ,  1050000
    ,  1050001
    ,  1050002
    ,  2000000
    ,  2000001
    ,  2010000
    ,  2100000
    ,  2100001
    ,  2100002
    ,  2100003
    ,  2100004
    ,  2100005
    ,  2100006
    ,  2110000
    ,  2120000
    ,  2120001
    ,  2130000
    ,  2140000
    ,  2200000
    ,  2200001
    ,  2200002
    ,  2200003
    ,  2200004
    ,  2200005
    ,  2210000
    ,  2210001
    ,  2210002
    ,  2210003
    ,  2210004
    ,  2220000
    ,  2220001
    ,  2230000
    ,  2240000
    ,  2240001
    ,  2250000
    ,  2999999
    ,  3000101
    ,  3000201
    ,  3000202
    ,  3000203
    ,  3000301
    ,  3000302
    ,  3000303
    ,  3000304
    ,  3000305
    ,  3000306
    ,  3000307
    ,  3000402
    ,  3000403
    ,  3000404
    ,  3000405
    ,  3000406
    ,  3000407
    ,  3000503
    ,  3000505
    ,  3000506
    ,  3000507
    ,  3010000
    ,  3010001
    ,  3010002
    ,  3010003
    ,  3010004
    ,  3020000
    ,  3020001
    ,  3020002
    ,  3020003
    ,  3020004
    ,  3030000
    ,  3040000
    ,  3050000
    ,  3060000
    ,  3070000
    ,  3080000
    ,  3090000
    ,  3100000
    ,  3110000
    ,  3110001
    ,  3110002
    ,  3110003
    ,  3110004
    ,  3120000
    ,  3130000
    ,  3140000
    ,  3140001
    ,  3150000
    ,  3160000
    ,  3170000
    ,  3180000
    ,  3190000
    ,  3200000
    ,  3210000
    ,  3220000
    ,  3230000
    ,  3240000
    ,  3900000
    ,  3900001
    ,  3900002
    ,  3900003
    ,  3900004
    ,  3900005
    ,  4000000
    ,  4000001
    ,  4000002
    ,  4000003
    ,  4000004
    ,  4000005
    ,  4000006
    ,  4000007
    ,  4000008
    ,  4000009
    ,  4010000
    ,  4020000
    ,  4030000
    ,  4040000
    ,  4050000
    ,  4050001
    ,  4020002
    ,  4060000
    ,  4060001
    ,  4060002
    ,  4060003
    ,  4060004
    ,  4060005
    ,  4060006
    ,  4070000
    ,  4070001
    ,  4080000
    ,  4080001
    ,  4080002
    ,  4080003
    ,  4080004
    ,  4090000
    ,  4090001
    ,  4090002
    ,  4090003
    ,  4100000
    ,  4110000
    ,  4120000
    ,  4120001
    ,  4130000
    ,  4140000
    ,  4900000
    ,  4900001
    ,  4900002
    ,  4900003
    , 99000000
    , 99000001
    , 99000002
    , 99000003
    , 99000004
    , 99000005
    , 99000006
    , 99000007
    , 99000008
    , 99000009
    , 99000010
    , 99000011
    , 99000012
    , 99000013
    , 99000014
    , 99000015
    , 99000016
    , 99000017
    , 99000018
    , 99000019
    , 99000020
    , 99000021
    , 99000022
    , 99000023
    , 99000024
    , 99000025
    , 99000026
    , 99000027
    , 99000028
    , 99000029
    , 99000030
    , 99000031
    , 99000032
    , 99000033
    , 99000034
    , 99000035
    , 99000036
    , 99000037
};

extern const Teleport_Preset_Info Teleport_Preset[TELEPORT_PRESET_COUNT];
extern const __int32 Scenario_Map_ID[SCENARIO_COUNT];