#include <Windows.h>

#include "SFHelperLanguage.h"

LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
    {    // 0 AWSTR_WNDNAME
L"神兵助手 by Richard",
L"神兵助手 by Richard",
L"ShadowFlare Helper by Richard",
    }, { // 1 AWSTR_MENU_OPTION
L"選項 (&O)",
L"选项 (&O)",
L"(&O)ption",
    }, { // 2 AWSTR_MENU_ABOUT
L"關於 (&A)",
L"关于 (&A)",
L"(&A)bout",
    }, { // 3 AWSTR_MENU_HIDE
L"隱藏到通知區域 (&I)",
L"隐藏到通知栏 (&I)",
L"H(&i)de to TaskBar",
    }, { // 4 AWSTR_MENU_EXIT
L"退出 (&X)",
L"退出 (&X)",
L"E(&x)it",
    }, { // 5 AWSTR_MENU_HELP
L"幫助 (&H)",
L"帮助 (&H)",
L"(&H)elp",
    }, { // 6 AWSTR_MENU_ABOUTAPP
L"關於神兵助手 (&S)",
L"关于神兵助手 (&S)",
L"About (&S)FHelper",
    }, { // 7 
L"",
L"",
L"",
    }, { // 8 
L"",
L"",
L"",
    }, { // 9 
L"",
L"",
L"",
    }, { // 10 AWSTR_TAB_INIT
L"初始化",
L"初始化",
L"Init",
    }, { // 11 AWSTR_TAB_WALLHACK
L"穿墻術",
L"穿墙术",
L"WallHack",
    }, { // 12 AWSTR_TAB_ASSIST
L"常用",
L"常用",
L"Assist",
    }, { // 13 AWSTR_TAB_MAGIC
L"魔法",
L"魔法",
L"Magic",
    }, { // 14 AWSTR_TAB_QUEST
L"任務",
L"任务",
L"Quest",
    }, { // 15 AWSTR_TAB_STATUS_1
L"屬性 1",
L"属性 1",
L"Status 1",
    }, { // 16 AWSTR_TAB_STATUS_2
L"屬性 2",
L"属性 2",
L"Status 2",
    }, { // 17 AWSTR_TAB_STATUS_3
L"屬性 3",
L"属性 3",
L"Status 3",
    }, { // 18 AWSTR_TAB_STATUS_4
L"屬性 4",
L"属性 4",
L"Status 4",
    }, { // 19 AWSTR_TAB_STATUS_5
L"屬性 5",
L"属性 5",
L"Status 5",
    }, { // 20 
L"",
L"",
L"",
    }, { // 21 
L"",
L"",
L"",
    }, { // 22 
L"",
L"",
L"",
    }, { // 23 
L"",
L"",
L"",
    }, { // 24 
L"",
L"",
L"",
    }, { // 25 
L"",
L"",
L"",
    }, { // 26 
L"",
L"",
L"",
    }, { // 27 
L"",
L"",
L"",
    }, { // 28 
L"",
L"",
L"",
    }, { // 29 
L"",
L"",
L"",
    }, { // 30 
L"",
L"",
L"",
    }, { // 31 AWSTR_APP_INIT_HELP
L"將\"SFHelper.exe\"檔案放入焰影神兵遊戲文件夾。\r\n\
開啟遊戲並讀檔後，在下拉框中選擇遊戲版本。\r\n\
點擊\"綁定遊戲\"。成功後即可開始修改。\r\n\
\r\n\
注意: 重啟遊戲或重新讀檔後，需要重新綁定遊戲。\r\n\
將間隔時間(單位: 毫秒)調至過低可能會導致CPU佔用率上升。\r\n",
L"将\"SFHelper.exe\"放入焰影神兵游戏文件夹。\r\n\
开启游戏并读档，在下拉框中选择游戏版本。\r\n\
点击\"绑定游戏\"。成功后即可开始修改。\r\n\
\r\n\
注意: 重启游戏或重新读档后，需要重新绑定游戏。\r\n\
将间隔时间(单位: 毫秒)调至过低可能会导致CPU占用率高。\r\n",
L"Put \"SFHelper.exe\" to your ShadowFLare Game Folder.\r\n\
Opening SF Game and Load your Savefile.\r\n\
Choose SF Version from ComboBox and \"Bind Game\"\r\n\
After Binding successfully, Hack functions unlock. \r\n\
\r\n\
ATTENTION: Re-Bind Game after you S/L Savefile.\r\n\
Set a low delay (unit: MilliSeconds) may cause high CPU usage.\r\n",
    }, { // 32 AWSTR_APP_WALLHACK_HELP
L"點擊全局鉤子開關以開啟鍵盤移動, 再次點擊可關閉。\r\n\
在遊戲內使用數字鍵盤/方向鍵進行移動。\r\n\
將間隔時間(單位: 毫秒)調至過低可能會導致CPU佔用率上升。",
L"点击全局钩子开关以开启键盘移动，再次点击可关闭。\r\n\
在游戏内使用小键盘/方向键以移动。\r\n\
将间隔时间(单位: 毫秒)调至过低可能会导致CPU占用率高。",
L"Click On/Off Button to enable WallHack. Click again to disable.\r\n\
Use Numpad/ Arrow key to move within game.\r\n\
Set a low delay (unit: MilliSeconds) may cause high CPU usage.",
    }, { // 33 AWSTR_APP_LOG_TO_FILE_FAIL
L"錯誤: 未能寫入日誌文件。",
L"错误: 未能写入日志文件。",
L"Err: Failed to print log to file.",
    },{ // 34 AWSTR_APP_SF_RUNNING
L"遊戲已經在運行了。",
L"游戏已经在运行了。",
L"Game already running.",
    }, { // 35 AWSTR_APP_SFEXE_NOT_FOUND
L"未找到Shadowflare.exe",
L"未找到Shadowflare.exe",
L"Err: ShadowFlare.exe not found.",
    }, { // 36 AWSTR_APP_SFEXE_FOUND
L"找到了遊戲，並嘗試打開。",
L"找到了游戏本体，并尝试运行。",
L"Find ShadowFlare.exe and try to open it.",
    }, { // 37 AWSTR_APP_GET_SFWND_FAIL
L"錯誤: 未能找到ShadowFlare窗口。",
L"错误: 未能找到ShadowFlare窗口。",
L"Err: ShadowFlare Game Window not found.",
    }, { // 38 AWSTR_APP_GET_TID_FAIL
L"錯誤: 未能獲得TID。",
L"错误: 未能获取TID。",
L"Err: Failed to get ShadowFlare TID.",
    }, { // 39 AWSTR_APP_GET_PID_FAIL
L"錯誤: 未能獲得PID。",
L"错误: 未能获取PID。",
L"Err: Failed to get ShadowFlare PID.",
    }, { // 40 AWSTR_APP_GET_HANDLE_FAIL
L"錯誤: 未能獲取ShadowFlare句柄。",
L"错误: 未能获取ShadowFlare句柄。",
L"Err: Failed to get ShadowFlare HANDLE.",
    }, { // 41 AWSTR_APP_GET_MODULE_FAIL
L"錯誤: 未能獲取各模塊加載基址。",
L"错误: 未能获取各模块加载基址。",
L"Err: Failed to get Process Modules.",
    }, { // 42 AWSTR_APP_GET_SFWND_SUC
L"找到了ShadowFlare窗口: ",
L"找到了ShadowFlare窗口: ",
L"ShadowFlare Window located at: ",
    }, { // 43 AWSTR_APP_GET_TID_SUC
L"獲得了TID: ",
L"已获取TID: ",
L"TID obtained. TID: ",
    }, { // 44 AWSTR_APP_GET_PID_SUC
L"獲得了PID: ",
L"已获取PID: ",
L"PID obtained. PID: ",
    }, { // 45 AWSTR_APP_GET_HANDLE_SUC
L"獲得了進程句柄: ",
L"已获取进程句柄: ",
L"Handle obtained. HANDLE: ",
    }, { // 46 AWSTR_APP_GET_MODULE_SUC
L"獲得了程式各個模塊基址。",
L"获取各模块加载基址。",
L"Module base addr obtained.",
    }, { // 47 AWSTR_APP_SF_BASE_ADDR
L"ShadowFlare.exe基址位於: ",
L"ShadowFlare.exe基址位于: ",
L"Base address of Shadowflare.exe: ",
    }, { // 48 AWSTR_APP_SF_BIND_SUC
L"綁定成功!",
L"绑定成功!",
L"Bind Game success!",
    }, { // 49 AWSTR_APP_READ_MEMORY_FAIL
L"錯誤: 讀內存失敗。",
L"错误: 读取内存失败。",
L"Err: Failed to read memory.",
    }, { // 50 AWSTR_APP_WRITE_MEMORY_FAIL
L"錯誤: 寫內存失敗。",
L"错误: 写入内存失败。",
L"Err: Failed to write memory.",
    }, { // 51 AWSTR_APP_HINT_ONLINE_RISKY
L"敬告: 聯網遊戲中，部分功能可能不生效/不穩定/有延遲/導致閃退。\r\n",
L"敬告: 在联机游戏时，部分功能可能不生效/不稳定/有延迟/导致闪退。\r\n",
L"Tip: As your role is Online-Client, some functions may be\r\n\
risky/unstable/delayed/ineffective.\r\n",
    }, { // 52 AWSTR_APP_PERMISSION_DENIED
L"錯誤: 權限不足。請以管理員權限重啟神兵助手。",
L"错误: 权限不足。请以管理员权限重启神兵助手。",
L"Err: Permission denied. Please restart SFHelper as Administrator.",
    }, { // 53 AWSTR_APP_STRING_OVERFLOW
L"提示: 字符串過長。溢出部分已捨棄。",
L"提示: 字符串过长。溢出部分已舍弃。",
L"Notice: String too long. Discard out-of-bound characters.",
    }, { // 54 AWSTR_APP_HINT_RELOAD_SAVEFILE
L"敬告: 重新讀檔以使性別/同伴ID修改生效。",
L"敬告: 重新读档以使性别/同伴ID修改生效。",
L"Tip: S/L Savefile to refresh your Sex/Comp.ID.",
    }, { // 55 AWSTR_APP_KEYBOARD_HOOK_FAIL
L"錯誤: 設置鍵盤鉤子失敗。",
L"错误: 设置键盘钩子失败。",
L"Err: Failed to set keyboard Hook.",
    }, { // 56 AWSTR_APP_CREATE_THREAD_FAIL
L"錯誤: 創建線程失敗。",
L"错误: 创建线程失败。",
L"Err: Failed to create thread.",
    }, { // 57 AWSTR_APP_JOIN_THREAD_FAIL
L"錯誤: 終止線程失敗。",
L"错误: 终止线程失败。",
L"Err: Failed to join thread.",
    }, { // 58 AWSTR_APP_HOOK_ON
L"設置鉤子成功。",
L"设置钩子成功。",
L"Hook On!",
    }, { // 59 AWSTR_APP_HOOK_OFF
L"解除鉤子成功。",
L"解除钩子成功。",
L"Hook Off!",
    }, { // 60 AWSTR_APP_SF_CLOSED
L"檢測到遊戲已關閉。",
L"检测到游戏已关闭。",
L"ShadowFlare is closed.",
    }, { // 61 AWSTR_APP_SF_LOGOUT
L"檢測到遊戲已登出存檔。",
L"检测到游戏已登出存档。",
L"ShadowFlare player logged out.",
    }, { // 62 AWSTR_APP_SF_NOT_LOGIN
L"檢測到遊戲還未讀檔。",
L"检测到游戏还未读档。",
L"ShadowFlare Savefile not logged in.",
    }, { // 63 AWSTR_APP_REFRESH_ON
L"數據同步已開啟。",
L"数据同步已开启。",
L"Refresh On!",
    }, { // 64 AWSTR_APP_REFRESH_OFF
L"數據同步已關閉。",
L"数据同步已关闭。",
L"Refresh Off!",
    }, { // 65 
L"",
L"",
L"",
    }, { // 66 
L"",
L"",
L"",
    }, { // 67 
L"",
L"",
L"",
    }, { // 68 
L"",
L"",
L"",
    }, { // 69 
L"",
L"",
L"",
    }, { // 70 
L"",
L"",
L"",
    }, { // 71 
L"",
L"",
L"",
    }, { // 72 
L"",
L"",
L"",
    }, { // 73 
L"",
L"",
L"",
    }, { // 74 
L"",
L"",
L"",
    }, { // 75 
L"",
L"",
L"",
    }, { // 76 
L"",
L"",
L"",
    }, { // 77 
L"",
L"",
L"",
    }, { // 78 
L"",
L"",
L"",
    }, { // 79 
L"",
L"",
L"",
    }, { // 80 AWSTR_CTL_B_CHANGE_LANG
L"Change APP Language to Simplified Chinese (简体中文)",
L"Change APP Language to English (英语)",
L"將程式語言設定為繁體中文 (Traditional Chinese)",
    }, { // 81 AWSTR_CTL_B_OPENSF
L"運行遊戲",
L"运行游戏",
L"Run Game",
    }, { // 82 AWSTR_CTL_B_BIND_GAME
L"綁定遊戲",
L"绑定游戏",
L"Bind Game",
    }, { // 83 AWSTR_CTL_B_REFRESH
L"數據刷新開關",
L"数据刷新开关",
L"Refresh Data On/Off",
    }, { // 84 AWSTR_CTL_S_REFRESH_DELAY
L"數據刷新間隔時間:",
L"数据刷新间隔时间:",
L"Refresh Delay Time:",
    }, { // 85 AWSTR_CTL_S_GAMEMODE
L"遊戲模式:",
L"游戏模式:",
L"Game Mode:",
    }, { // 86 AWSTR_CTL_E_GAMEMODE_SINGLE
L"單人",
L"单机",
L"Single Game",
    }, { // 87 AWSTR_CTL_E_GAMEMODE_ONLINE
L"聯網",
L"联机",
L"Online Game",
    }, { // 88 AWSTR_CTL_S_ONLINEROLE
L"網路職能:",
L"联机职责:",
L"Online Role:",
    }, { // 89 AWSTR_CTL_S_PLAYER_NAME
L"角色名:",
L"角色名:",
L"Name:",
    }, { // 90 AWSTR_CTL_B_APPLY
L"確認",
L"确认",
L"Apply",
    }, { // 91 AWSTR_CTL_S_LV
L"LV:",
L"LV:",
L"LV:",
    }, { // 92 AWSTR_CTL_S_SEX
L"性別:",
L"性别:",
L"Sex:",
    }, { // 93 AWSTR_CTL_S_EXP
L"經驗:",
L"经验:",
L"Exp:",
    }, { // 94 AWSTR_CTL_S_PROF
L"職業:",
L"职业:",
L"Prof:",
    }, { // 95 AWSTR_CTL_S_PROF_TO_BE
L"將轉職為:",
L"将转职为:",
L"Prof To Be:",
    }, { // 96 AWSTR_CTL_S_COMPANION_LV
L"隊友等級:",
L"队友等级:",
L"Comp LV:",
    }, { // 97 AWSTR_CTL_S_COMPANION_ID
L"隊友ID:",
L"队友ID:",
L"Comp ID:",
    }, { // 98 AWSTR_CTL_S_COMPANION_EXP
L"隊友經驗:",
L"队友经验:",
L"Comp Exp:",
    }, { // 99 AWSTR_CTL_B_HOOK
L"全局鉤子開關",
L"全局钩子开关",
L"Global Hook On/Off",
    }, { // 100 AWSTR_CTL_S_HOOK_STATUS
L"鉤子狀態:",
L"钩子状态:",
L"Hook Status:",
    }, { // 101 AWSTR_CTL_E_HOOK_STATUS_ON
L"開",
L"开",
L"On",
    }, { // 102 AWSTR_CTL_E_HOOK_STATUS_OFF
L"關",
L"关",
L"Off",
    }, { // 103 AWSTR_CTL_S_MAP_ID
L"地圖ID:",
L"地图ID:",
L"Map ID:",
    }, { // 104 AWSTR_CTL_S_X
L"X:",
L"X:",
L"X:",
    }, { // 105 AWSTR_CTL_S_Y
L"Y:",
L"Y:",
L"Y:",
    }, { // 106 AWSTR_CTL_S_MOVE_DISTANCE
L"移動距離:",
L"移动距离:",
L"Move Dist.:",
    }, { // 107 AWSTR_CTL_S_MOVE_DELAY
L"移動間隔時間:",
L"移动间隔时间:",
L"Move Delay Time:",
    }, { // 108 
L"",
L"",
L"",
    }, { // 109 
L"",
L"",
L"",
    }, { // 110 
L"",
L"",
L"",
    }
 
};

