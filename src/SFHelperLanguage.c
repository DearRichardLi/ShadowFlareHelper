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
    }, { // 7 AWSTR_MENU_ADDRESS
L"開源項目地址 (&G)",
L"开源项目地址 (&G)",
L"(&G)itHub Address",
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
    }, { // 15 AWSTR_TAB_G_WAREHOUSE
L"大倉庫",
L"大仓库",
L"G_Warehouse",
    }, { // 16 AWSTR_TAB_TELEPORT_GATE
L"傳送門",
L"传送门",
L"Teleport Gate",
    }, { // 17 AWSTR_TAB_STATUS_1
L"屬性 1",
L"属性 1",
L"Status 1",
    }, { // 18 AWSTR_TAB_STATUS_2
L"屬性 2",
L"属性 2",
L"Status 2",
    }, { // 19 AWSTR_TAB_STATUS_3
L"屬性 3",
L"属性 3",
L"Status 3",
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
L"將\"SFHelper.exe\" \"libwinpthread-1.dll\"放入焰影神兵遊戲文件夾。\r\n\
開啟遊戲並讀檔後，在下拉框中選擇遊戲版本。\r\n\
點擊\"綁定遊戲\"。成功後即可開始修改。\r\n\
\r\n\
注意: 重啟遊戲或重新讀檔後，需要重新綁定遊戲。\r\n\
將間隔時間(單位: 毫秒)調至過低可能會導致CPU佔用率上升。\r\n",
L"将\"SFHelper.exe\" \"libwinpthread-1.dll\"放入焰影神兵游戏文件夹。\r\n\
开启游戏并读档，在下拉框中选择游戏版本。\r\n\
点击\"绑定游戏\"。成功后即可开始修改。\r\n\
\r\n\
注意: 重启游戏或重新读档后，需要重新绑定游戏。\r\n\
将间隔时间(单位: 毫秒)调至过低可能会导致CPU占用率高。\r\n",
L"Put \"SFHelper.exe\" \"libwinpthread-1.dll\" to your ShadowFLare Game Folder.\r\n\
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
    }, { // 65 AWSTR_APP_HINT_ASSIST
L"沒關就是開了? 小開不算開!\r\n\
部分功能會在裝備產生變動後自動失效，需重新激活。\r\n\
敬請自由探索。\r\n",
L"没关就是开了? 小开不算开!\r\n\
部分功能会在装备产生变动后自动失效，需重新激活。\r\n\
敬请自由探索。\r\n",
L"Some functions need to be Re-actived \r\n\
after changing your equiqment.\r\n\
Have fun!\r\n",
    }, { // 66 AWSTR_APP_CURSOR_NULL
L"沒有手持任何物品。",
L"没有手持任何物品。",
L"No Item holding in Cursor.",
    }, { // 67 AWSTR_APP_BE_RICH_NOT_MONEY
L"手持的不是Gold。",
L"手持的不是Gold。",
L"Item holding in Cursor is not money.",
    }, { // 68 AWSTR_APP_HINT_G_WAREHOUSE
L"點擊按鈕解鎖/禁用對應的大倉庫頁面。\r\n\
\"當前頁面編號\"的範圍為[0 - 13; 25 - 479], \r\n\
其中[0 - 9]分別對應10頁大倉庫;\r\n\
[10 - 13]頁對應特殊物品頁([X])的四部分內容。\r\n\
這4頁也可以用來存物品但不推薦,\r\n\
因為會導致特殊物品頁([X])顯示異常。\r\n\
[25 - 479]頁為隱藏頁, 其內存儲的物品會在[關閉遊戲]後全部清除。\r\n\
但是你可以用這個功能在不同存檔之間傳遞裝備(返回主菜單時物品不清空)。",
L"点击按钮解锁/禁用对应的大仓库页面。\r\n\
\"当前页面编号\"的范围为[0 - 13; 25 - 479], \r\n\
其中[0 - 9]分别对应10页大仓库;\r\n\
[10 - 13]页对应特殊物品页([X])的四部分内容。\r\n\
这4页也可以用来存物品但不推荐,\r\n\
因为会导致特殊物品页([X])的显示异常。\r\n\
[25 - 479]页为隐藏页, 其内存储的物品会在[关闭游戏]后全部清除。\r\n\
但是你可以用这个功能在不同存档之间传递装备(返回主菜单时物品不清空)。\r\n",
L"Click a button to Lock/Unlock a page of Giant Warehouse.\r\n\
The Range of \"Current G_Warehouse Page\" is [0 - 13; 25 - 479].\r\n\
Among them, [0 - 9] correspond to 10 pages of G_Warehouse,\r\n\
[10 - 13] correspond to 4 sections in 'Special Item ([X])' Tab.\r\n\
These 4 pages could also be used to store Item, but not suggested.\r\n\
Because this cause abnormal displaying in 'Special Item ([X])' Tab.\r\n\
[25 - 479] is considered as hidden pages.\r\n\
Items in these pages will DISAPPEAR after EXIT GAME.\r\n\
We could use these pages to deliver Items across different Savefiles.\r\n",
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
    }, { // 79 AWSTR_APP_SFHELPER_ADDRESS
L"開源項目地址: https://github.com/DearRichardLi/ShadowFlareHelper",
L"开源项目地址: https://github.com/DearRichardLi/ShadowFlareHelper",
L"GitHub Address: https://github.com/DearRichardLi/ShadowFlareHelper",
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
    }, { // 106 AWSTR_CTL_S_MAP_GATE_ID
L"門ID:",
L"门ID:",
L"Gate ID:",
    }, { // 107 AWSTR_CTL_S_MOVE_DISTANCE
L"單次移動距離:",
L"单次移动距离:",
L"Move Distance:",
    }, { // 108 AWSTR_CTL_S_MOVE_DELAY
L"移動間隔時間:",
L"移动间隔时间:",
L"Move Delay:",
    }, { // 109 AWSTR_CTL_S_TELEPORT
L"任意門:",
L"任意门:",
L"Teleport:",
    }, { // 110 AWSTR_CTL_S_TELEPORT_MAP_ID
L"地圖ID:",
L"地图ID:",
L"Map ID:",
    }, { // 111 AWSTR_CTL_G_GATEORXY
L"傳送模式選擇",
L"传送模式选择",
L"Teleport Mode Choice",
    }, { // 112 AWSTR_CTL_B_R_GATE
L"門ID模式",
L"门ID模式",
L"Gate ID Mode",
    }, { // 113 AWSTR_CTL_B_R_XY
L"坐標模式",
L"坐标模式",
L"X/Y Mode",
    }, { // 114 AWSTR_CTL_S_TELEPORT_GATE_ID
L"門ID:",
L"门ID:",
L"Gate ID:",
    }, { // 115 AWSTR_CTL_S_TELEPORT_GATE_WARN
L"門ID填錯會導致遊戲閃退!",
L"门ID填错会导致游戏闪退!",
L"Wrong ID Cause Game CRASH!",
    }, { // 116 AWSTR_CTL_S_TELEPORT_X
L"X:",
L"X:",
L"X:",
    }, { // 117 AWSTR_CTL_S_TELEPORT_Y
L"Y:",
L"Y:",
L"Y:",
    }, { // 118 AWSTR_CTL_B_TELEPORT
L"一鍵傳送!",
L"一键传送!",
L"Teleport me!",
    }, { // 119 AWSTR_CTL_B_OPEN_WAREHOUSE
L"打開倉庫頁",
L"打开仓库页",
L"Open Warehouse Tab",
    }, { // 120 AWSTR_CTL_B_OPEN_G_WAREHOUSE
L"打開大倉庫頁",
L"打开大仓库页",
L"Open Giant Warehouse Tab",
    }, { // 121 AWSTR_CTL_B_OPEN_CUSTOM_OUTFIT
L"打開自定義裝備配色頁",
L"打开自定义装备配色页",
L"Open Custom Outfit Tab",
    }, { // 122 AWSTR_CTL_B_PAUSE_GAME
L"暫停遊戲",
L"暂停游戏",
L"PAUSE GAME",
    }, { // 123 AWSTR_CTL_B_INFINITE_POWER
L"無限暴走 [P]",
L"无限暴走 [P]",
L"Infinite [P]ower",
    }, { // 124 AWSTR_CTL_B_COMP_REVIVE
L"同伴立刻復活",
L"同伴立刻复活",
L"Companion Revive",
    }, { // 125 AWSTR_CTL_B_EX_LANDMINE
L"額外地雷個數",
L"额外地雷个数",
L"Extra Landmine Limit",
    }, { // 126 AWSTR_CTL_B_EX_LANDMINE_POWER
L"額外地雷威力",
L"额外地雷威力",
L"Extra Landmine Power",
    }, { // 127 AWSTR_CTL_B_BE_RICH
L"變有錢 (需要手持Gold)",
L"变有钱 (需要手持Gold)",
L"Be RICH (Cursor Hold Gold)",
    }, { // 128 AWSTR_CTL_B_NO_MONSTER
L"關閉敵人顯示與AI",
L"关闭敌人显示与AI",
L"Close Enemy Display and AI",
    }, { // 129 AWSTR_CTL_B_MAGIC_TO_30
L"魔法一鍵30級 (非永久)",
L"魔法一键30级 (非永久)",
L"Magic LV30 (Not permanent)",
    }, { // 130 AWSTR_CTL_B_CRAZY_SPEED
L"瘋狂移速",
L"疯狂移速",
L"Crazy Walking Speed",
    }, { // 131 AWSTR_CTL_B_GOD_MODE
L"屬性無敵",
L"属性无敌",
L"Invincible Status",
    }, { // 132 AWSTR_CTL_B_EXTEND_ATK_RANGE
L"攻擊距離拉滿",
L"攻击距离拉满",
L"Extend Swordman Atk Range",
    }, { // 133 AWSTR_CTL_B_REVIVE_ENEMY
L"復活所有敵人 (先任意切換個地圖再點按鈕)",
L"复活所有敌人 (先任意切换个地图再点按钮)",
L"Revive Enemy (Switch to any map, then click)",
    }, { // 134 AWSTR_CTL_B_SUICIDE
L"原 地 自 殺",
L"原 地 自 尽",
L"S-U-I-C-I-D-E",
    }, { // 135 AWSTR_CTL_S_MAGIC_NAME
L"魔法名稱",
L"魔法名称",
L"Magic Name",
    }, { // 136 AWSTR_CTL_S_MAGIC_LV
L"LV",
L"LV",
L"LV",
    }, { // 137 AWSTR_CTL_S_MAGIC_EXP
L"EXP",
L"EXP",
L"EXP",
    }, { // 138 AWSTR_CTL_G_MAGIC_PAGE_1
L"第1頁魔法",
L"第1页魔法",
L"Magic Page 1",
    }, { // 139 AWSTR_CTL_G_MAGIC_PAGE_2
L"第2頁魔法",
L"第2页魔法",
L"Magic Page 2",
    }, { // 140 AWSTR_CTL_G_MAGIC_PAGE_3
L"第3頁魔法",
L"第3页魔法",
L"Magic Page 3",
    }, { // 141 AWSTR_CTL_G_MAGIC_PAGE_4
L"第4頁魔法",
L"第4页魔法",
L"Magic Page 4",
    }, { // 142 AWSTR_CTL_S_QUEST_COL_1
L"第1列",
L"第1列",
L"Column 1",
    }, { // 143 AWSTR_CTL_S_QUEST_COL_2
L"第2列",
L"第2列",
L"Column 2",
    }, { // 144 AWSTR_CTL_S_QUEST_COL_3
L"第3列",
L"第3列",
L"Column 3",
    }, { // 145 AWSTR_CTL_S_QUEST_COL_4
L"第4列",
L"第4列",
L"Column 4",
    }, { // 146 AWSTR_CTL_G_QUEST_PAGE_1
L"第1頁任務",
L"第1页任务",
L"Quest Page 1",
    }, { // 147 AWSTR_CTL_G_QUEST_PAGE_2
L"第2頁任務",
L"第2页任务",
L"Quest Page 2",
    }, { // 148 AWSTR_CTL_G_G_WAREHOUSE
L"解鎖大倉庫",
L"解锁大仓库",
L"Unlock Giant Warehouse",
    }, { // 149 AWSTR_CTL_S_G_WAREHOUSE_INDEX
L"目前大倉庫頁面編號 (范围: 0-13; 25-479):",
L"当前大仓库页面编号 (范围: 0-13; 25-479):",
L"Current G_Warehouse Page (Range: 0-13; 25-479):",
    }, { // 150 
L"",
L"",
L"",
    }, { // 151 
L"",
L"",
L"",
    }, { // 152 
L"",
L"",
L"",
    }, { // 153 
L"",
L"",
L"",
    }, { // 154 
L"",
L"",
L"",
    }, { // 155 
L"",
L"",
L"",
    }, { // 156 
L"",
L"",
L"",
    }, { // 157 
L"",
L"",
L"",
    }, { // 158 
L"",
L"",
L"",
    }, { // 159 
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
LPCWSTR APP_WSTR_TELEPORT_PRESET[APP_WSTR_TELEPORT_PRESET_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 
L"邊境之鎮周邊 - 紅哥布林",
L"边境之镇周边 - 红哥布林",
L"Near the Remote Town - Red Goblin",
    }, { // 1 
L"鐵之邊境 - [馬爾斯的寶石]",
L"铁之边境 - [马尔斯的宝石]",
L"Iron Boundary Line - [Malse's Gem]",
    }, { // 2 
L"石柱荒地 - 藍裝商人",
L"石柱荒地 - 蓝装商人",
L"Wasteland of Pillars - Blue Item Shop",
    }, { // 3 
L"塵土遺跡 連接的房間 - [絲莉亞的精靈石]",
L"尘土遗迹 连接的房间 - [丝莉亚的精灵石]",
L"Dusty Ruins, Continued Room - [Syria's Spirit Stone]",
    }, { // 4 
L"塵土遺跡 審判室",
L"尘土遗迹 审判室",
L"Dusty Ruins, Room of Judgment",
    }, { // 5 
L"寒冰暗妖精鎮周邊 - [回憶之紅寶石]",
L"寒冰暗妖精镇周边 - [回忆之红宝石]",
L"Near Cold Svalt Town - [Memorable Ruby]",
    }, { // 6 
L"邊境之鎮 - 幫格多跑腿",
L"边境之镇 - 帮格多跑腿",
L"Remote Town - Errand for Gedo",
    }, { // 7 
L"冰冷遺跡 最底層",
L"冰冷遗迹 最底层",
L"Cold Ruins, Bottom Floor",
    }, { // 8 
L"判決煉獄 是非之室 入口",
L"判决炼狱 是非之室 入口",
L"Purgatory of Judgments, Right/Wrong Room",
    }, { // 9 
L"輪迴遺跡 大廳 入口",
L"轮回遗迹 大厅 入口",
L"Remains of Reincarnation, Big Hall Entrance",
    }, { // 10 
L"樹海 不死的遺跡門口 - 任務觸發",
L"树海 不死的遗迹门口 - 任务触发",
L"Sea of Trees - Immortal Remains - Quest Trigger",
    }, { // 11 
L"不死的遺跡 絕望的通路",
L"不死的遗迹 绝望的通路",
L"Immortal Remains, Hopeless Road",
    }, { // 12 
L"========商隊 - 開啟第二話========",
L"========商队 - 开启第二话========",
L"========Caravan - EP.2 ========",
    }, { // 13 
L"煤礦之鎮 剛弗雷",
L"煤矿之镇 刚弗雷",
L"Kanfore, Mining Town",
    }, { // 14 
L"鉤爪之森 - 消滅盜賊團",
L"钩爪之森 - 消灭盗贼团",
L"Forest of Claws, Destory thieves",
    }, { // 15 
L"十字礦場 進入精靈之村之前 - 任務觸發",
L"十字矿场 进入精灵之村之前 - 任务触发",
L"Cross Agora - before Village of Elves - Quest Trigger",
    }, { // 16 
L"魔導師之塔 10F - 晉見魔導師吉爾修塔德",
L"魔导师之塔 10F - 晋见魔导师吉尔修塔德",
L"Tower of the Wizard, 10F - Meet Wizard Kirushutat",
    }, { // 17 
L"悲哀騎士森林 盜賊的碉堡 - 劇情觸發",
L"悲哀骑士森林 盗贼的碉堡 - 剧情触发",
L"Forest of Knight's Misery - Fort of Thieves - Quest Trigger",
    }, { // 18 
L"悲哀騎士森林 - 盜賊的碉堡內部通路入口",
L"悲哀骑士森林 - 盗贼的碉堡内部通路入口",
L"Forest of Knight's Misery - Fort of Thieves, a Back Street",
    }, { // 19 
L"盜賊的碉堡 - [封印的水晶]",
L"盗贼的碉堡 - [封印的水晶]",
L"Fort of Thieves - [Seal Crystal]",
    }, { // 20 
L"優格諾斯坑道 地下二樓 - 任務觸發",
L"优格诺斯坑道 地下二楼 - 任务触发",
L"Mining Tunnel of Yugunos, B2F - Quest Trigger",
    }, { // 21 
L"地下道 地下二樓 - 奪回防護控制設施",
L"地下道 地下二楼 - 夺回防护控制设施",
L"Underground Passage, B2F - Security & Control Facility",
    }, { // 22 
L"地下道 地下二樓 - 箱子",
L"地下道 地下二楼 - 箱子",
L"Underground Passage, B2F - Tresure Boxes",
    }, { // 23 
L"優格諾斯坑道 地下四樓 - 任務觸發",
L"优格诺斯坑道 地下四楼 - 任务触发",
L"Mining Tunnel of Yugunos, B4F - Quest Trigger",
    }, { // 24 
L"電源設施周邊 - 死亡二選一",
L"电源设施周边 - 死亡二选一",
L"Around the Power Supply Facility - Deadly Choice",
    }, { // 25 
L"電源碉堡",
L"电源碉堡",
L"Power Supply Fort",
    }, { // 26 
L"優格諾斯坑道 地下五樓 - 打倒巨龍",
L"优格诺斯坑道 地下五楼 - 打倒巨龙",
L"Mining Tunnel of Yugunos, B5F - Defeat the Dragon!",
    }, { // 27 
L"寂靜之森 - 入口",
L"寂静之森 - 入口",
L"Forest of Silence - Entrance",
    }, { // 28 
L"寂靜之森 - 剷除惡魔蜘蛛",
L"寂静之森 - 铲除恶魔蜘蛛",
L"Forest of Silence - Kill the Tarantulas.",
    }, { // 29 
L"威斯雷洞窟 - 尋找[非法的證據]",
L"威斯雷洞窟 - 寻找[非法的证据]",
L"Wesley Cave - [Evidence of Injustice]",
    }, { // 30 - 
L"========優格諾斯南方軍營 - 開啟第三話========",
L"========优格诺斯南方军营 - 开启第三话========",
L"========South Camp of Yugunos - EP.3 ========",
    }, { // 31 
L"德多隆山麓 - 消滅餘黨",
L"德多隆山麓 - 消灭余党",
L"South Camp of Yugunos - Sweep vicinity",
    }, { // 32 
L"納茲爾之塔 1樓 - 任務觸發",
L"那兹尔之塔 1楼 - 任务触发",
L"Tower of Nazzle, 1F - Quest Trigger",
    }, { // 33 
L"安德魯雪鎮",
L"安德鲁雪镇",
L"Town of Antalusia",
    }, { // 34 
L"納茲爾之塔 5樓 - [神聖之羽毛]",
L"那兹尔之塔 5楼 - [神圣之羽毛]",
L"Tower of Nazzle, 5F - [Sacred Wing]",
    }, { // 35 
L"教會地下洞窟 - [天使之發]",
L"教会地下洞窟 - [天使之发]",
L"Underground Cave of a Church - [Angle's Hair]",
    }, { // 36 
L"羅斯曼茲鎮東方 - 進入羅斯曼茲鎮之前 - 任務觸發",
L"罗斯曼兹镇东方 - 进入罗斯曼兹镇之前 - 任务触发",
L"East Losmans - before Town of Losmans - Quest Trigger",
    }, { // 37 
L"鼓動之遺跡",
L"鼓动之遗迹",
L"The Remains of Heartbeat",
    }, { // 38 
L"隆賽迪雅灣 - 鎮壓配管設施",
L"隆赛迪雅湾 - 镇压配管设施",
L"The Gulf of Lucentia - Examine the plumbing",
    }, { // 39 
L"羅斯曼茲鎮 - 帕西巴爾",
L"罗斯曼兹镇 - 帕西巴尔",
L"Town of Losmans - Barshival",
    }, { // 40 
L"羅斯曼茲鎮 - 晉見聖騎士萊鋼 - 任務觸發",
L"罗斯曼兹镇 - 晋见圣骑士莱钢 - 任务触发",
L"Town of Losmans - Saint Knight Licarn - Quest Trigger",
    }, { // 41 
L"萊剛之塔 1F",
L"莱刚之塔 1F",
L"Tower of Licarn, 1F",
    }, { // 42 
L"萊剛之塔 5F - 衝破萊剛之塔",
L"莱刚之塔 5F - 冲破莱刚之塔",
L"Tower of Licarn, 5F - Break through the Tower",
    }, { // 43 
L"龍之洞窟 - [天使之指甲]",
L"龙之洞窟 - [天使之指甲]",
L"Dragon Cave - [Angel's Nail]",
    }, { // 44 
L"遠古之遺跡 地下2樓",
L"远古之遗迹 地下2楼",
L"Ancient Ruins, B2F",
    }, { // 45 
L"矮人之村 彭賽 - 取得[解毒劑]",
L"矮人之村 彭赛 - 取得[解毒剂]",
L"Ponse, Village of Dwarves, Get an [Antidote]",
    }, { // 46 
L"波尼諾洞窟 - [波尼諾的果實]",
L"波尼诺洞窟 - [波尼诺的果实]",
L"Ponero Cave - [Fruit of Ponero]",
    }, { // 47 
L"聖女賽娜的祠堂 - 賽娜",
L"圣女赛娜的祠堂 - 赛娜",
L"Sena's Small Shrine - Sena",
    }, { // 48 
L"死者之遺跡 中央房間 - 討伐賈爾格",
L"死者之遗迹 中央房间 - 讨伐贾尔格",
L"The Remains of the Dead, Central Room",
    }, { // 49 
L"羅斯曼茲鎮 - 幫摩裡司夫人跑腿 - 任務觸發",
L"罗斯曼兹镇 - 帮摩里司夫人跑腿 - 任务触发",
L"Town of Losmans - Errand for Mrs. Morris - Quest Trigger",
    }, { // 50 
L"安德魯雪鎮 - 幫摩裡司夫人跑腿 - 白布",
L"安德鲁雪镇 - 帮摩里司夫人跑腿 - 白布",
L"Town of Antalusia - Errand for Mrs. Morris - White Cloth",
    }, { // 51 
L"卡拉得鎮 - 幫摩裡司夫人跑腿 - 紅線",
L"卡拉得镇 - 帮摩里司夫人跑腿 - 红线",
L"Town of Calado - Errand for Mrs. Morris - Red Thread",
    }, { // 52 
L"矮人之村 - 幫摩裡司夫人跑腿 - 銀針",
L"矮人之村 - 帮摩里司夫人跑腿 - 银针",
L"Village of Dwarves - Errand for Mrs. Morris - Silver Needle",
    }, { // 53 
L"安德魯雪鎮 - 歐貝隆之淚 - 任務觸發",
L"安德鲁雪镇 - 欧贝隆之泪 - 任务触发",
L"Town of Antalusia - Tears of Oberon - Quest Trigger",
    }, { // 54 
L"精靈之村 - 歐貝隆之淚 - 任務觸發",
L"精灵之村 - 欧贝隆之泪 - 任务触发",
L"Village of Elves - Tears of Oberon - Quest Trigger",
    }, { // 55 
L"卡拉得鎮 - 歐貝隆之淚 - 任務觸發",
L"卡拉得镇 - 欧贝隆之泪 - 任务触发",
L"Town of Calado - Tears of Oberon - Quest Trigger",
    }, { // 56 
L"黑暗天使的基地 - [歐貝隆之淚]",
L"黑暗天使的基地 - [欧贝隆之泪]",
L"Dark Elves Hiding Place - [Tears of Oberon]",
    }, { // 57 
L"矮人之村 - 遠古之短刀 - 任務觸發",
L"矮人之村 - 远古之短刀 - 任务触发",
L"Village of Dwarves - Ancient Short Sword - Quest Trigger",
    }, { // 58 
L"死與黑暗的荒野 [遠古之短刀]",
L"死与黑暗的荒野 [远古之短刀]",
L"The Wilds of Death and Darkness - [Ancient Short Sword]",
    }, { // 59 
L"薩雷斯遺跡 [金光球]",
L"萨雷斯遗迹 [金光球]",
L"The Ruins of Zeres - [Gold Orb]",
    }, { // 60 
L"魯庫那遺跡 [銀光球]",
L"鲁库那遗迹 [银光球]",
L"The Ruins of Lukuna - [Silver Orb]",
    }, { // 61 
L"果實 - 曼陀羅的根 - MP 50% - [黑傑克卡]",
L"果实 - 曼陀罗的根 - MP 50% - [黑杰克卡]",
L"Fruit - Mandragora - MP 50% - [Jack]",
    }, { // 62 
L"果實 - 精力之源 - MP 35% - [鬼卡]",
L"果实 - 精力之源 - MP 35% - [鬼卡]",
L"Fruit-  Mental Source - MP 35% - [Joker]",
    }, { // 63 
L"果實 - 活力之源 - HP 35% - [國王卡]",
L"果实 - 活力之源 - HP 35% - [国王卡]",
L"Fruit - Vitality Source - HP 35% - [King]",
    }, { // 64 
L"果實 - 木通子 - HP 30% - [皇后卡]",
L"果实 - 木通子 - HP 30% - [皇后卡]",
L"Fruit - Akebi Fruit - HP 30% - [Queen]",
    }, { // 65 
L"果實 - 柳橙 - MP 20%",
L"果实 - 柳橙 - MP 20%",
L"Fruit - Smart Orange - MP 20%",
    }, { // 66 
L"果實 - 枸杞 - MP 15%",
L"果实 - 枸杞 - MP 15%",
L"Fruit - Chinese Matrimony Vine - MP 15%",
    }, { // 67 
L"果實 - 青蘋果 - MP 10%",
L"果实 - 青苹果 - MP 10%",
L"Fruit - Green Apple - MP 10%",
    }, { // 68 
L"果實 - 奇哥的果實 - HP 20%",
L"果实 - 奇哥的果实 - HP 20%",
L"Fruit - Chico Nut - HP 20%",
    }, { // 69 
L"果實 - 胡桃 - HP 15%",
L"果实 - 胡桃 - HP 15%",
L"Fruit - Walnut - HP 15%",
    }, { // 70 
L"果實 - 蘋果 - HP 10%",
L"果实 - 苹果 - HP 10%",
L"Fruit - Apple - HP 10%",
    }, { // 71 
L"兌換 [黑傑克卡]",
L"兑换 [黑杰克卡]",
L"Redeem [Jack]",
    }, { // 72 
L"兌換 [鬼卡]",
L"兑换 [鬼卡]",
L"Redeem [Joker]",
    }, { // 73 
L"兌換 [國王卡]",
L"兑换 [国王卡]",
L"Redeem [King]",
    }, { // 74 
L"兌換 [皇后卡]",
L"兑换 [皇后卡]",
L"Redeem [Queen]",
    }, { // 75 
L"瓦姆洞窟 - [煉金藥] 復活藥",
L"瓦姆洞窟 - [炼金药] 复活药",
L"Wham Cave - [Elixir]",
    }, { // 76 
L"========卡拉得鎮西門 - 開啟第四話========",
L"========卡拉得镇西门 - 开启第四话========",
L"========West Gate of Calado - EP.4 ========",
    }, { // 77 
L"古代研究所 - [天使之記憶]",
L"古代研究所 - [天使之记忆]",
L"The Ancient Institute - [Angel's Memory]",
    }, { // 78 
L"卡修格爾遺跡 - [綠光球]",
L"卡修格尔遗迹 - [绿光球]",
L"The Ruins of Kashugal - [Green Orb]",
    }, { // 79 
L"貝爾尼村 - 賈爾格夫妻的紀念物 - 任務觸發",
L"贝尔尼村 - 贾尔格夫妻的纪念物 - 任务触发",
L"Berini Village - Find Jurg's Remembrance - Quest Trigger",
    }, { // 80 
L"貝爾尼村 - 賈爾格夫妻的紀念物 - 音樂盒",
L"贝尔尼村 - 贾尔格夫妻的纪念物 - 音乐盒",
L"Berini Village - Find Jurg's Remembrance - Music Box",
    }, { // 81 
L"廢墟之洞窟 地下2層 - [藍光球]",
L"废墟之洞窟 地下2层 - [蓝光球]",
L"The Cave of Ruins - [Blue Orb]",
    }, { // 82 
L"賽娜試煉之塔 5樓 - [紅光球]",
L"赛娜试炼之塔 5楼 - [红光球]",
L"Sena's Tower, 5F - [Red Orb]",
    }, { // 83 
L"退魔之遺跡",
L"退魔之遗迹",
L"The Ruins of Exorcism",
    }, { // 84 
L"終焉之森 - 前往哥利亞提之館 - 任務觸發",
L"终焉之森 - 前往哥利亚提之馆 - 任务触发",
L"Forest of Death - Goliate's Mansion - Quest Trigger",
    }, { // 85 
L"哥利亞提之館 地下3樓 - 哥利亞提",
L"哥利亚提之馆 地下3楼 - 哥利亚提",
L"Goliate's Mansion, B3 - Goliate",
    }, { // 86 
L"魔神的城堡 最上層 - 打倒魔神迪格諾西斯",
L"魔神的城堡 最上层 - 打倒魔神迪格诺西斯",
L"Devil's Castle, Top Floor - Beat the Devil Dignosis",
    }, { // 87 
L"矮人之村 - 賢者之遺跡 - 任務觸發1",
L"矮人之村 - 贤者之遗迹 - 任务触发1",
L"Village of Dwarves - Ruins of the Wise - Quest Trigger1",
    }, { // 88 
L"矮人之村 - 賢者之遺跡 - 任務觸發2",
L"矮人之村 - 贤者之遗迹 - 任务触发2",
L"Village of Dwarves - Ruins of the Wise - Quest Trigger2",
    }, { // 89 
L"賢者之遺跡 - 賢者魯溫",
L"贤者之遗迹 - 贤者鲁温",
L"Ruins of the Wise - Ruin, the Wise Man",
    }, { // 90 
L"反亂之塔 4樓 - 賈爾格餘黨的叛亂 - 任務觸發",
L"反乱之塔 4楼 - 贾尔格余党的叛乱 - 任务触发",
L"The Tower of Rebellion, 4F - Jurg Party - Quest Trigger",
    }, { // 91 
L"貝爾尼村 - 賈爾格餘黨的叛亂 - 任務觸發",
L"贝尔尼村 - 贾尔格余党的叛乱 - 任务触发",
L"Berini Village - Jurg Party - Quest Trigger",
    }, { // 92 
L"瘴氣之森 - [惡魔之牙]",
L"瘴气之森 - [恶魔之牙]",
L"Forest of Posion - [Demon Fang]",
    }, { // 93 
L"安德魯雪鎮 - 邊境之遺跡 - 任務觸發",
L"安德鲁雪镇 - 边境之遗迹 - 任务触发",
L"Town of Antalusia - The Ruins of Remoteness - Quest Trigger",
    }, { // 94 
L"邊境之遺跡 - [桂榴石] [紫水晶]",
L"边境之遗迹 - [桂榴石] [紫水晶]",
L"Ruins of Remoteness - [Hessonite] [Amethyst]",
    }, { // 95 
L"惡魔之碉堡 地下一層 - [錫石]",
L"恶魔之碉堡 地下一层 - [锡石]",
L"Fort of Demon, B1F - [Chiastolite]",
    }, { // 96 
L"惡魔之碉堡 地下二層 - [藍晶石]",
L"恶魔之碉堡 地下二层 - [蓝晶石]",
L"Fort of Demon, B2F - [Kyanite]",
    }, { // 97 
L"邊境之鎮 - [石榴石]",
L"边境之镇 - [石榴石]",
L"Remote Town - [Garnet]",
    }, { // 98 
L"寒冰暗妖精鎮 - [透輝石]",
L"寒冰暗妖精镇 - [透辉石]",
L"Cold Svalt Town - [Diopside]",
    }, { // 99 
L"煤礦之鎮 - [青金石]",
L"煤矿之镇 - [青金石]",
L"Mining Town - [Lapis-Lazuli]",
    }, { // 100 
L"精靈之村 - [銫綠柱石]",
L"精灵之村 - [铯绿柱石]",
L"Village of Elves - [Morganite]",
    }, { // 101 
L"試煉之塔 最上層 - [薔薇石英]",
L"试炼之塔 最上层 - [蔷薇石英]",
L"Tower of Ordeal, Top Floor - [RoseQuartz]",
    }, { // 102 
L"試煉之塔 別塔 13層",
L"试炼之塔 别塔 13层",
L"Tower of Ordeal, Annex 13F",
    }, { // 103 
L"試煉之塔 別塔 最上層",
L"试炼之塔 别塔 最上层",
L"Tower of Ordeal, Annex Top Floor",
    }
};
LPCWSTR APP_WSTR_SCENARIO[APP_WSTR_SCENARIO_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 00000000
L"[*] 邊境之鎮",
L"[*] 边境之镇",
L"[*] Remote Town",
    }, { // 1 00000001
L"    邊境之鎮周邊",
L"    边境之镇周边",
L"    Near the Remote Town",
    }, { // 2 00000003
L"    迷之荒地",
L"    迷之荒地",
L"    Wasteland of Hesitation",
    }, { // 3 00000004
L"    鐵之邊界",
L"    铁之边界",
L"    Iron Borderline",
    }, { // 4 00000005
L"    冰凍森林",
L"    冰冻森林",
L"    Frozen Forest",
    }, { // 5 00000006
L"[*] 石柱荒地",
L"[*] 石柱荒地",
L"[*] Wasteland of Pillars",
    }, { // 6 00010000
L"    塵土遺跡 地下一層 + 地下二層",
L"    尘土遗迹 地下一层 + 地下二层",
L"    Dusty Ruins, B1F + B2F",
    }, { // 7 00010001
L"    塵土遺跡 地下三層",
L"    尘土遗迹 地下三层",
L"    Dusty Ruins, B3F",
    }, { // 8 00010002
L"[*] 塵土遺跡 地下四層",
L"[*] 尘土遗迹 地下四层",
L"[*] Dusty Ruins, B4F",
    }, { // 9 00010003
L"[*] 塵土遺跡 底下五層",
L"[*] 尘土遗迹 底下五层",
L"[*] Dusty Ruins, B5F",
    }, { // 10 00010004
L"    塵土遺跡 審判室",
L"    尘土遗迹 审判室",
L"    Dusty Ruins, Room of Judgment",
    }, { // 11 00010005
L"    塵土遺跡 連通的房間",
L"    尘土遗迹 连通的房间",
L"    Dusty Ruins, Continued Room",
    }, { // 12 01000000
L"[*] 寒冰暗妖精鎮",
L"[*] 寒冰暗妖精镇",
L"[*] Cold Svalt Town",
    }, { // 13 01000001
L"    寒冰暗妖精鎮周邊",
L"    寒冰暗妖精镇周边",
L"    Near Cold Svalt Town",
    }, { // 14 01000002
L"[*] 蒸氣森林",
L"[*] 蒸气森林",
L"[*] Vaporous Forest",
    }, { // 15 01000003
L"[*] 倒吊男之森",
L"[*] 倒吊男之森",
L"[*] Hanged Men's Forest",
    }, { // 16 01000004
L"[*] 樹海",
L"[*] 树海",
L"[*] Sea of Trees",
    }, { // 17 01020000
L"    冰冷遺跡 地下一層",
L"    冰冷遗迹 地下一层 ",
L"    Cold Ruins, B1F",
    }, { // 18 01020001
L"[*] 冰冷遺跡 地下二層 + 地下三層 + 小房間",
L"[*] 冰冷遗迹 地下二层 + 地下三层 + 小房间",
L"[*] Cold Ruins, B2F + B3F + Small Room",
    }, { // 19 01020002
L"    冰冷遺跡 最底層",
L"    冰冷遗迹 最底层",
L"    Cold Ruins, Bottom Floor",
    }, { // 20 01030000
L"[*] 判決煉獄 地下一層",
L"[*] 判决炼狱 地下一层",
L"[*] Purgatory of Judgments, B1F",
    }, { // 21 01030001
L"    判決煉獄 地下二層",
L"    判决炼狱 地下二层",
L"    Purgatory of Judgments, B2F",
    }, { // 22 01030002
L"    判決煉獄 是非之室入口 + 是非之室",
L"    判决炼狱 是非之室入口 + 是非之室",
L"    Purgatory of Judgments, Right/Wrong Room",
    }, { // 23 01040000
L"    輪回遺跡(入口)",
L"    轮回遗迹(入口)",
L"    Remains of Reincarnation (Entrance)",
    }, { // 24 01040001
L"    輪回遺跡1F + 1F大廳 + 2F + B1F + 2F大廳 + 3F",
L"    轮回遗迹1F + 1F大厅 + 2F + B1F + 2F大厅 + 3F",
L"    Remains of Reincarnation, 1F + B1F + 2F + 3F",
    }, { // 25 01040002
L"    輪回遺跡 大廳入口 + 大廳 + 光亮的房間",
L"    轮回遗迹 大厅入口 + 大厅 + 光亮的房间",
L"    Remains of Reincarnation, Big Hall",
    }, { // 26 01050000
L"    不死的遺跡 地下一層",
L"    不死的遗迹 地下一层",
L"    Immortal Remains, B1F",
    }, { // 27 01050001
L"[*] 不死的遺跡 地下二層",
L"[*] 不死的遗迹 地下二层",
L"[*] Immortal Remains, B2F",
    }, { // 28 01050002
L"    不死的遺跡 絕望的通路 + 悶熱的房間 + 最底層",
L"    不死的遗迹 绝望的通路 + 闷热的房间 + 最底层",
L"    Immortal Remains Heated Hall + Bottom Section",
    }, { // 29 02000000
L"    森林(區域一)",
L"    森林(区域一)",
L"    Forest (Area 1)",
    }, { // 30 02000001
L"    森林(區域二)",
L"    森林(区域二)",
L"    Forest (Area 2)",
    }, { // 31 02010000
L"    煤礦(森林(區域二))",
L"    煤矿(森林(区域二))",
L"    Mine (Forest (Area 2))",
    }, { // 32 02100000
L"[*] 煤礦之鎮 剛佛雷",
L"[*] 煤矿之镇 刚佛雷",
L"[*] Kanfore, Mining Town",
    }, { // 33 02100001
L"    四葉之森",
L"    四叶之森",
L"    Forest of Four Leaves",
    }, { // 34 02100002
L"[*] 鉤爪之森",
L"[*] 钩爪之森",
L"[*] Forest of Claws",
    }, { // 35 02100003
L"    寂靜之森",
L"    寂静之森",
L"    Forest of Silence",
    }, { // 36 02100004
L"[*] 十字礦場",
L"[*] 十字矿场",
L"[*] Cross Agora",
    }, { // 37 02100005
L"[*] 英靈之森",
L"[*] 英灵之森",
L"[*] Forest of Sprits",
    }, { // 38 02100006
L"[*] 悲哀騎士森林",
L"[*] 悲哀骑士森林",
L"[*] Forest of Knight's Misery",
    }, { // 39 02110000
L"    魔導師之塔 1F-10F(英靈之森)",
L"    魔导师之塔 1F-10F(英灵之森)",
L"    Tower of the Wizard (Forest of Sprits)",
    }, { // 40 02120000
L"    盜賊的碉堡(悲哀騎士森林)",
L"    盗贼的碉堡(悲哀骑士森林)",
L"    Fort of Thieves",
    }, { // 41 02120001
L"    盜賊的碉堡內部通路(悲哀騎士森林)",
L"    盗贼的碉堡内部通路(悲哀骑士森林)",
L"    Back Street of the Fort of Thieves",
    }, { // 42 02130000
L"    煤礦(四葉之森)",
L"    煤矿(四叶之森)",
L"    Coal Mine (Forest of Four Leaves)",
    }, { // 43 02140000
L"    煤礦(英靈之森)",
L"    煤矿(英灵之森)",
L"    Coal Mine (Forest of Sprits)",
    }, { // 44 02200000
L"[*] 精靈之村 法南",
L"[*] 精灵之村 法南",
L"[*] Fanann, Village of Elves",
    }, { // 45 02200001
L"    蝶之丘",
L"    蝶之丘",
L"    Butterfly Hill",
    }, { // 46 02200002
L"    威斯雷森林",
L"    威斯雷森林",
L"    Forest of Wesley",
    }, { // 47 02200003
L"[*] 龍之道",
L"[*] 龙之道",
L"[*] Dragon Road",
    }, { // 48 02200004
L"    摩布之迷宮",
L"    摩布之迷宫",
L"    Labyrinth of Mauve",
    }, { // 49 02200005
L"[*] 電源設備周邊",
L"[*] 电源设备周边",
L"[*] Near The Power Supply Facility",
    }, { // 50 02210000
L"    優格諾斯坑道 地下一層",
L"    优格诺斯坑道 地下一层",
L"    Mining Tunnel of Yugunos, B1F",
    }, { // 51 02210001
L"    優格諾斯坑道 地下二層",
L"    优格诺斯坑道 地下二层",
L"    Mining Tunnel of Yugunos, B2F",
    }, { // 52 02210002
L"[*] 優格諾斯坑道 地下三層",
L"[*] 优格诺斯坑道 地下三层",
L"[*] Mining Tunnel of Yugunos, B3F",
    }, { // 53 02210003
L"    優格諾斯坑道 地下四層",
L"    优格诺斯坑道 地下四层",
L"    Mining Tunnel of Yugunos, B4F",
    }, { // 54 02210004
L"    優格諾斯坑道 地下五層",
L"    优格诺斯坑道 地下五层",
L"    Mining Tunnel of Yugunos, B5F",
    }, { // 55 02220000
L"    地下道 地下一層",
L"    地下道 地下一层",
L"    Underground Passage, B1F",
    }, { // 56 02220001
L"    地下道 地下二層",
L"    地下道 地下二层",
L"    Underground Passage, B2F",
    }, { // 57 02230000
L"    電源碉堡(電源設備周邊)",
L"    电源碉堡(电源设备周边)",
L"    Fort of the Power Supply",
    }, { // 58 02240000
L"    洞窟 地下一樓(蝶之丘)",
L"    洞窟 地下一楼(蝶之丘)",
L"    Cave, B1F (Butterfly Hill)",
    }, { // 59 02240001
L"    洞窟 地下一樓(蝶之丘)",
L"    洞窟 地下一楼(蝶之丘)",
L"    Cave, B2F",
    }, { // 60 02250000
L"    威斯雷洞窟(威斯雷森林)",
L"    威斯雷洞窟(威斯雷森林)",
L"    Wesley Cave",
    }, { // 61 02999999
L"    商隊",
L"    商队",
L"    Caravan",
    }, { // 62 03000101
L"    死與黑暗的荒野",
L"    死与黑暗的荒野",
L"    The Wilds of Death and Darkness",
    }, { // 63 03000201
L"[*] 走向毀滅者之谷",
L"[*] 走向毁灭者之谷",
L"[*] Valley of Dying People",
    }, { // 64 03000202
L"    魯那法多海岸",
L"    鲁那法多海岸",
L"    Lunafuld Beach",
    }, { // 65 03000203
L"    阿爾提利亞",
L"    阿尔提利亚",
L"    Alteria",
    }, { // 66 03000301
L"    哥拉斯沙漠",
L"    哥拉斯沙漠",
L"    Golas Desert",
    }, { // 67 03000302
L"[*] 天翔之丘",
L"[*] 天翔之丘",
L"[*] Hill of Heaven",
    }, { // 68 03000303
L"[*] 贖罪之道",
L"[*] 赎罪之道",
L"[*] The Road of Atonement",
    }, { // 69 03000304
L"    哥羅那郊區",
L"    哥罗那郊区",
L"    Goronaburb",
    }, { // 70 03000305
L"    隆賽迪雅灣",
L"    隆赛迪雅湾",
L"    The Gulf of Lucentia",
    }, { // 71 03000306
L"[*] 迪雅羅賽平原",
L"[*] 迪雅罗赛平原",
L"[*] The Plain of Dialose",
    }, { // 72 03000307
L"[*] 龍脈之荒野",
L"[*] 龙脉之荒野",
L"[*] The Wilds of Ryumyaku",
    }, { // 73 03000402
L"[*] 依爾巴那之森",
L"[*] 依尔巴那之森",
L"[*] Forest of Ilbarna",
    }, { // 74 03000403
L"    羅斯曼茲鎮南方",
L"    罗斯曼兹镇南方",
L"    South Losmans",
    }, { // 75 03000404
L"    羅斯曼茲鎮東方",
L"    罗斯曼兹镇东方",
L"    East Losmans",
    }, { // 76 03000405
L"    剛格司頓瓦爾多",
L"    剛格司頓瓦爾多",
L"    Gungstonwald",
    }, { // 77 03000406
L"    安德魯雪鎮西方",
L"    安德鲁雪镇西方",
L"    West Antalusia",
    }, { // 78 03000407
L"    德多隆山麓",
L"    德多隆山麓",
L"    The Foot of Mt. Tedoron",
    }, { // 79 03000503
L"    摩爾多那半島",
L"    摩尔多那半岛",
L"    The Moldona Peninsula",
    }, { // 80 03000505
L"[*] 梅賽拉爾德古墳",
L"[*] 梅赛拉尔德古坟",
L"[*] Mesrald Burial Grounds",
    }, { // 81 03000506
L"    安德魯雪鎮南方",
L"    安德鲁雪镇南方",
L"    South Antalusia",
    }, { // 82 03000507
L"    安德魯雪鎮東方",
L"    安德鲁雪镇东方",
L"    East Antalusia",
    }, { // 83 03010000
L"    死者之遺跡 東方",
L"    死者之遗迹 东方",
L"    East of The Remains of The Dead (Alteria)",
    }, { // 84 03010001
L"    死者之遺跡 西方",
L"    死者之遗迹 西方",
L"    West of The Remains of The Dead",
    }, { // 85 03010002
L"    死者之遺跡 南方",
L"    死者之遗迹 南方",
L"    South of The Remains of The Dead",
    }, { // 86 03010003
L"    死者之遺跡 北方",
L"    死者之遗迹 北方",
L"    North of The Remains of The Dead",
    }, { // 87 03010004
L"    死者之遺跡 中央房間",
L"    死者之遗迹 中央房间",
L"    The Remains of The Dead, Central Room",
    }, { // 88 03020000
L"    那茲爾之塔 1樓(安德魯雪鎮東方)",
L"    那兹尔之塔 1楼(安德鲁雪镇东方)",
L"    Tower of Nazzle, 1F (East Losmans)",
    }, { // 89 03020001
L"    那茲爾之塔 2樓",
L"    那兹尔之塔 2楼",
L"    Tower of Nazzle, 2F",
    }, { // 90 03020002
L"    那茲爾之塔 3樓",
L"    那兹尔之塔 3楼",
L"    Tower of Nazzle, 3F",
    }, { // 91 03020003
L"    那茲爾之塔 4樓",
L"    那兹尔之塔 4楼",
L"    Tower of Nazzle, 4F",
    }, { // 92 03020004
L"    那茲爾之塔 5樓",
L"    那兹尔之塔 5楼",
L"    Tower of Nazzle, 5F",
    }, { // 93 03030000
L"    教會地下洞窟(安德魯雪鎮)",
L"    教会地下洞窟(安德鲁雪镇)",
L"    Underground Cave of a Church (A Town of Antalusia)",
    }, { // 94 03040000
L"    剛恩遺跡(梅賽拉爾德古墳)",
L"    刚恩遗迹(梅赛拉尔德古坟)",
L"    Ruins of Carn (Mesrald Burial Grounds)",
    }, { // 95 03050000
L"    達爾斯遺跡(梅賽拉爾德古墳)",
L"    达尔斯遗迹(梅赛拉尔德古坟)",
L"    Ruins of Dals (Mesrald Burial Grounds)",
    }, { // 96 03060000
L"    葛爾迪亞洞窟(梅賽拉爾德古墳)",
L"    葛尔迪亚洞窟(梅赛拉尔德古坟)",
L"    Coldea Cave (Mesrald Burial Grounds)",
    }, { // 97 03070000
L"    瓦姆洞窟(梅賽拉爾德古墳)",
L"    瓦姆洞窟(梅赛拉尔德古坟)",
L"    Wham Cave (Mesrald Burial Grounds)",
    }, { // 98 03080000
L"    湖之遺跡(迪雅羅賽平原)",
L"    湖之遗迹(迪雅罗赛平原)",
L"    The Ruins of The Lake (The Plain of Dialose)",
    }, { // 99 03090000
L"    鼓動之遺跡(龍脈之荒野)",
L"    鼓动之遗迹(龙脉之荒野)",
L"    The Remains of Heartbeat (The Wilds of Ryumyaku)",
    }, { // 100 03100000
L"    哥亞洞窟[肉](剛格司頓瓦爾多)",
L"    哥亚洞窟[肉](刚格司顿瓦尔多)",
L"    Gore Cave [Meat] (Gungstonwald)",
    }, { // 101 03110000
L"    萊剛之塔 1樓(羅斯曼茲鎮南方)",
L"    莱刚之塔 1楼(罗斯曼兹镇南方)",
L"    Tower of Licarn, 1F (South Losmans)",
    }, { // 102 03110001
L"    萊剛之塔 2樓",
L"    莱刚之塔 2楼",
L"    Tower of Licarn, 2F",
    }, { // 103 03110002
L"    萊剛之塔 3樓",
L"    莱刚之塔 3楼",
L"    Tower of Licarn, 3F",
    }, { // 104 03110003
L"    萊剛之塔 4樓",
L"    莱刚之塔 4楼",
L"    Tower of Licarn, 4F",
    }, { // 105 03110004
L"    萊剛之塔 5樓",
L"    莱刚之塔 5楼",
L"    Tower of Licarn, 5F",
    }, { // 106 03120000
L"    龍之洞窟(依爾巴那之森)",
L"    龙之洞窟(依尔巴那之森)",
L"    Dragon Cave (Forest of Ilbarna)",
    }, { // 107 03130000
L"    波尼諾洞窟(摩爾多那半島)",
L"    波尼诺洞窟(摩尔多那半岛)",
L"    Ponero Cave (The Moldona Peninsula)",
    }, { // 108 03140000
L"    遠古之遺跡 地下一樓(天翔之丘)",
L"    远古之遗迹 地下一楼(天翔之丘)",
L"    Ancient Ruins, B1F (Hill of Heaven)",
    }, { // 109 03140001
L"    遠古之遺跡 地下二樓",
L"    远古之遗迹 地下二楼",
L"    Ancient Ruins, B2F",
    }, { // 110 03150000
L"    哥爾德遺跡(贖罪之道)",
L"    哥尔德遗迹(赎罪之道)",
L"    The Ruins of Goldo (The Road of Atonement)",
    }, { // 111 03160000
L"    梅利亞遺跡(哥羅那郊區)",
L"    梅利亚遗迹(哥罗那郊区)",
L"    Meria Ruin (Goronaburb)",
    }, { // 112 03170000
L"    拜達爾遺跡(哥拉斯沙漠)",
L"    拜达尔遗迹(哥拉斯沙漠)",
L"    Bidal Ruin (Golas Desert)",
    }, { // 113 03180000
L"    魯庫那遺跡(哥拉斯沙漠)",
L"    鲁库那遗迹(哥拉斯沙漠)",
L"    The Ruins of Lukuna (Golas Desert)",
    }, { // 114 03190000
L"    多隆遺跡(哥拉斯沙漠)",
L"    多隆遗迹(哥拉斯沙漠)",
L"    The Ruins of Dron (Golas Desert)",
    }, { // 115 03200000
L"    渥格洞窟[藥](走向毀滅者之穀)",
L"    渥格洞窟[药](走向毁灭者之谷)",
L"    Wog Cave [Tablet] (Valley of Dying People)",
    }, { // 116 03210000
L"    地下通路(走向毀滅者之穀-死與黑暗的荒野)",
L"    地下通路(走向毁灭者之谷-死与黑暗的荒野)",
L"    Underground Passage (Valley of Dying People)",
    }, { // 117 03220000
L"    薩雷斯遺跡(魯那法多海岸)",
L"    萨雷斯遗迹(鲁那法多海岸)",
L"    The Ruins of Zeres (Lunafuld Beach)",
    }, { // 118 03230000
L"    姆爾洞窟[膠囊](魯那法多海岸)",
L"    姆尔洞窟[胶囊](鲁那法多海岸)",
L"    Mour Cave [Capsule] (Lunafuld Beach)",
    }, { // 119 03240000
L"[*] 黑暗天使的基地",
L"[*] 黑暗天使的基地",
L"[*] Dark Elves Hiding Place",
    }, { // 120 03900000
L"    優格諾斯南方軍營",
L"    优格诺斯南方军营",
L"    South Camp of Yugunos",
    }, { // 121 03900001
L"[*] 安德魯雪鎮",
L"[*] 安德鲁雪镇",
L"[*] A Town of Antalusia",
    }, { // 122 03900002
L"[*] 卡拉得鎮",
L"[*] 卡拉得镇",
L"[*] Town of Calado",
    }, { // 123 03900003
L"[*] 羅斯曼茲鎮",
L"[*] 罗斯曼兹镇",
L"[*] Town of Losmans",
    }, { // 124 03900004
L"[*] 矮人之村 彭賽",
L"[*] 矮人之村 彭赛",
L"[*] Ponse, Village of Dwarves",
    }, { // 125 03900005
L"[*] 聖女賽娜的祠堂",
L"[*] 圣女赛娜的祠堂",
L"[*] Sena's Small Shrine",
    }, { // 126 04000000
L"    卡拉得鎮西方",
L"    卡拉得镇西方",
L"    West Calado",
    }, { // 127 04000001
L"[*] 卡伍德濕地",
L"[*] 卡伍德湿地",
L"[*] Garwood Swamp",
    }, { // 128 04000002
L"[*] 湖之迷宮",
L"[*] 湖之迷宫",
L"[*] Labyrinth of the Lake",
    }, { // 129 04000003
L"[*] 龍之森",
L"[*] 龙之森",
L"[*] Dragon Forest",
    }, { // 130 04000004
L"    魔物之森",
L"    魔物之森",
L"    Demon's Forest",
    }, { // 131 04000005
L"[*] 歐爾菲海岸",
L"[*] 欧尔菲海岸",
L"[*] Orphe Beach",
    }, { // 132 04000006
L"    瘴氣之森",
L"    瘴气之森",
L"    Forest of Poison",
    }, { // 133 04000007
L"[*] 哥利亞提森林",
L"[*] 哥利亚提森林",
L"[*] Forest of Goliate",
    }, { // 134 04000008
L"    夢幻之道",
L"    梦幻之道",
L"    Fantasy Road",
    }, { // 135 04000009
L"[*] 終焉之森",
L"[*] 终焉之森",
L"[*] Forest of Death",
    }, { // 136 04010000
L"    古代研究所(龍之森)",
L"    古代研究所(龙之森)",
L"    The Ancient Institute (Dragon Forest)",
    }, { // 137 04020000
L"    卡修格爾遺跡(卡伍德濕地)",
L"    卡修格尔遗迹(卡伍德湿地)",
L"    The Ruins of Kashugal (Garwood Swamp)",
    }, { // 138 04030000
L"    湖之地下通路",
L"    湖之地下通路",
L"    Tunnel Under The Lake (Labyrinth of the Lake)",
    }, { // 139 04040000
L"    退魔之遺跡(魔物之森)",
L"    退魔之遗迹(魔物之森)",
L"    Ruins of Exorcism (Demon's Forest)",
    }, { // 140 04050000
L"    哥利亞提之館 地下一層",
L"    哥利亚提之馆 地下一层",
L"    Goliate's Mansion, B1F (Forest of Goliate)",
    }, { // 141 04050001
L"    哥利亞提之館 地下二層",
L"    哥利亚提之馆 地下二层",
L"    Goliate's Mansion, B2F",
    }, { // 142 04050002
L"    哥利亞提之館 地下三層",
L"    哥利亚提之馆 地下三层",
L"    Goliate's Mansion, B3F",
    }, { // 143 04060000
L"[*] 冥府之道(區域一)",
L"[*] 冥府之道(区域一)",
L"[*] The Road of The Netherworld, B1F (Forest of Death)",
    }, { // 144 04060001
L"    冥府之道(區域二)",
L"    冥府之道(区域二)",
L"    The Road of The Netherworld, B2F",
    }, { // 145 04060002
L"    冥府之道(區域三)",
L"    冥府之道(区域三)",
L"    The Road of The Netherworld, B3F",
    }, { // 146 04060003
L"    魔神的城堡 一層",
L"    魔神的城堡 一层",
L"    Devil's Castle, 1F",
    }, { // 147 04060004
L"    魔神的城堡 二層",
L"    魔神的城堡 二层",
L"    Devil's Castle, 2F",
    }, { // 148 04060005
L"    魔神的城堡 三層",
L"    魔神的城堡 三层",
L"    Devil's Castle, 3F",
    }, { // 149 04060006
L"    魔神的城堡 最頂層",
L"    魔神的城堡 最顶层",
L"    Devil's Castle, Top Floor",
    }, { // 150 04070000
L"    廢墟之洞窟 地下一層(廢墟)",
L"    废墟之洞窟 地下一层(废墟)",
L"    The Cave of Ruins, B1F (Ruins of Berini Village)",
    }, { // 151 04070001
L"    廢墟之洞窟 地下二層",
L"    废墟之洞窟 地下二层",
L"    The Cave of Ruins, B2F",
    }, { // 152 04080000
L"    賽娜試煉之塔 一樓(貝爾尼村)",
L"    赛娜试炼之塔 一楼(贝尔尼村)",
L"    Sena's Tower, 1F (Berini Village)",
    }, { // 153 04080001
L"    賽娜試煉之塔 二樓",
L"    赛娜试炼之塔 二楼",
L"    Sena's Tower, 2F",
    }, { // 154 04080002
L"    賽娜試煉之塔 三樓",
L"    赛娜试炼之塔 三楼",
L"    Sena's Tower, 3F",
    }, { // 155 04080003
L"    賽娜試煉之塔 四樓",
L"    赛娜试炼之塔 四楼",
L"    Sena's Tower, 4F",
    }, { // 156 04080004
L"    賽娜試煉之塔 五樓",
L"    赛娜试炼之塔 五楼",
L"    Sena's Tower, 5F",
    }, { // 157 04090000
L"    反亂之塔 一樓(哥拉斯沙漠)",
L"    反乱之塔 一楼(哥拉斯沙漠)",
L"    Tower of Rebellion, 1F (Golas Desert)",
    }, { // 158 04090001
L"    反亂之塔 二樓",
L"    反乱之塔 二楼",
L"    Tower of Rebellion, 2F",
    }, { // 159 04090002
L"    反亂之塔 三樓",
L"    反乱之塔 三楼",
L"    Tower of Rebellion, 3F",
    }, { // 160 04090003
L"    反亂之塔 四樓",
L"    反乱之塔 四楼",
L"    Tower of Rebellion, 4F",
    }, { // 161 04100000
L"    賢者之遺跡(哥羅那郊區)",
L"    贤者之遗迹(哥罗那郊区)",
L"    The Ruins of The Wise (Goronaburb)",
    }, { // 162 04110000
L"    邊境之遺跡(梅賽拉爾德古墳)",
L"    边境之遗迹(梅赛拉尔德古坟)",
L"    The Ruins of Remoteness (Mesrald Burial Grounds)",
    }, { // 163 04120000
L"    惡魔之碉堡 地下一層(安特村)",
L"    恶魔之碉堡 地下一层(安特村)",
L"    Fort of Demon, B1F",
    }, { // 164 04120001
L"    惡魔之碉堡 地下二層",
L"    恶魔之碉堡 地下二层",
L"    Fort of Demon, B2F",
    }, { // 165 04130000
L"[*] 狂氣之森",
L"[*] 狂气之森",
L"[*] Forest of Madness",
    }, { // 166 04140000
L"    恐龍之洞窟(夢幻之道)",
L"    恐龙之洞窟(梦幻之道)",
L"    Dinosaur Cave (Fantasy Road)",
    }, { // 167 04900000
L"    卡拉得鎮西門",
L"    卡拉得镇西门",
L"    West Gate of Calado",
    }, { // 168 04900001
L"[*] 貝爾尼村",
L"[*] 贝尔尼村",
L"[*] Berini Village",
    }, { // 169 04900002
L"[*] 安特村",
L"[*] 安特村",
L"[*] Ento Village",
    }, { // 170 04900003
L"    廢墟",
L"    废墟",
L"    Ruins of Berini Village",
    }, { // 171 99000000
L"    通往塔的道路",
L"    通往塔的道路",
L"    Road to a Tower",
    }, { // 172 99000001
L"[*] 試煉之塔",
L"[*] 试炼之塔",
L"[*] Tower of Ordeal",
    }, { // 173 99000002
L"    試煉之塔 1樓",
L"    试炼之塔 1楼",
L"    Tower of Ordeal, 1F",
    }, { // 174 99000003
L"    試煉之塔 2樓",
L"    试炼之塔 2楼",
L"    Tower of Ordeal, 2F",
    }, { // 175 99000004
L"    試煉之塔 3樓",
L"    试炼之塔 3楼",
L"    Tower of Ordeal, 3F",
    }, { // 176 99000005
L"    試煉之塔 4樓",
L"    试炼之塔 4楼",
L"    Tower of Ordeal, 4F",
    }, { // 177 99000006
L"    試煉之塔 5樓",
L"    试炼之塔 5楼",
L"    Tower of Ordeal, 5F",
    }, { // 178 99000007
L"[*] 試煉之塔 6樓",
L"[*] 试炼之塔 6楼",
L"[*] Tower of Ordeal, 6F",
    }, { // 179 99000008
L"    試煉之塔 7樓",
L"    试炼之塔 7楼",
L"    Tower of Ordeal, 7F",
    }, { // 180 99000009
L"    試煉之塔 8樓",
L"    试炼之塔 8楼",
L"    Tower of Ordeal, 8F",
    }, { // 181 99000010
L"    試煉之塔 9樓",
L"    试炼之塔 9楼",
L"    Tower of Ordeal, 9F",
    }, { // 182 99000011
L"    試煉之塔 10樓",
L"    试炼之塔 10楼",
L"    Tower of Ordeal, 10F",
    }, { // 183 99000012
L"    試煉之塔 11樓",
L"    试炼之塔 11楼",
L"    Tower of Ordeal, 11F",
    }, { // 184 99000013
L"[*] 試煉之塔 12樓",
L"[*] 试炼之塔 12楼",
L"[*] Tower of Ordeal, 12F",
    }, { // 185 99000014
L"    試煉之塔 13樓",
L"    试炼之塔 13楼",
L"    Tower of Ordeal, 13F",
    }, { // 186 99000015
L"    試煉之塔 14樓",
L"    试炼之塔 14楼",
L"    Tower of Ordeal, 14F",
    }, { // 187 99000016
L"    試煉之塔 15樓",
L"    试炼之塔 15楼",
L"    Tower of Ordeal, 15F",
    }, { // 188 99000017
L"    試煉之塔 16樓",
L"    试炼之塔 16楼",
L"    Tower of Ordeal, 16F",
    }, { // 189 99000018
L"[*] 試煉之塔 17樓",
L"[*] 试炼之塔 17楼",
L"[*] Tower of Ordeal, 17F",
    }, { // 190 99000019
L"    試煉之塔 18樓",
L"    试炼之塔 18楼",
L"    Tower of Ordeal, 18F",
    }, { // 191 99000020
L"    試煉之塔 19樓",
L"    试炼之塔 19楼",
L"    Tower of Ordeal, 19F",
    }, { // 192 99000021
L"    試煉之塔 20樓",
L"    试炼之塔 20楼",
L"    Tower of Ordeal, 20F",
    }, { // 193 99000022
L"    試煉之塔 21樓",
L"    试炼之塔 21楼",
L"    Tower of Ordeal, 21F",
    }, { // 194 99000023
L"[*] 試煉之塔 最上層",
L"[*] 试炼之塔 最上层",
L"[*] Tower of Ordeal, Top Floor",
    }, { // 195 99000024
L"    試煉之塔 別塔 1樓",
L"    试炼之塔 别塔 1楼",
L"    Tower of Ordeal, Annex, 1F",
    }, { // 196 99000025
L"    試煉之塔 別塔 2樓",
L"    试炼之塔 别塔 2楼",
L"    Tower of Ordeal, Annex, 2F",
    }, { // 197 99000026
L"    試煉之塔 別塔 3樓",
L"    试炼之塔 别塔 3楼",
L"    Tower of Ordeal, Annex, 3F",
    }, { // 198 99000027
L"    試煉之塔 別塔 4樓",
L"    试炼之塔 别塔 4楼",
L"    Tower of Ordeal, Annex, 4F",
    }, { // 199 99000028
L"    試煉之塔 別塔 5樓",
L"    试炼之塔 别塔 5楼",
L"    Tower of Ordeal, Annex, 5F",
    }, { // 200 99000029
L"    試煉之塔 別塔 6樓",
L"    试炼之塔 别塔 6楼",
L"    Tower of Ordeal, Annex, 6F",
    }, { // 201 99000030
L"    試煉之塔 別塔 7樓",
L"    试炼之塔 别塔 7楼",
L"    Tower of Ordeal, Annex, 7F",
    }, { // 202 99000031
L"    試煉之塔 別塔 8樓",
L"    试炼之塔 别塔 8楼",
L"    Tower of Ordeal, Annex, 8F",
    }, { // 203 99000032
L"    試煉之塔 別塔 9樓",
L"    试炼之塔 别塔 9楼",
L"    Tower of Ordeal, Annex, 9F",
    }, { // 204 99000033
L"    試煉之塔 別塔 10樓",
L"    试炼之塔 别塔 10楼",
L"    Tower of Ordeal, Annex, 10F",
    }, { // 205 99000034
L"    試煉之塔 別塔 11樓",
L"    试炼之塔 别塔 11楼",
L"    Tower of Ordeal, Annex, 11F",
    }, { // 206 99000035
L"    試煉之塔 別塔 12樓",
L"    试炼之塔 别塔 12楼",
L"    Tower of Ordeal, Annex, 12F",
    }, { // 207 99000036
L"    試煉之塔 別塔 13樓",
L"    试炼之塔 别塔 13楼",
L"    Tower of Ordeal, Annex, 13F",
    }, { // 208 99000037
L"    試煉之塔 別塔 頂層",
L"    试炼之塔 别塔 顶层",
L"    Tower of Ordeal, Annex, Top Floor",
    }
};
LPCWSTR APP_WSTR_MAGIC[APP_WSTR_MAGIC_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 AWSTR_MAGIC_TRANSPORT
L"傳送術",
L"传送术",
L"Transport",
    }, { // 1 AWSTR_MAGIC_FIRE_BALL
L"火球術",
L"火球术",
L"Fire Ball",
    }, { // 2 AWSTR_MAGIC_ICE_BOLT
L"冰彈術",
L"冰弹术",
L"Ice Bolt",
    }, { // 3 AWSTR_MAGIC_PLASMA
L"閃電術",
L"闪电术",
L"Plasma",
    }, { // 4 AWSTR_MAGIC_HELL_FIRE
L"地獄火",
L"地狱火",
L"Hell Fire",
    }, { // 5 AWSTR_MAGIC_ICE_BLAST
L"冰風暴",
L"冰风暴",
L"Ice Blast",
    }, { // 6 AWSTR_MAGIC_HEAL
L"治療術",
L"治疗术",
L"Heal",
    }, { // 7 AWSTR_MAGIC_MOON
L"月之術",
L"月之术",
L"Moon",
    }, { // 8 AWSTR_MAGIC_BERSERKER
L"狂暴化",
L"狂暴化",
L"Berserker",
    }, { // 9 AWSTR_MAGIC_ENERGY_SHIELD
L"能量盾",
L"能量盾",
L"Energy Shield",
    }, { // 10 AWSTR_MAGIC_EARTH_SPEAR
L"大地之槍",
L"大地之枪",
L"Earth Spear",
    }, { // 11 AWSTR_MAGIC_FLAME_STRIKE
L"烈焰強擊",
L"烈焰强击",
L"Flame Strike",
    }, { // 12 AWSTR_MAGIC_DREAD_DEATHSCYTHE
L"冰鐮刀",
L"冰镰刀",
L"Dread Deathscythe",
    }, { // 13 AWSTR_MAGIC_LIGHTNING_STORM
L"閃電風暴",
L"闪电风暴",
L"Lightning Storm",
    }, { // 14 AWSTR_MAGIC_MEDUSA
L"蛇發魔女",
L"蛇发魔女",
L"Medusa",
    }, { // 15 AWSTR_MAGIC_SONIC_BLADE
L"音速劍",
L"音速剑",
L"Sonic Blade",
    }, { // 16 AWSTR_MAGIC_MUD_JAVELIN
L"泥槍術",
L"泥枪术",
L"Mud Javelin",
    }, { // 17 AWSTR_MAGIC_IDENTIFY
L"鑒定術",
L"鉴定术",
L"Identify",
    }, { // 18 AWSTR_MAGIC_MAGIC_SHIELD
L"魔法盾",
L"魔法盾",
L"Magic Shield",
    }, { // 19 AWSTR_MAGIC_COUNTER_BURST
L"攻擊反彈",
L"攻击反弹",
L"Counter Burst",
    }, { // 20 AWSTR_MAGIC_EXPLOSION
L"爆炸術",
L"爆炸术",
L"Explosion",
    }, { // 21 AWSTR_MAGIC_ELEMENTAL_STRIKE
L"元素攻擊",
L"元素攻击",
L"Elemental Strike",
    }
};
LPCWSTR APP_WSTR_QUEST[APP_WSTR_QUEST_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
        { // 0 AWSTR_QUEST_DEFEAT_THE_RED_GOBLIN
L"紅哥布林",
L"红哥布林",
L"Red Goblin",
    }, { // 1 AWSTR_QUEST_TAKE_BACK_MALSES_GEM
L"馬爾斯的寶石",
L"马尔斯的宝石",
L"Malse's Gem",
    }, { // 2 AWSTR_QUEST_TAKE_BACK_SYRIAS_SPIRIT_STONE
L"絲莉亞精靈石",
L"丝莉亚精灵石",
L"Syria's stone",
    }, { // 3 AWSTR_QUEST_SWEEP_THE_MONSTERS_IN_THE_DUSTY_RUINS
L"塵土遺跡",
L"尘土遗迹",
L"Dusty Ruins",
    }, { // 4 AWSTR_QUEST_TAKE_BACK_ROSANNAS_MEMORABLE_RUBY
L"回憶之紅寶石",
L"回忆之红宝石",
L"Memorable ruby",
    }, { // 5 AWSTR_QUEST_ERRAND_FOR_GEDO
L"幫格多跑腿",
L"帮格多跑腿",
L"Errand for Gedo",
    }, { // 6 AWSTR_QUEST_SWEEP_THE_MONSTERS_IN_THE_COLD_RUINS
L"冰冷遺跡",
L"冰冷遗迹",
L"Cold Ruins",
    }, { // 7 AWSTR_QUEST_SCOUT_THE_PURGATORY_OF_JUDGMENTS
L"判決煉獄",
L"判决炼狱",
L"Purgatory",
    }, { // 8 AWSTR_QUEST_SCOUT_THE_REMAINS_OF_REINCARNATION
L"輪迴遺跡",
L"轮回遗迹",
L"Reincarnation",
    }, { // 9 AWSTR_QUEST_SCOUT_THE_CONTINUING_LAND
L"輪迴遺跡周邊",
L"轮回遗迹周边",
L"Continuing land",
    }, { // 10 AWSTR_QUEST_SCOUT_THE_IMMORTAL_REMAINS
L"不死的遺跡",
L"不死的遗迹",
L"Immortal",
    }, { // 11 AWSTR_QUEST_DESTROY_THIEVES_STAYING_SE_OF_KANFORE
L"消滅盜賊團",
L"消灭盗贼团",
L"Destroy thieves",
    }, { // 12 AWSTR_QUEST_HEAD_FOR_THE_MINING_TUNNEL_OF_YUGUNOS
L"前往調查坑道",
L"前往调查坑道",
L"Yugunos",
    }, { // 13 AWSTR_QUEST_MEET_WITH_THE_WIZARD_KIRUSHUTAT
L"晉見魔導師",
L"晋见魔导师",
L"Meet Wizard",
    }, { // 14 AWSTR_QUEST_TAKE_BACK_THE_SEAL_CRYSTAL
L"封印的水晶",
L"封印的水晶",
L"Seal Crystal",
    }, { // 15 AWSTR_QUEST_RETAKE_THE_SECURITY_CONTROL_FACILITY
L"防護控制設施",
L"防护控制设施",
L"Retake Facility",
    }, { // 16 AWSTR_QUEST_RECAPTURE_THE_POWER_SUPPLY_FACILITY
L"前往電源碉堡",
L"前往电源碉堡",
L"Recapture Faci.",
    }, { // 17 AWSTR_QUEST_DEFEAT_THE_DRAGONS
L"打倒巨龍",
L"打倒巨龙",
L"Dragon!",
    }, { // 18 AWSTR_QUEST_KILL_THE_TARANTULAS
L"剷除惡魔蜘蛛",
L"铲除恶魔蜘蛛",
L"Kill tarantulas",
    }, { // 19 AWSTR_QUEST_SEARCH_DEVALIOS_HIDDEN_WAREHOUSE
L"尋找非法證據",
L"寻找非法证据",
L"Devalio's",
    }, { // 20 AWSTR_QUEST_SWEEP_VICINITY_OF_S_CAMP_OF_YUGUNOS
L"消滅餘黨",
L"消灭余党",
L"Sweep vicinity",
    }, { // 21 AWSTR_QUEST_GET_THE_SACRED_RELIC_SACRED_WING
L"神聖之羽毛",
L"神圣之羽毛",
L"Sacred Wing",
    }, { // 22 AWSTR_QUEST_GET_THE_SACRED_RELIC_ANGELS_HAIR
L"天使之發",
L"天使之发",
L"Angel's Hair",
    }, { // 23 AWSTR_QUEST_DELIVER_THE_BISHOP_BERINIS_REPORT
L"報告書送達",
L"报告书送达",
L"Deliver report",
    }, { // 24 AWSTR_QUEST_EXPLORE_THE_REMAINS_OF_HEARTBEAT
L"鼓動之遺跡",
L"鼓动之遗迹",
L"Heartbeat",
    }, { // 25 AWSTR_QUEST_EXAMINE_THE_PLUMBING
L"鎮壓配管設施",
L"镇压配管设施",
L"plumbing",
    }, { // 26 AWSTR_QUEST_TRUTH_BEHIND_DEATH_OF_THE_ELF_RANGERS
L"全滅的真相",
L"全灭的真相",
L"Truth behind",
    }, { // 27 AWSTR_QUEST_MEET_WITH_SAINT_KNIGHT_LICARN
L"聖騎士萊鋼",
L"圣骑士莱刚",
L"Saint Knight",
    }, { // 28 AWSTR_QUEST_BREAK_THROUGH_THE_TOWER_OF_LICARN
L"衝破萊剛之塔",
L"冲破莱刚之塔",
L"Break through",
    }, { // 29 AWSTR_QUEST_GET_THE_SACRED_RELIC_ANGELS_NAIL
L"天使之指甲",
L"天使之指甲",
L"Angel's Nail",
    }, { // 30 AWSTR_QUEST_RESEARCH_THE_ANCIENT_RUINS
L"遠古之遺跡",
L"远古之遗迹",
L"Ancient Ruins",
    }, { // 31 AWSTR_QUEST_GET_AN_ANTIDOTE
L"取得解毒劑",
L"取得解毒剂",
L"Get an antidote",
    }, { // 32 AWSTR_QUEST_PUNITIVE_EXPEDITION_AGAINST_JURG
L"討伐賈爾格",
L"讨伐贾尔格",
L"Jurg",
    }, { // 33 AWSTR_QUEST_ERRANDS_FOR_MRS_MORRIS
L"幫摩裡司夫人",
L"帮摩里斯夫人",
L"Mrs. Morris",
    }, { // 34 AWSTR_QUEST_TAKE_BACK_THE_STOLEN_TEARS_OF_OBERON
L"歐貝隆之淚",
L"欧贝隆之泪",
L"Tears of Oberon",
    }, { // 35 AWSTR_QUEST_FIND_THE_ANCIENT_SHORT_SWORD
L"遠古之短刀",
L"远古之短刀",
L"Ancient Sword",
    }, { // 36 AWSTR_QUEST_GET_THE_SACRED_RELIC_ANGELS_MEMORY
L"天使之記憶",
L"天使之记忆",
L"Angel's Memory",
    }, { // 37 AWSTR_QUEST_DELIVER_THE_SACRED_RELICS_TO_ST_SENA
L"交給聖女賽娜",
L"交给圣女塞娜",
L"Deliver to Sena",
    }, { // 38 AWSTR_QUEST_GET_THE_BLUE_AND_GREEN_ORBS
L"藍、綠光球",
L"蓝、绿光球",
L"Blue Green Orbs",
    }, { // 39 AWSTR_QUEST_FIND_MR_MRS_JURGS_REMEMBRANCE
L"夫妻的紀念物",
L"夫妻的纪念物",
L"remembrance",
    }, { // 40 AWSTR_QUEST_GET_THE_RED_ORB
L"取得紅光球",
L"取得红光球",
L"Red Orb",
    }, { // 41 AWSTR_QUEST_RECAPTURE_THE_RUINS_OF_EXORCISM
L"退魔之遺跡",
L"退魔之遗迹",
L"Exorcism",
    }, { // 42 AWSTR_QUEST_HEAD_FOR_GOLIATES_MANSION
L"哥利亞提之館",
L"哥利亚提之馆",
L"Goliate Mansion",
    }, { // 43 AWSTR_QUEST_BEAT_THE_DEVIL_DIGNOSIS
L"打倒魔神",
L"打倒魔神",
L"Devil Dignosis",
    }, { // 44 AWSTR_QUEST_A_WISE_MAN_IN_RUINS_OF_THE_WISE
L"賢者之遺跡",
L"贤者之遗迹",
L"A wise man",
    }, { // 45 AWSTR_QUEST_LET_THE_JURG_PARTY_SURRENDER
L"餘黨的叛亂",
L"余党的叛乱",
L"Party surrender",
    }, { // 46 AWSTR_QUEST_SUBJECTION_OF_THE_FORT_OF_DEMONS
L"惡魔之碉堡",
L"恶魔之碉堡",
L"Fort of Demons",
    }, { // 47 AWSTR_QUEST_GO_TO_THE_FOREST_OF_MADNESS
L"瘋狂之森",
L"疯狂之森",
L"Madness",
    }
};
LPCWSTR APP_WSTR_TELEPORT_GATE[APP_WSTR_TELEPORT_GATE_COUNT][AVAILABLE_LANGUAGE_COUNT] = {
       { // 0 AWSTR_TELEPORT_GATE_REMOTE_TOWN
L"邊境之鎮",
L"边境之镇",
L"Remote Town",
    }, { // 1 AWSTR_TELEPORT_GATE_WASTELAND_OF_PILLARS
L"石柱荒地",
L"石柱荒地",
L"Wasteland of Pillars",
    }, { // 2 AWSTR_TELEPORT_GATE_DUSTY_RUINS_B4F
L"塵土遺跡 地下4樓",
L"尘土遗迹 地下4楼",
L"Dusty Ruins, B4F",
    }, { // 3 AWSTR_TELEPORT_GATE_DUSTY_RUINS_B5F
L"塵土遺跡 地下5樓",
L"尘土遗迹 地下5楼",
L"Dusty Ruins, B5F",
    }, { // 4 AWSTR_TELEPORT_GATE_COLD_SVALT_TOWN
L"寒冰暗妖精鎮",
L"寒冰暗妖精镇",
L"Cold Svalt Town",
    }, { // 5 AWSTR_TELEPORT_GATE_VAPOROUS_FOREST
L"蒸汽森林",
L"蒸汽森林",
L"Vaporous Forest",
    }, { // 6 AWSTR_TELEPORT_GATE_HANGED_MENS_FOREST
L"倒吊男之森",
L"倒吊男之森",
L"Hanged Men's Forest",
    }, { // 7 AWSTR_TELEPORT_GATE_FOREST_DIVIDED_LIKE_A_CROSS
L"裂成十字形的樹海",
L"裂成十字形的树海",
L"Forest Divided Like a Cross",
    }, { // 8 AWSTR_TELEPORT_GATE_THE_RUINS_OF_FIRE_SEA_OF_TREES
L"樹海燃燒後的遺跡",
L"树海燃烧后的遗迹",
L"The Ruins of Fire, Sea of Trees",
    }, { // 9 AWSTR_TELEPORT_GATE_COLD_RUINS_B3F
L"冰冷遺跡 地下3樓",
L"冰冷遗迹 地下3楼",
L"Cold Ruins, B3F",
    }, { // 10 AWSTR_TELEPORT_GATE_PURGATORY_OF_JUDGEMENTS_B1F
L"判決煉獄 地下1樓",
L"判决炼狱 地下1楼",
L"Purgatory of Judgements, B1F",
    }, { // 11 AWSTR_TELEPORT_GATE_IMMORTAL_REMAINS_B2F
L"不死的遺跡 地下2樓",
L"不死的遗迹 地下2楼",
L"Immortal Remains, B2F",
    }, { // 12 AWSTR_TELEPORT_GATE_TOWER_OF_ORDEAL
L"試煉之塔",
L"试炼之塔",
L"Tower of Ordeal",
    }, { // 13 AWSTR_TELEPORT_GATE_KANFORE_MINING_TOWN
L"煤礦之鎮 剛佛雷",
L"煤矿之镇 刚佛雷",
L"Kanfore, Mining Town",
    }, { // 14 AWSTR_TELEPORT_GATE_FOREST_OF_CLAWS
L"鉤爪之森",
L"钩爪之森",
L"Forest of Claws",
    }, { // 15 AWSTR_TELEPORT_GATE_CROSS_AGORA
L"十字礦場",
L"十字矿场",
L"Cross Agora",
    }, { // 16 AWSTR_TELEPORT_GATE_FOREST_OF_SPRITS
L"英靈之森",
L"英灵之森",
L"Forest of Sprits",
    }, { // 17 AWSTR_TELEPORT_GATE_FORT_OF_THIEVES
L"盜賊的碉堡",
L"盗贼的碉堡",
L"Fort of Thieves",
    }, { // 18 AWSTR_TELEPORT_GATE_FANANN_VILLAGE_OF_ELVES
L"精靈之村 法南",
L"精灵之村 法南",
L"Fanann, Village of Elves",
    }, { // 19 AWSTR_TELEPORT_GATE_MINING_TUNNEL_OF_YUGUNOS
L"優格諾斯坑道",
L"优格诺斯坑道",
L"Mining Tunnel of Yugunos",
    }, { // 20 AWSTR_TELEPORT_GATE_DRAGON_DEFENSE_WALLS
L"抗龍防禦壁之前",
L"抗龙防御壁之前",
L"Dragon Defense Walls",
    }, { // 21 AWSTR_TELEPORT_GATE_MINING_TUNNEL_OF_YUGUNOS_B3F
L"優格諾斯坑道 地下3樓",
L"优格诺斯坑道 地下3楼",
L"Mining Tunnel of Yugunos, B3F",
    }, { // 22 AWSTR_TELEPORT_GATE_POWER_SUPPLY_FACILLITY
L"封印之電源設施",
L"封印之电源设施",
L"Power Supply Facillity",
    }, { // 23 AWSTR_TELEPORT_GATE_TOWER_OF_ORDEAL_6F
L"試煉之塔 6樓",
L"试炼之塔 6楼",
L"Tower of Ordeal, 6F",
    }, { // 24 AWSTR_TELEPORT_GATE_TOWER_OF_ORDEAL_12F
L"試煉之塔 12樓",
L"试炼之塔 12楼",
L"Tower of Ordeal, 12F",
    }, { // 25 AWSTR_TELEPORT_GATE_SOUTH_CAMP_OF_YUGUNOS
L"優格諾斯南方軍營",
L"优格诺斯南方军营",
L"South Camp of Yugunos",
    }, { // 26 AWSTR_TELEPORT_GATE_TOWN_OF_ANTALUSIA
L"安德魯雪鎮",
L"安德鲁雪镇",
L"Town of Antalusia",
    }, { // 27 AWSTR_TELEPORT_GATE_MESRALD_BURIAL_GROUNDS
L"梅賽拉爾德古墳",
L"梅赛拉尔德古坟",
L"Mesrald Burial Grounds",
    }, { // 28 AWSTR_TELEPORT_GATE_PLAIN_OF_DIALOSE
L"迪雅羅賽平原",
L"迪雅罗赛平原",
L"Plain of Dialose",
    }, { // 29 AWSTR_TELEPORT_GATE_THE_WILDS_OF_RYUMYAKU
L"龍脈之荒野",
L"龙脉之荒野",
L"The Wilds of Ryumyaku",
    }, { // 30 AWSTR_TELEPORT_GATE_TOWN_OF_CALADO
L"卡拉得鎮",
L"卡拉得镇",
L"Town of Calado",
    }, { // 31 AWSTR_TELEPORT_GATE_TOWN_OF_LOSMANS
L"羅斯曼茲鎮",
L"罗斯曼兹镇",
L"Town of Losmans",
    }, { // 32 AWSTR_TELEPORT_GATE_FOREST_OF_ILBARNA
L"依爾巴那之森",
L"依尔巴那之森",
L"Forest of Ilbarna",
    }, { // 33 AWSTR_TELEPORT_GATE_PONSE_VILLAGE_OF_DWARVES
L"矮人之村 彭賽",
L"矮人之村 彭赛",
L"Ponse, Village of Dwarves",
    }, { // 34 AWSTR_TELEPORT_GATE_HILL_OF_HEAVEN
L"天翔之丘",
L"天翔之丘",
L"Hill of Heaven",
    }, { // 35 AWSTR_TELEPORT_GATE_THE_ROAD_OF_ATONEMENT
L"贖罪之道",
L"赎罪之道",
L"The Road of Atonement",
    }, { // 36 AWSTR_TELEPORT_GATE_VALLEY_OF_DYING_PEOPLE
L"逐漸毀滅者之谷",
L"逐渐消亡者之谷",
L"Valley of Dying People",
    }, { // 37 AWSTR_TELEPORT_GATE_SENAS_SMALL_SHRINE
L"聖女賽娜的祠堂",
L"圣女赛娜之祠堂",
L"Sena's Small Shrine",
    }, { // 38 AWSTR_TELEPORT_GATE_DARK_ELVES_HIDING_PLACE
L"黑暗天使的基地",
L"黑暗天使的基地",
L"Dark Elves Hiding Place",
    }, { // 39 AWSTR_TELEPORT_GATE_TOWER_OF_ORDEAL_17F
L"試煉之塔 17樓",
L"试炼之塔 17楼",
L"Tower of Ordeal, 17F",
    }, { // 40 AWSTR_TELEPORT_GATE_BEINI_VILLAGE
L"貝爾尼村",
L"贝尔尼村",
L"Beini Village",
    }, { // 41 AWSTR_TELEPORT_GATE_ENTO_VILLAGE
L"安特村",
L"安特村",
L"Ento Village",
    }, { // 42 AWSTR_TELEPORT_GATE_THE_RUINS_OF_KASHUGAL
L"卡修格爾遺跡前",
L"卡修格尔遗迹前",
L"The Ruins of Kashugal",
    }, { // 43 AWSTR_TELEPORT_GATE_LABYRINTH_OF_THE_LAKE
L"湖之迷宮",
L"湖之迷宫",
L"Labyrinth of the Lake",
    }, { // 44 AWSTR_TELEPORT_GATE_THE_ANCIENT_INSTITUTE
L"古代研究所前",
L"古代研究所前",
L"The Ancient Institute",
    }, { // 45 AWSTR_TELEPORT_GATE_THE_RUINS_OF_EXORCISM
L"退魔之遺跡前",
L"退魔之遗迹前",
L"The Ruins of Exorcism",
    }, { // 46 AWSTR_TELEPORT_GATE_GOLIATES_MANSION
L"哥利亞提之館",
L"哥利亚提之馆",
L"Goliate's Mansion",
    }, { // 47 AWSTR_TELEPORT_GATE_FOREST_OF_DEATH
L"終焉之森",
L"终焉之森",
L"Forest of Death",
    }, { // 48 AWSTR_TELEPORT_GATE_THE_ROAD_OF_THE_UNDERWORLD
L"冥府之道",
L"冥府之道",
L"The Road of The Underworld",
    }, { // 49 AWSTR_TELEPORT_GATE_FOREST_OF_MADNESS
L"瘋狂之森",
L"疯狂之森",
L"Forest of Madness",
    }, { // 50 AWSTR_TELEPORT_GATE_TOWER_OF_ORDEAL_TOP_FLOOR
L"試煉之塔 最上階",
L"试炼之塔 最上阶",
L"Tower of Ordeal, Top Floor",
    }
};

extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SEX[APP_WSTR_SEX_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_PROF[APP_WSTR_PROF_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_COMP[APP_WSTR_COMP_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_TELEPORT_PRESET[APP_WSTR_TELEPORT_PRESET_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SCENARIO[APP_WSTR_SCENARIO_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_MAGIC[APP_WSTR_MAGIC_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_QUEST[APP_WSTR_QUEST_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_TELEPORT_GATE[APP_WSTR_TELEPORT_GATE_COUNT][AVAILABLE_LANGUAGE_COUNT];




