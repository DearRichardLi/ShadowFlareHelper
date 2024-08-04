#include <Windows.h>


#ifndef _SF_HELPER_FUNC
#define _SF_HELPER_FUNC

#define PLAYER_NAME_LEN      20
#define MAP_NAME_LEN        256

BOOL OpenSF(void);
void OpenSFLogger(HWND hwndEditInitLog);
BOOL BindSF(void);
void BindSFLogger(HWND hwndEditInitLog);
BOOL ReadVal(void* addr, void* val, size_t nSize);
BOOL WriteVal(void* addr, void* val, size_t nSize);
void ReadAndSetValues(HWND hwndTab);
void GetGameModeAndOnlineRole(void);
void DisplayGameModeAndOnlineRole(HWND hwndTab);
void GetPlayerName(BYTE *str);
void DisplayPlayerName(HWND hwndTab, BYTE *str);
void ApplyPlayerName(HWND hwndTab);
LONG64 KeepNumWStrInRange(WCHAR* buf, size_t nSize, LONG64 lBound, LONG64 hBound, BOOL _Modify, int _Radix);
void GetAndDisplayPlayerLV(HWND hwndTab);
void ApplyPlayerLV(HWND hwndTab);
void GetAndDisplayPlayerSex(HWND hwndTab);
void ApplyPlayerSex(HWND hwndTab);
void GetAndDisplayPlayerEXP(HWND hwndTab);
void ApplyPlayerEXP(HWND hwndTab);
void GetAndDisplayPlayerProf(HWND hwndTab);
void ApplyPlayerProf(HWND hwndTab);
void GetAndDisplayPlayerProfToBe(HWND hwndTab);
void ApplyPlayerProfToBe(HWND hwndTab);
void GetAndDisplayCompanionLV(HWND hwndTab);
void ApplyCompanionLV(HWND hwndTab);
void GetAndDisplayCompanionID(HWND hwndTab);
void ApplyCompanionID(HWND hwndTab);
void GetAndDisplayCompanionEXP(HWND hwndTab);
void ApplyCompanionEXP(HWND hwndTab);

#endif /* SFHelperFunc.h */