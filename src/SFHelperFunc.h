#include <Windows.h>


#ifndef _SF_HELPER_FUNC
#define _SF_HELPER_FUNC



void TimeLogger(HWND hwndEditLog, BOOL lineFeed);
BOOL OpenSF(void);
void OpenSFLogger(HWND hwndEditLog);
BOOL ApplyGameVersion(HWND hwndParent);
BOOL BindSF(void);
void BindSFLogger(HWND hwndEditLog);
BOOL ReadVal(void* addr, void* val, size_t nSize);
BOOL WriteVal(void* addr, void* val, size_t nSize);
BOOL GetAndDisplayValues(HWND hwndParent);
BOOL GetGameModeAndOnlineRole(void);
BOOL DisplayGameModeAndOnlineRole(HWND hwndParent);
void GameStringToAPP(LPCH str, LPWSTR wstr, __int32 cchWideChar);
void APPStringToGame(LPCH str, LPWSTR wstr, __int32 cchWideChar);
BOOL GetAndDisplayPlayerName(HWND hwndParent);
BOOL ApplyPlayerName(HWND hwndParent);
LONG64 NumWStrInRange(WCHAR* buf, size_t nSize, 
        LONG64 lBound, LONG64 hBound, BOOL _Modify, 
        __int32 _Radix);
LONG64 KeepWndNumWStrInRange(HWND hwndParent, int hwndID, 
        size_t nSize, LONG64 lBound, LONG64 hBound, BOOL _Modify, 
        __int32 _Radix);
BOOL GetAndDisplayPlayerLV(HWND hwndParent);
BOOL ApplyPlayerLV(HWND hwndParent);
BOOL GetAndDisplayPlayerSex(HWND hwndParent);
BOOL ApplyPlayerSex(HWND hwndParent);
BOOL GetAndDisplayPlayerEXP(HWND hwndParent);
BOOL ApplyPlayerEXP(HWND hwndParent);
BOOL GetAndDisplayPlayerProf(HWND hwndParent);
BOOL ApplyPlayerProf(HWND hwndParent);
BOOL GetAndDisplayPlayerProfToBe(HWND hwndParent);
BOOL ApplyPlayerProfToBe(HWND hwndParent);
BOOL GetAndDisplayCompanionLV(HWND hwndParent);
BOOL ApplyCompanionLV(HWND hwndParent);
BOOL GetAndDisplayCompanionID(HWND hwndParent);
BOOL ApplyCompanionID(HWND hwndParent);
BOOL GetAndDisplayCompanionEXP(HWND hwndParent);
BOOL ApplyCompanionEXP(HWND hwndParent);
BOOL GetPlayerPositionX(void);
BOOL GetPlayerPositionY(void);
BOOL DisplayPlayerPosition(HWND hwndParent);
void PlayerMoveAxisX(BOOL isNegative);
void PlayerMoveAxisY(BOOL isNegative);
BOOL ApplyPlayerPositionX(void);
BOOL ApplyPlayerPositionY(void);
LRESULT CALLBACK LowLevelKeyboardProc(
        DWORD nCode, WPARAM wParam, LPARAM lParam);
void GlobalKeyboardHook(void);
void CheckGameCloseOrLogout(void);
void CloseAllExtraThread(void);
void SFHelperCreateThread(pthread_t *th, 
        const pthread_attr_t *attr, 
        void *(* func)(void *), void *arg);
void SFHelperJoinThread(pthread_t t, void **res);
void HookLogger(HWND hwndEditLog);
void RefreshLogger(HWND hwndEditLog);
BOOL DisplayHookStatus(HWND hwndParent);
BOOL GetAndDisplayMapID(HWND hwndParent);
BOOL GetAndDisplayMapName(HWND hwndParent);
BOOL GetAndDisplayMapGateID(HWND hwndParent);
BOOL DisplayMoveDistance(HWND hwndParent);
BOOL DisplayMoveDelay(HWND hwndParent);
BOOL DisplayRefreshDelay(HWND hwndParent);
BOOL GetTabs(void);
BOOL CloseAllTabs(void);
BOOL PressCloseTabButton(void);
BOOL SetXYDefault(HWND hwndParent);
BOOL SetGateIDDefault(HWND hwndParent);
BOOL ApplyTeleportPreset(HWND hwndParent);
BOOL PresetContentChange(HWND hwndParent);
BOOL ApplyTeleportMapID(HWND hwndParent);
BOOL ApplyTeleport(HWND hwndParent);
BOOL OpenWarehouseTab(void);
BOOL OpenGaintWarehouseTab(void);
BOOL OpenCustomOutfitTab(void);
BOOL PauseGame(void);
BOOL InfinitePower(void);
BOOL CompanionRevive(void);
BOOL ExtraLandMine(void);
BOOL ExtraLandMinePower(void);
BOOL BeRich(void);
BOOL NoMonsterDisplay(void);
BOOL MagicLVto30(void);
BOOL CrazySpeed(void);
BOOL GodMode(void);
BOOL ExtendAtkRange(void);
BOOL ReviveEneny(void);
BOOL Suicide(void);
BOOL GetAndDisplayMagicStatus(HWND hwndParent);
BOOL UnlockMagic(HWND hwndParent, __int32 index);
BOOL ApplyMagicLV(HWND hwndParent, __int32 index);
BOOL ApplyMagicEXP(HWND hwndParent, __int32 index);

#endif /* SFHelperFunc.h */