LPCWSTR APP_WSTR_SEX[APP_WSTR_SEX_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 AWSTR_SEX_FEMALE
L"女",
L"女",
L"Female",
    }, { // 1 AWSTR_SEX_MALE
L"男",
L"男",
L"Male",
    }
};
LPCWSTR APP_WSTR_PROF[APP_WSTR_PROF_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 AWSTR_PROF_GUNNER
L"砲手",
L"炮手",
L"Gunner",
    }, { // 1 AWSTR_PROF_THIFE
L"盜賊",
L"盗贼",
L"Thife",
    }, { // 2 AWSTR_PROF_NINJA
L"忍者",
L"忍者",
L"Ninja",
    }, { // 3 AWSTR_PROF_SAVAGE
L"野蠻人",
L"野蛮人",
L"Savage",
    }, { // 4 AWSTR_PROF_ASSASSIN
L"刺客",
L"刺客",
L"Assassin",
    }, { // 5 AWSTR_PROF_HUNTER
L"獵人",
L"猎人",
L"Hunter",
    }, { // 6 AWSTR_PROF_SWORDMAN
L"劍士",
L"剑士",
L"Swordman",
    }, { // 7 AWSTR_PROF_WARRIOR
L"戰士",
L"战士",
L"Warrior",
    }, { // 8 AWSTR_PROF_BLACKMAGE
L"黑魔導師",
L"黑魔法师",
L"Black Mage",
    }, { // 9 AWSTR_PROF_WITCH
L"魔導師",
L"魔法师",
L"Witch",
    }, { // 10 AWSTR_PROF_SPELLSWORD
L"魔劍士",
L"魔剑士",
L"Spellsword",
    }, { // 11 AWSTR_PROF_KNIGHT
L"騎士",
L"骑士",
L"Knight",
    }, { // 12 AWSTR_PROF_SAGE
L"賢者",
L"贤者",
L"Sage",
    }, { // 13 AWSTR_PROF_MONK
L"僧侶",
L"僧侣",
L"Monk",
    }, { // 14 AWSTR_PROF_SAMURAI
L"武士",
L"武士",
L"Samurai",
    }, { // 15 AWSTR_PROF_SAINTKNIGHT
L"聖騎士",
L"圣骑士",
L"Saint Knight",
    }, { // 16 AWSTR_PROF_MERCENARY
L"傭兵",
L"佣兵",
L"Mercenary",
    }
};
LPCWSTR APP_WSTR_COMP[APP_WSTR_COMP_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 AWSTR_COMP_KERBEROS
L"0 克爾貝羅斯",
L"0 克尔贝罗斯",
L"0 Kerberos",
    }, { // 1 AWSTR_COMP_GRAVITY
L"1 格拉比提",
L"1 格拉比提",
L"1 Gravity",
    }, { // 2 AWSTR_COMP_DUNE
L"2 迪恩",
L"2 迪恩",
L"2 Dune",
    }, { // 3 AWSTR_COMP_FANG
L"3 芳格",
L"3 芳格",
L"3 Fang",
    }, { // 4 AWSTR_COMP_HARLEY
L"4 哈雷",
L"4 哈雷",
L"4 Harley",
    }, { // 5 AWSTR_COMP_HAWK
L"5 霍克",
L"5 霍克",
L"5 Hawk",
    }
};

extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SEX[APP_WSTR_SEX_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_PROF[APP_WSTR_PROF_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_COMP[APP_WSTR_COMP_COUNT][AVAILABLE_LANGUAGE_COUNT];




