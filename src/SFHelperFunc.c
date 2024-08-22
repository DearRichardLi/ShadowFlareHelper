#include <Windows.h>
#include <psapi.h> 
#include <pthread.h>

#include "SFHelperAddr.h"
#include "SFHelperStd.h"
#include "SFHelperException.h"
#include "SFHelperWindows.h"
#include "SFHelperLanguage.h"
#include "SFHelperFunc.h"
#include "SFHelperResource.h"



extern LPCWSTR SF_EXE_Filename;
extern const Version GameVersions[SF_VERSION_COUNT];
extern Hack_Statu_Info Hack_Status;
extern SF_Window_Info SF_Window;
extern Hook_Move_Info Hook_Move;
extern SF_Tab_Info SF_Tab;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern LPCWSTR APP_WSTR_SCENARIO[APP_WSTR_SCENARIO_COUNT][AVAILABLE_LANGUAGE_COUNT];
extern const Teleport_Preset_Info Teleport_Preset[TELEPORT_PRESET_COUNT];
extern const __int32 Scenario_Map_ID[SCENARIO_COUNT];

void TimeLogger(HWND hwndEditLog, BOOL lineFeed){
    WCHAR buffer[16] = {0};
    SYSTEMTIME st;
    GetLocalTime(&st);
    swprintf_s(buffer, sizeof(buffer), 
            L"%02d:%02d:%02d.%03d", 
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    AppendText(hwndEditLog, buffer, lineFeed);
}
BOOL OpenSF(void){
    Hack_Status.LastErrorCode = APP_NORMAL;
    if(SF_Window.hWnd != NULL){
        Hack_Status.LastErrorCode = ERR_SF_SFEXE_ALREADY_RUNNING;
        return FALSE;
    } else if(PathFileExistsW(SF_EXE_Filename) == FALSE) {
        Hack_Status.LastErrorCode = ERR_SF_SFEXE_NOT_FOUND;
        return FALSE;
    } else{
        ShellExecuteW(NULL, L"open", SF_EXE_Filename, NULL, NULL, SW_SHOWNORMAL);
    }
    return TRUE;
}
void OpenSFLogger(HWND hwndEditLog){
    if(Hack_Status.LastErrorCode == ERR_SF_SFEXE_ALREADY_RUNNING){
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_SF_RUNNING][Hack_Status.App_Language], TRUE);
        return;
    } else if(Hack_Status.LastErrorCode == ERR_SF_SFEXE_NOT_FOUND){
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_SFEXE_NOT_FOUND][Hack_Status.App_Language], TRUE);
        return;
    } else{
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_SFEXE_FOUND][Hack_Status.App_Language], TRUE);
    }
}
BOOL ApplyGameVersion(HWND hwndParent){
    // integer, from 0 to SF_VERSION_COUNT
    __int32 index = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_GAMEVERSION), CB_GETCURSEL, 0, 0); 
    SF_Window.SF_Version = index;
    return TRUE;
}
BOOL BindSF(void){
    Hack_Status.LastErrorCode = APP_NORMAL;
    SF_Window.hWnd = FindWindowW(NULL, GameVersions[SF_Window.SF_Version].WindowTitle);
    if(SF_Window.hWnd == NULL){ // ----Failed to find ShadowFlare.exe Window---- //
        Hack_Status.LastErrorCode = ERR_SF_GET_WINDOW_FAILED;
        return FALSE;
    }
        // ----Try to get TID & PID---- //
    SF_Window.TID = GetWindowThreadProcessId(SF_Window.hWnd, &SF_Window.PID);
    if(SF_Window.TID == 0){ // ----Failed to get TID---- //
        Hack_Status.LastErrorCode = ERR_SF_GET_TID_FAILED;
        return FALSE;
    }
    if(SF_Window.PID == 0){ // ----Failed to get PID---- //
        Hack_Status.LastErrorCode = ERR_SF_GET_PID_FAILED;
        return FALSE;
    }
        // ----Try to get HANDLE---- //
    SF_Window.SF_Handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, SF_Window.PID);
    if(SF_Window.SF_Handle == (HANDLE)0){ // ----Failed to get HANDLE---- // 
        if(GetLastError() == 5){ // ----Permission Denied---- // 
            Hack_Status.LastErrorCode = ERR_APP_PERMISSION_DENIED;
        } else{
            Hack_Status.LastErrorCode = ERR_SF_GET_HANDLE_FAILED;
        }
        return FALSE;
    } 
        // ----Try to get the entry of Shadowflare.exe, not the DLLs---- //
    DWORD dwRet = 0;
    HMODULE hModule[128] = {0}; // ----The List of Modules---- //
    DWORD bRet = EnumProcessModulesEx(SF_Window.SF_Handle, (HMODULE*)hModule, sizeof(hModule), &dwRet, 0x03);
    SF_Window.Module_Count = dwRet / sizeof(HMODULE);
    if(SF_Window.Module_Count == 0 || bRet == FALSE){ // ----Failed to get Process Modules---- //
        Hack_Status.LastErrorCode = ERR_SF_GET_PROCESS_MODULES_FAILED;
        return FALSE;
    }
        // ----Base Addr is the Addr of 1st Module---- //
    SF_Window.Base_hModule = hModule[0]; 
    
    /*
        // ----Print every module with address---- //
    FILE *file = fopen("Module_address.log", "a"); 
    WCHAR lpBaseName[128] = {0};
    for(__int32 i = 0; i < Module_Num; i++){
        GetModuleBaseNameW(SF_Window.SF_Handle, hModule[i], lpBaseName, sizeof(lpBaseName));
        fwprintf_s(file, L"%-3d %-50s: %#x\n", i, lpBaseName, hModule[i]);
    }
    fclose(file);
    */
    return TRUE;
}
void BindSFLogger(HWND hwndEditLog){
    ClearText(hwndEditLog);
    WCHAR buffer[128] = {0};
    TimeLogger(hwndEditLog, TRUE);
    if(SF_Window.hWnd == NULL){ // ----Failed to find ShadowFlare.exe Window---- //
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_SFWND_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Found ShadowFlare.exe Window---- //
    swprintf_s(buffer, sizeof(buffer), L"0x%x", (void*)SF_Window.hWnd); //%p to print full LONG_PTR
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_SFWND_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditLog, buffer, TRUE);
    if(SF_Window.TID == 0){ // ----Failed to get TID---- //
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_TID_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Got TID---- //
    swprintf_s(buffer, sizeof(buffer), L"%d", (__int32)SF_Window.TID);
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_TID_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditLog, buffer, TRUE);
    if(SF_Window.PID == 0){ // ----Failed to get PID---- //
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_PID_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Got PID---- //
    swprintf_s(buffer, sizeof(buffer), L"%d", (__int32)SF_Window.PID);
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_PID_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditLog, buffer, TRUE);
    if(SF_Window.SF_Handle == (HANDLE)0){ // ----Failed to get HANDLE---- // 
        if(GetLastError() == 5){ // ----Permission Denied---- // 
            AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_PERMISSION_DENIED][Hack_Status.App_Language], TRUE);
        } else{
            AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_HANDLE_FAIL][Hack_Status.App_Language], TRUE);
        }
        return;
    } 
        // ----Got HANDLE---- // 
    swprintf_s(buffer, sizeof(buffer), L"%u", SF_Window.SF_Handle);
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_HANDLE_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditLog, buffer, TRUE);
    if(SF_Window.Module_Count == 0){ // ----Failed to get Process Modules---- //
        AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_MODULE_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Got the entry of Shadowflare.exe---- //
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_GET_MODULE_SUC][Hack_Status.App_Language], TRUE);
        // ----Base Addr is the Addr of 1st Module---- //
    swprintf_s(buffer, sizeof(buffer), L"0x%x", (void *)SF_Window.Base_hModule);
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_SF_BASE_ADDR][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditLog, buffer, TRUE);
        // Bind Success
    AppendText(hwndEditLog, APP_WSTR[AWSTR_APP_SF_BIND_SUC][Hack_Status.App_Language], 1);
}
BOOL ReadVal(void* addr, void* val, size_t nSize){
    BOOL ret = ReadProcessMemory(SF_Window.SF_Handle, (LPVOID)addr, val, nSize, NULL);
    if(ret == FALSE){
        Hack_Status.LastErrorCode = ERR_APP_READ_MEMORY_FAILED;
    }
    return ret;
}
BOOL WriteVal(void* addr, void* val, size_t nSize){
    BOOL ret = WriteProcessMemory(SF_Window.SF_Handle, (LPVOID)addr, val, nSize, NULL);
    if(ret == FALSE){
        Hack_Status.LastErrorCode = ERR_APP_WRITE_MEMORY_FAILED;
    }
    return ret; 
}
BOOL GetAndDisplayValues(HWND hwndParent){
    if(    GetAndDisplayPlayerName(hwndParent)
        && GetAndDisplayPlayerLV(hwndParent)
        && GetAndDisplayPlayerSex(hwndParent)
        && GetAndDisplayPlayerEXP(hwndParent)
        && GetAndDisplayPlayerProf(hwndParent)
        && GetAndDisplayPlayerProfToBe(hwndParent)
        && GetAndDisplayCompanionLV(hwndParent)
        && GetAndDisplayCompanionID(hwndParent)
        && GetAndDisplayCompanionEXP(hwndParent)
        && GetPlayerPositionX()
        && GetPlayerPositionY()
        && DisplayHookStatus(hwndParent)
        && DisplayPlayerPosition(hwndParent)
        && GetAndDisplayMapID(hwndParent)
        && GetAndDisplayMapName(hwndParent)
        && GetAndDisplayMapGateID(hwndParent)
        && GetTabs()
        && GetAndDisplayMagicStatus(hwndParent)
        && GetAndDisplayGiantWarehouseIndex(hwndParent)
    ){
        return TRUE;
    } else{
        if(Hack_Status.LastErrorCode != APP_NORMAL){
            ExceptionHandler();
        }
        return FALSE;
    }
    return TRUE;
}
BOOL GetGameModeAndOnlineRole(void){
    ULONG_PTR Addr1 = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] + 
            STATS_IMPORTANT_POINTER_3_P),
            (void*)&Addr1, sizeof(DWORD));
    ReadVal((void*)(Addr1 + sizeof(DWORD) * 2), 
            &Hack_Status.Client_Index, sizeof(DWORD));

    ULONG_PTR Addr2 = 0;
    ReadVal((void*)(Addr1 + sizeof(DWORD)), 
            (void*)&Addr2, sizeof(DWORD));
    
    ULONG_PTR Addr3 = 0;
    ReadVal((void*)(Addr2 + sizeof(DWORD) * Hack_Status.Client_Index), 
            (void*)&Addr3, sizeof(DWORD));
    Hack_Status.Character_Attribute_P = Addr3;
    
    ReadVal((void*)(Addr3), 
            &Hack_Status.Game_Mode, sizeof(DWORD));
    return TRUE;
}
BOOL DisplayGameModeAndOnlineRole(HWND hwndParent){
    switch (Hack_Status.Game_Mode){
    case 0: // Single Game
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_GAMEMODE_SINGLE][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_GAMEMODE_SINGLE][Hack_Status.App_Language]);
        break;
    case 1: case 2: // Online Game, host&client
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_GAMEMODE_ONLINE][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_GAMEMODE_ONLINE][Hack_Status.App_Language]);
        if (Hack_Status.Client_Index == 0){
            AppendText(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE), L"Host", FALSE);
        } else{
            AppendText(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE), L"Client ", FALSE);
            WCHAR buffer[2] = {0};
            _ultow_s(Hack_Status.Client_Index, buffer, 2, 10);
            AppendText(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE), buffer, FALSE);
            AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
                    APP_WSTR[AWSTR_APP_HINT_ONLINE_RISKY][Hack_Status.App_Language], FALSE);
        }
        break;
    default:
        Hack_Status.LastErrorCode = ERR_SF_NOT_LOGIN;
        return FALSE;
    }
    return TRUE;
}
void GameStringToAPP(LPCH str, LPWSTR wstr, __int32 cchWideChar){
    switch(SF_Window.SF_Version){
    case 0: // CHT encoding: Big 5
        MultiByteToWideChar(950, 0, str, -1, wstr, cchWideChar);
        break;
    case 1: // CHN encoding: GBK
        MultiByteToWideChar(936, 0, str, -1, wstr, cchWideChar);
        break;
    case 2: // ENG encoding: ANSI
        MultiByteToWideChar(437, 0, str, -1, wstr, cchWideChar);
        break;
    case 3: // JPN encoding: Shift-JIS
        MultiByteToWideChar(932, 0, str, -1, wstr, cchWideChar);
        break;
    case 4: // KOR endocing: Euc-kr?? 51949(euc) or 949?
        // MultiByteToWideChar(949, 0, str, -1, wstr, cchWideChar);
        MultiByteToWideChar(51949, 0, str, -1, wstr, cchWideChar);
    }
}
void APPStringToGame(LPCH str, LPWSTR wstr, __int32 cchWideChar){
    switch(SF_Window.SF_Version){
    case 0: // CHT encoding: Big 5
        WideCharToMultiByte(950, 0, wstr, cchWideChar, str, -1, NULL, NULL);
        break;
    case 1: // CHN encoding: GBK
        WideCharToMultiByte(936, 0, wstr, cchWideChar, str, -1, NULL, NULL);
        break;
    case 2: // ENG encoding: ANSI
        WideCharToMultiByte(437, 0, wstr, cchWideChar, str, -1, NULL, NULL);
        break;
    case 3: // JPN encoding: Shift-JIS
        WideCharToMultiByte(932, 0, wstr, cchWideChar, str, -1, NULL, NULL);
        break;
    case 4: // KOR endocing: Euc-kr?? 51949(euc) or 949?
        // WideCharToMultiByte(949, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
        WideCharToMultiByte(51949, 0, wstr, cchWideChar, str, -1, NULL, NULL);
    }
}
BOOL GetAndDisplayPlayerName(HWND hwndParent){
    char str[PLAYER_NAME_LEN] = {0}; //Player name max_len is 20 bytes in SF
    WCHAR wstr[PLAYER_NAME_LEN] = {0};
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_NAME), 
            (void*)str, sizeof(char) * PLAYER_NAME_LEN);
    GameStringToAPP(str, wstr, PLAYER_NAME_LEN);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME), wstr);
    return TRUE;
}
BOOL ApplyPlayerName(HWND hwndParent){
    /*
     * funny here. IDN weather it is because my PC is CN locale.
     * No need to Get window text with WCHAR and transform to multybyte.
     * just need to Get with ANSI version. seems there is a auto transform
     */
    // WCHAR wstr[PLAYER_NAME_LEN];
    char str[PLAYER_NAME_LEN] = {0};
    GetWindowTextA(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME), str, PLAYER_NAME_LEN);
    // APPStringToGame(str, wstr, PLAYER_NAME_LEN);
    if(str[PLAYER_NAME_LEN-1] != 0){
        str[PLAYER_NAME_LEN-1] = 0;
        AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
                APP_WSTR[AWSTR_APP_STRING_OVERFLOW][Hack_Status.App_Language], TRUE);
    }
    WriteVal((void*)(Hack_Status.Character_Attribute_P + CA_PLAYER_NAME), 
            (void*)str, sizeof(char) * PLAYER_NAME_LEN);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + CA_PLAYER_NAME_2), 
            (void*)str, sizeof(char) * PLAYER_NAME_LEN);
    return TRUE;
}
LONG64 NumWStrInRange(WCHAR* buf, size_t nSize, 
        LONG64 lBound, LONG64 hBound, BOOL _Modify, __int32 _Radix){
    LONG64 num = _wtoi64(buf);
    num = num<lBound? lBound: num>hBound? hBound: num;
    if(_Modify) 
        _i64tow_s(num, buf, nSize, _Radix);
    return num;
}
LONG64 KeepWndNumWStrInRange(HWND hwndParent, int hwndID, size_t nSize, 
        LONG64 lBound, LONG64 hBound, BOOL _Modify, __int32 _Radix){
    WCHAR buffer[nSize];
    GetWindowTextW(GetDlgItem(hwndParent, hwndID), buffer, nSize);
    LONG64 num = NumWStrInRange(buffer, nSize, lBound, hBound, _Modify, _Radix);
    SetWindowTextW(GetDlgItem(hwndParent, hwndID), buffer);
    SendMessageW(GetDlgItem(hwndParent, hwndID), EM_SETSEL, nSize - 1, nSize - 1);
    return num;
}
BOOL GetAndDisplayPlayerLV(HWND hwndParent){
    __int32 LV = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV), 
            (void*)&LV, sizeof(__int32));
    WCHAR buffer[4] = {0};
    _itow_s(LV, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_LV), buffer);
    return TRUE;
}
BOOL ApplyPlayerLV(HWND hwndParent){
    WCHAR buffer[4] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_LV), buffer, 4);
    __int32 LV = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV), 
            (void*)&LV, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV_2), 
            (void*)&LV, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayPlayerSex(HWND hwndParent){
    __int32 Sex = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_SEX), 
            (void*)&Sex, sizeof(__int32));
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), 
            CB_SETCURSEL, Sex, 0);
    return TRUE;
}
BOOL ApplyPlayerSex(HWND hwndParent){
    __int32 Sex = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), 
            CB_GETCURSEL, 0, 0); 
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_SEX), 
            (void*)&Sex, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_SEX_2), 
            (void*)&Sex, sizeof(__int32));
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
            APP_WSTR[AWSTR_APP_HINT_RELOAD_SAVEFILE][Hack_Status.App_Language], TRUE);
    return TRUE;
}
BOOL GetAndDisplayPlayerEXP(HWND hwndParent){
    __int32 EXP = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_EXP), 
            (void*)&EXP, sizeof(__int32));
    WCHAR buffer[10] = {0};
    _itow_s(EXP, buffer, 10, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_EXP), buffer);
    return TRUE;
}
BOOL ApplyPlayerEXP(HWND hwndParent){
    WCHAR buffer[10] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_EXP), buffer, 10);
    __int32 EXP = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_EXP), 
            (void*)&EXP, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayPlayerProf(HWND hwndParent){
    __int32 Prof = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PROFESSION), 
            (void*)&Prof, sizeof(__int32));
    switch(Prof){
    case P_C_HUNTER:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 0, 0);
        break;
    case P_C_SWORDMAN:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 1, 0);
        break;
    case P_C_WITCH:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 2, 0);
        break;
    case P_C_MERCENARY:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 3, 0);
        break;
    }
    return TRUE;
}
BOOL ApplyPlayerProf(HWND hwndParent){
    __int32 Prof = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
            CB_GETCURSEL, 0, 0); 
        Prof = Prof == 0? P_C_HUNTER:
                Prof == 1? P_C_SWORDMAN:
                Prof == 2? P_C_WITCH:
                Prof == 3? P_C_MERCENARY: P_C_MERCENARY;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PROFESSION), 
            (void*)&Prof, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PROFESSION_2), 
            (void*)&Prof, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayPlayerProfToBe(HWND hwndParent){
    __int32 ProfToBe = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PROFESSION_TO_BE), 
            (void*)&ProfToBe, sizeof(__int32));
    switch(ProfToBe){
        // can not become Mercenary, so no need to consider case 16
    case P_C_HUNTER:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
                CB_SETCURSEL, 0, 0);
        break;
    case P_C_SWORDMAN:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
                CB_SETCURSEL, 1, 0);
        break;
    case P_C_WITCH:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
                CB_SETCURSEL, 2, 0);
        break;
    }
    return TRUE;
}
BOOL ApplyPlayerProfToBe(HWND hwndParent){
    __int32 ProfToBe = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
        CB_GETCURSEL, 0, 0); 
    ProfToBe = ProfToBe == 0? P_C_HUNTER:
            ProfToBe == 1? P_C_SWORDMAN:
            ProfToBe == 2? P_C_WITCH: P_C_WITCH;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PROFESSION_TO_BE), 
            (void*)&ProfToBe, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PROFESSION_TO_BE_2), 
            (void*)&ProfToBe, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayCompanionLV(HWND hwndParent){
    __int32 CompanionLV = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_LV), 
            (void*)&CompanionLV, sizeof(__int32));
    WCHAR buffer[3] = {0};
    _itow_s(CompanionLV, buffer, 3, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV), buffer);
    return TRUE;
}
BOOL ApplyCompanionLV(HWND hwndParent){
    WCHAR buffer[3] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV), buffer, 3);
    __int32 CompanionLV = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_LV), 
            (void*)&CompanionLV, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_LV_2), 
            (void*)&CompanionLV, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayCompanionID(HWND hwndParent){
    __int32 CompanionID = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_ID), 
            (void*)&CompanionID, sizeof(__int32));
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), 
            CB_SETCURSEL, CompanionID, 0);
    return TRUE;
}
BOOL ApplyCompanionID(HWND hwndParent){
    __int32 CompanionID = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), 
            CB_GETCURSEL, 0, 0); 
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_ID), 
            (void*)&CompanionID, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_ID_2), 
            (void*)&CompanionID, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayCompanionEXP(HWND hwndParent){
    __int32 CompanionEXP = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_EXP), 
            (void*)&CompanionEXP, sizeof(__int32));
    WCHAR buffer[4] = {0};
    _itow_s(CompanionEXP, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP), buffer);
    return TRUE;
}
BOOL ApplyCompanionEXP(HWND hwndParent){
    WCHAR buffer[4] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP), buffer, 4);
    __int32 CompanionEXP = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_EXP), 
            (void*)&CompanionEXP, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_EXP_2), 
            (void*)&CompanionEXP, sizeof(__int32));
    return TRUE;
}
BOOL GetPlayerPositionX(void){
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_POSITION_X), 
            (void*)&Hook_Move.X, sizeof(__int32));
    return TRUE;
}
BOOL GetPlayerPositionY(void){
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_POSITION_Y), 
            (void*)&Hook_Move.Y, sizeof(__int32));
    return TRUE;
}
BOOL DisplayPlayerPosition(HWND hwndParent){
    WCHAR buffer[12] = {0};
    _itow_s(Hook_Move.X, buffer, 12, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_X), buffer);
    _itow_s(Hook_Move.Y, buffer, 12, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_Y), buffer);
    return TRUE;
}
void PlayerMoveAxisX(BOOL isNegative){
    Hook_Move.X += Hook_Move.Move_Distance * (-1 + ((__int32)isNegative<<1));
}
void PlayerMoveAxisY(BOOL isNegative){
    Hook_Move.Y += Hook_Move.Move_Distance * (-1 + ((__int32)isNegative<<1));
}
BOOL ApplyPlayerPositionX(void){
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_POSITION_X), 
            (void*)&Hook_Move.X, sizeof(__int32));
    return TRUE;
}
BOOL ApplyPlayerPositionY(void){
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_POSITION_Y), 
            (void*)&Hook_Move.Y, sizeof(__int32));
    return TRUE;
}
LRESULT CALLBACK LowLevelKeyboardProc(DWORD nCode, WPARAM wParam, LPARAM lParam){
    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;
    BOOL movable = !(
            (SF_Tab.Tab_Shop             || SF_Tab.Tab_Quest       || 
             SF_Tab.Tab_Help             || SF_Tab.Tab_Esc_Menu    || 
             SF_Tab.Tab_Customize_Outfit || SF_Tab.Tab_Blackjack)
            ||
            ((SF_Tab.Tab_Status          || SF_Tab.Tab_Magic       ||
              SF_Tab.Tab_Warehouse       || SF_Tab.Tab_G_Warehouse ||
              SF_Tab.Tab_Teleport_Gates  || SF_Tab.Tab_Minimap)
             &&
             (SF_Tab.Tab_Item            || SF_Tab.Tab_Special_Item)
            )
    );
    if(GetForegroundWindow() == SF_Window.hWnd && movable &&
            (ks->flags == 0 || ks->flags == 1)){
        GetPlayerPositionX();
        GetPlayerPositionY();
        switch(ks->vkCode){ 
        case VK_NUMPAD1:     // numpad 1, SOUTH
        // case 0x46:           // F, SOUTH
            PlayerMoveAxisY(TRUE); 
            break;
        case VK_NUMPAD3:     // numpad 3, EAST
        // case 0x47:           // G, EAST
            PlayerMoveAxisX(TRUE); 
            break;
        case VK_NUMPAD7:     // numpad 7, WEST
        // case 0x54:           // T, WEST
            PlayerMoveAxisX(FALSE); 
            break;
        case VK_NUMPAD9:     // numpad 9, NORTH
        // case 0x59:           // Y, NORTH
            PlayerMoveAxisY(FALSE); 
            break;
        case VK_DOWN:                         // Down arrow
            if(SF_Tab.Tab_Minimap)
                break;
        case VK_NUMPAD2: case VK_NUMPAD5:     // numpad 2 & 5 
            PlayerMoveAxisX(TRUE); 
            PlayerMoveAxisY(TRUE); 
            break;
        case VK_LEFT:                         // Left arrow
            if(SF_Tab.Tab_Minimap)
                break;
        case VK_NUMPAD4:                      // numpad 4
            PlayerMoveAxisX(FALSE); 
            PlayerMoveAxisY(TRUE); 
            break;
        case VK_RIGHT:                        // Right arrow
            if(SF_Tab.Tab_Minimap)
                break;
        case VK_NUMPAD6:                      // numpad 6
            PlayerMoveAxisX(TRUE); 
            PlayerMoveAxisY(FALSE); 
            break;
        case VK_UP:                           // UP arrow
            if(SF_Tab.Tab_Minimap)
                break;
        case VK_NUMPAD8:                      // numpad 8
            PlayerMoveAxisX(FALSE); 
            PlayerMoveAxisY(FALSE); 
            break;
        } 
        ApplyPlayerPositionX();
        ApplyPlayerPositionY();
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam); 
}
void GlobalKeyboardHook(void){
    HHOOK keyboardHook = SetWindowsHookExW(
            WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, NULL, 0);
    if(keyboardHook == 0){
        Hack_Status.LastErrorCode = ERR_APP_KEYBOARD_HOOK_FAIL;
        return;
    }
    Hack_Status.isGlobal_Keyboard_Hooked = TRUE;
    MSG msg;
    while(Hack_Status.isGlobal_Keyboard_Hooked){
        if(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        Sleep(Hook_Move.Move_Delay);
    }
    UnhookWindowsHookEx(keyboardHook);
}
void CheckGameCloseOrLogout(void){
    HWND hwnd = FindWindowW(L"SFHelperWindowClass", 
            APP_WSTR[AWSTR_WNDNAME][Hack_Status.App_Language]);
    while(Hack_Status.isBind_Game){
        DWORD flag = WaitForSingleObject(SF_Window.SF_Handle, 
                DEFAULT_CHECK_GAME_CLOSED_WAIT_MILLISECONDS);
        if(flag == 0){
            Hack_Status.isBind_Game = FALSE;
            Hack_Status.LastErrorCode = ERR_SF_CLOSED;
            SendMessageW(hwnd, WM_GAME_CLOSED, 0, 0);
        } else{
            DWORD GameLogin = 0;
            ReadVal((void*)(Hack_Status.Character_Attribute_P), 
                    (void*)&GameLogin, sizeof(DWORD));
            if(GameLogin > 1){
                Hack_Status.isBind_Game = FALSE;
                Hack_Status.LastErrorCode = ERR_SF_LOGOUT;
            SendMessageW(hwnd, WM_GAME_LOGOUT, 0, 0);
            }
        }
        if(Hack_Status.LastErrorCode != APP_NORMAL){
            ExceptionHandler();
            return;
        }
        Sleep(Hack_Status.Data_Refresh_Delay);
    }
}
void SendRefreshSignal(void){
    HWND hwnd = FindWindowW(L"SFHelperWindowClass", 
            APP_WSTR[AWSTR_WNDNAME][Hack_Status.App_Language]);
    while(Hack_Status.isRefresh_On){
        SendMessageW(hwnd, WM_REFRESH_DATA, 0, 0);
        Sleep(Hack_Status.Data_Refresh_Delay);
    }
}
void CloseAllExtraThread(void){
    extern pthread_t th_GlobalKeyboardHook;
    extern pthread_t th_CheckGameCloseOrLogout;
    extern pthread_t th_SendRefreshSignal;
    if(Hack_Status.isGlobal_Keyboard_Hooked){
        Hack_Status.isGlobal_Keyboard_Hooked = FALSE;
        SFHelperJoinThread(th_GlobalKeyboardHook, NULL);
    }
    if(Hack_Status.isChecking_Game){
        Hack_Status.isChecking_Game = FALSE;
        SFHelperJoinThread(th_CheckGameCloseOrLogout, NULL);
    }
    if(Hack_Status.isRefresh_On){
        Hack_Status.isRefresh_On = FALSE;
        SFHelperJoinThread(th_SendRefreshSignal, NULL);
    }
    if(Hack_Status.LastErrorCode != APP_NORMAL){
        ExceptionHandler();
    }
}
void SFHelperCreateThread(pthread_t *th, const pthread_attr_t *attr, 
        void *(* func)(void *), void *arg){
    if(pthread_create(th, attr, func, arg) != 0){
        Hack_Status.LastErrorCode = ERR_APP_CREATE_THREAD_FAIL;
    }
    MessageBeep(MB_ICONEXCLAMATION);
}
void SFHelperJoinThread(pthread_t t, void **res){
    if(pthread_join(t, res) != 0){
        Hack_Status.LastErrorCode = ERR_APP_JOIN_THREAD_FAIL;
    }
    MessageBeep(MB_OK); 
}
void HookLogger(HWND hwndEditLog){
    if(Hack_Status.LastErrorCode != APP_NORMAL){
        ExceptionHandler();
    } else{
        TimeLogger(hwndEditLog, TRUE);
        if(Hack_Status.isGlobal_Keyboard_Hooked){
            AppendText(hwndEditLog, 
                    APP_WSTR[AWSTR_APP_HOOK_ON][Hack_Status.App_Language], TRUE);
        } else{
            AppendText(hwndEditLog, 
                    APP_WSTR[AWSTR_APP_HOOK_OFF][Hack_Status.App_Language], TRUE);
        }
    }
}
void RefreshLogger(HWND hwndEditLog){
    if(Hack_Status.LastErrorCode != APP_NORMAL){
        ExceptionHandler();
    } else{
        TimeLogger(hwndEditLog, TRUE);
        if(Hack_Status.isRefresh_On){
            AppendText(hwndEditLog, 
                    APP_WSTR[AWSTR_APP_REFRESH_ON][Hack_Status.App_Language], TRUE);
        } else{
            AppendText(hwndEditLog, 
                    APP_WSTR[AWSTR_APP_REFRESH_OFF][Hack_Status.App_Language], TRUE);
        }
    }
}
BOOL DisplayHookStatus(HWND hwndParent){
    switch (Hack_Status.isGlobal_Keyboard_Hooked){
    case 0:
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_OFF][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_OFF][Hack_Status.App_Language]);
        break;
    case 1:
        SendMessageW(GetDlgItem(hwndParent, IDC_EDIT_HOOK_STATUS), WM_SETTEXT, 
                (WPARAM)wcslen(APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_ON][Hack_Status.App_Language]), 
                (LPARAM)APP_WSTR[AWSTR_CTL_E_HOOK_STATUS_ON][Hack_Status.App_Language]);
        break;
    default:
        break;
    }
    return TRUE;
}
BOOL GetAndDisplayMapID(HWND hwndParent){
    __int32 MapID = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_Map_ID[SF_Window.SF_Version]),
            (void*)&MapID, sizeof(__int32));
    WCHAR buffer[9] = {0};
    _itow_s(MapID, buffer, 9, 10);
    WCHAR buffer2[9] = {0};
    swprintf_s(buffer2, sizeof(buffer), L"%08s", buffer);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAP_ID), buffer2);
    return TRUE;
}
BOOL GetAndDisplayMapName(HWND hwndParent){
    char str[MAP_NAME_LEN] = {0};
    WCHAR wstr[MAP_NAME_LEN] = {0};
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_Map_Name[SF_Window.SF_Version]),
            (void*)str, sizeof(char) * MAP_NAME_LEN);
    str[strlen(str)-1] = '\0';
    GameStringToAPP(str, wstr, MAP_NAME_LEN);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAP_NAME), wstr);
    return TRUE;
}
BOOL GetAndDisplayMapGateID(HWND hwndParent){
    __int32 MapGateID = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_Map_Gate_ID[SF_Window.SF_Version]),
            (void*)&MapGateID, sizeof(__int32));
    WCHAR buffer[5] = {0};
    _itow_s(MapGateID, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAP_GATE_ID), buffer);
    return TRUE;
}
BOOL DisplayMoveDistance(HWND hwndParent){
    WCHAR buffer[5] = {0};
    _itow_s(Hook_Move.Move_Distance, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DISTANCE), buffer);
    return TRUE;
}
BOOL DisplayMoveDelay(HWND hwndParent){
    WCHAR buffer[5] = {0};
    _itow_s(Hook_Move.Move_Delay, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DELAY), buffer);
    return TRUE;
}
BOOL DisplayRefreshDelay(HWND hwndParent){
    WCHAR buffer[5] = {0};
    _itow_s(Hack_Status.Data_Refresh_Delay, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY), buffer);
    return TRUE;
}
BOOL GetTabs(void){
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_STATUS), 
            (void*)&SF_Tab, sizeof(__int32) * 14);
    return TRUE;
}
BOOL CloseAllTabs(void){
    SF_Tab_Info Close = {0};
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_STATUS), 
            (void*)&Close, sizeof(__int32) * 14);
    return TRUE;
}
BOOL PressCloseTabButton(void){
    __int32 Close = 3;
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_CLOSE_BUTTON_STATUS), 
            (void*)&Close, sizeof(__int32));
    return TRUE;
}
BOOL SetXYDefault(HWND hwndParent){
    WCHAR buffer[3] = L"0";
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_GATE_ID), buffer);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_X), NULL);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_Y), NULL);
    return TRUE;
}
BOOL SetGateIDDefault(HWND hwndParent){
    WCHAR buffer[3] = L"-1";
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_GATE_ID), buffer);
    return TRUE;
}
BOOL ApplyTeleportPreset(HWND hwndParent){
    HWND hwnd = FindWindowW(L"SFHelperWindowClass", 
            APP_WSTR[AWSTR_WNDNAME][Hack_Status.App_Language]);
    __int32 index = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), 
            CB_GETCURSEL, 0, 0); 
    index = index < 0? 0: index;
    WCHAR buffer[12] = {0};
    WCHAR buffer2[12] = {0};
    _itow_s(Teleport_Preset[index].Map_ID, buffer, 12, 10);
    swprintf_s(buffer2, sizeof(buffer), L"%08s", buffer);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_MAP_ID), buffer2);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), 
            CB_SETCURSEL, -1, 0);
    if(Teleport_Preset[index].Gate_ID >= 0){ // Gate ID Mode
        SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_GATE), 
                BM_SETCHECK, BST_CHECKED, 0); 
        SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_XY), 
                BM_SETCHECK, BST_UNCHECKED, 0); 
        SendMessageW(hwnd, WM_COMMAND, IDC_BUTTON_RADIO_GATE, 0);
        _itow_s(Teleport_Preset[index].Gate_ID, buffer, 12, 10);
        SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_GATE_ID), buffer);
    } else{ // XY Mode
        SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_GATE), 
                BM_SETCHECK, BST_UNCHECKED, 0); 
        SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_XY), 
                BM_SETCHECK, BST_CHECKED, 0); 
        SendMessageW(hwnd, WM_COMMAND, IDC_BUTTON_RADIO_XY, 0);
        _itow_s(Teleport_Preset[index].X, buffer, 12, 10);
        SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_X), buffer);
        _itow_s(Teleport_Preset[index].Y, buffer, 12, 10);
        SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_Y), buffer);
    }
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), 
            CB_SETCURSEL, index, 0);
    return TRUE;
}
BOOL PresetContentChange(HWND hwndParent){
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), 
            CB_SETCURSEL, -1, 0);
    return TRUE;
}
BOOL ApplyTeleportMapID(HWND hwndParent){
    HWND hwnd = FindWindowW(L"SFHelperWindowClass", 
            APP_WSTR[AWSTR_WNDNAME][Hack_Status.App_Language]);
    __int32 index = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), 
            CB_GETCURSEL, 0, 0); 
    index = index < 0? 0: index;
    WCHAR buffer[9] = {0};
    WCHAR buffer2[9] = {0};
    _itow_s(Scenario_Map_ID[index], buffer, 9, 10);
    swprintf_s(buffer2, sizeof(buffer), L"%08s", buffer);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_MAP_ID), buffer2);
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_GATE), 
            BM_SETCHECK, BST_CHECKED, 0); 
    SendMessageW(GetDlgItem(hwndParent, IDC_BUTTON_RADIO_XY), 
            BM_SETCHECK, BST_UNCHECKED, 0); 
    SendMessageW(hwnd, WM_COMMAND, IDC_BUTTON_RADIO_GATE, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_MAP_NAME), 
            CB_SETCURSEL, index, 0);
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_TELEPORT_PRESET), 
            CB_SETCURSEL, -1, 0);
    return TRUE;
}
BOOL ApplyTeleport(HWND hwndParent){
    WCHAR buffer[12] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_MAP_ID), buffer, 12);
    __int32 MapID = _wtoi(buffer);
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_GATE_ID), buffer, 12);
    __int32 GateID = _wtoi(buffer);
    if(GateID < 0){ // XY Mode
        GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_X), buffer, 12);
        __int32 X = _wtoi(buffer);
        GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_TELEPORT_Y), buffer, 12);
        __int32 Y = _wtoi(buffer);
        WriteVal((void*)(Hack_Status.Character_Attribute_P + 
                CA_TRANSPORT_POSITION_X), 
                (void*)&X, sizeof(__int32));
        WriteVal((void*)(Hack_Status.Character_Attribute_P + 
                CA_TRANSPORT_POSITION_Y), 
                (void*)&Y, sizeof(__int32));
    }
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAP_ID), 
            (void*)&MapID, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAP_GATE_ID), 
            (void*)&GateID, sizeof(__int32));
    __int32 trigger = 1;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LOADSCREEN_TRIGGER), 
            (void*)&trigger, sizeof(__int32));
    return TRUE;
}
BOOL OpenWarehouseTab(void){
    CloseAllTabs();
    __int32 Warehouse = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_WAREHOUSE), 
            (void*)&Warehouse, sizeof(__int32));
    Warehouse ^= 1;
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_WAREHOUSE), 
            (void*)&Warehouse, sizeof(__int32));
    return TRUE;
}
BOOL OpenGiantWarehouseTab(void){
    CloseAllTabs();
    __int32 GiantWarehouse = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_G_WAREHOUSE), 
            (void*)&GiantWarehouse, sizeof(__int32));
    GiantWarehouse ^= 1;
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_G_WAREHOUSE), 
            (void*)&GiantWarehouse, sizeof(__int32));
    return TRUE;
}
BOOL OpenCustomOutfitTab(void){
    CloseAllTabs();
    __int32 Custom = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_CUSTOMIZE_OUTFIT), 
            (void*)&Custom, sizeof(__int32));
    Custom ^= 1;
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_TAB_CUSTOMIZE_OUTFIT), 
            (void*)&Custom, sizeof(__int32));
    return TRUE;
}
BOOL PauseGame(void){
    __int32 Pause = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_PAUSE_GAME), 
            (void*)&Pause, sizeof(__int32));
    Pause ^= 1;
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_PAUSE_GAME), 
            (void*)&Pause, sizeof(__int32));
    return TRUE;
}
BOOL InfinitePower(void){
    __int32 Power = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_POWER_REMAINING_TIMER), 
            (void*)&Power, sizeof(__int32));
    Power = Power > 0? 0: 0x20000;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_POWER_REMAINING_TIMER), 
            (void*)&Power, sizeof(__int32));
    return TRUE;
}
BOOL CompanionRevive(void){
    __int32 Timer = 1;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_REVIVE_TIMER), 
            (void*)&Timer, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_REVIVE_TIMER_2), 
            (void*)&Timer, sizeof(__int32));
    return TRUE;
}
BOOL ExtraLandMine(void){
    __int32 LandMine = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LANDMINE_POSSESS_LIMIT), 
            (void*)&LandMine, sizeof(__int32));
    LandMine = LandMine > 100? 10: 0xFFFF;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LANDMINE_POSSESS_LIMIT), 
            (void*)&LandMine, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LANDMINE_POSSESS_LIMIT_2), 
            (void*)&LandMine, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LANDMINE_POSSESS), 
            (void*)&LandMine, sizeof(__int32));
    return TRUE;
}
BOOL ExtraLandMinePower(void){
    __int32 LandMinePower = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_EXTRA_LANDMINE_POWER), 
            (void*)&LandMinePower, sizeof(__int32));
    LandMinePower = LandMinePower > 100? 0: 0x20000;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_EXTRA_LANDMINE_POWER), 
            (void*)&LandMinePower, sizeof(__int32));
    return TRUE;
}
BOOL BeRich(void){
    ULONG_PTR Addr1 = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_POINTER_HOLDING_ITEM_P), 
            (void*)&Addr1, sizeof(__int32));
    if(Addr1 == 0){
        Hack_Status.LastErrorCode = ERR_SF_CURSOR_NULL;
        ExceptionHandler();
        return FALSE;
    }
    __int32 ItemIdentifier = 0;
    ReadVal(((void*)Addr1), 
            (void*)&ItemIdentifier, sizeof(__int32));
    __int32 GoldIdentifier = SF_Window.SF_Version == 2?
            4681312 + 0x10 :4681312;
    if(ItemIdentifier != GoldIdentifier){
        Hack_Status.LastErrorCode = ERR_SF_BE_RICH_NOT_MONEY;
        ExceptionHandler();
        return FALSE;
    }
    __int32 GoldNum = 0;
    ReadVal(((void*)Addr1 + 0x40), 
            (void*)&GoldNum, sizeof(__int32));
    GoldNum = GoldNum <= 10000?
            88888: GoldNum <= 100000?
            888888: GoldNum <= 1000000?
            8888888: 88888888;
    WriteVal(((void*)Addr1 + 0x40), 
            (void*)&GoldNum, sizeof(__int32));
    return TRUE;
}
BOOL NoMonsterDisplay(void){
    __int32 Display = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MONSTER_DISPLAY_AND_AI), 
            (void*)&Display, sizeof(__int32));
    Display ^= 1;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MONSTER_DISPLAY_AND_AI), 
            (void*)&Display, sizeof(__int32));
    return TRUE;
}
BOOL MagicLVto30(void){
    __int32 Extra = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_EXTRA_MAGIC_LV_2), 
            (void*)&Extra, sizeof(__int32));
    Extra = Extra == 50? 0: 50;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_EXTRA_MAGIC_LV_2), 
            (void*)&Extra, sizeof(__int32));
    return TRUE;
}
BOOL CrazySpeed(void){
    __int32 Walk = 0;
    __int32 Run = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_REAL_SPEED_RUN), 
            (void*)&Run, sizeof(__int32));
    Run = Run > 50? 50: 200;
    Walk = Walk > 25? 25: 100;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_REAL_SPEED_WALK), 
            (void*)&Walk, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_REAL_SPEED_RUN), 
            (void*)&Run, sizeof(__int32));
    return TRUE;
}
BOOL GodMode(void){
    static God_Mode G_Ori = {0};
    static God_Mode G_After = {
        255,    255,
        100000, 100000,
        100000, 100000, 
        10000, 
        500000, 500000,
        1000,   1000,
        500000, 500000,
        1000,   1000,
    };
    __int32 Flag_Strength_Ori_value = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_STRENGTH), 
            (void*)&Flag_Strength_Ori_value, sizeof(__int32));
    if(Flag_Strength_Ori_value != G_After.Strength){
        ReadVal((void*)(Hack_Status.Character_Attribute_P + 
             CA_ATK_SPD), 
             (void*)&G_Ori, sizeof(__int32) * 15);
        WriteVal((void*)(Hack_Status.Character_Attribute_P + 
             CA_ATK_SPD), 
             (void*)&G_After, sizeof(__int32) * 15);
    } else{
        WriteVal((void*)(Hack_Status.Character_Attribute_P + 
             CA_ATK_SPD), 
             (void*)&G_Ori, sizeof(__int32) * 15);
    }
    return TRUE;
}
BOOL ExtendAtkRange(void){
    __int32 Range = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PICKUP_AND_ATK_RANGE), 
            (void*)&Range, sizeof(__int32));
    Range = Range == 159? 0x20000: 159;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PICKUP_AND_ATK_RANGE), 
            (void*)&Range, sizeof(__int32));
    return TRUE;
}
BOOL ReviveEneny(void){
    __int32 Reload = 1;
    WriteVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] +
            STATS_RELOAD_SAVEFILE_TRIGGER), 
            (void*)&Reload, sizeof(__int32));
    return TRUE;
}
BOOL Suicide(void){
    __int32 HP = 0;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_HP), 
            (void*)&HP, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayMagicStatus(HWND hwndParent){
    __int32 Magic[SF_MAGIC_COUNT * 3] = {0};
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAGIC_TRANSPORT), 
            (void*)&Magic, sizeof(__int32) * SF_MAGIC_COUNT * 3);
    for(__int32 i = 0; i < SF_MAGIC_COUNT; i++){
        if(Magic[i] == 0x3){
            EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_LV_1 + i * 5), TRUE);
            EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MAGIC_LV_1 + i * 5), TRUE);
            EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_EXP_1 + i * 5), TRUE);
            EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MAGIC_EXP_1 + i * 5), TRUE);
        }
        EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_MAGIC_1 + i * 5), TRUE);
        WCHAR buffer[4] = {0};
        _itow_s(Magic[i + SF_MAGIC_COUNT], buffer, 4, 10);
        SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_LV_1 + i * 5), buffer);
        _itow_s(Magic[i + SF_MAGIC_COUNT * 2], buffer, 4, 10);
        SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_EXP_1 + i * 5), buffer);   
    }
    return TRUE;
}
BOOL UnlockMagic(HWND hwndParent, __int32 index){
    __int32 val = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAGIC_TRANSPORT +
            sizeof(__int32) * index), 
            (void*)&val, sizeof(__int32));
    val ^= 0x03;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAGIC_TRANSPORT +
            sizeof(__int32) * index), 
            (void*)&val, sizeof(__int32));
    switch(val){
        case 0x0:
            EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_LV_1 + index * 5), FALSE);
            EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MAGIC_LV_1 + index * 5), FALSE);
            EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_EXP_1 + index * 5), FALSE);
            EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MAGIC_EXP_1 + index * 5), FALSE);
            break;
        case 0x3:
            EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_LV_1 + index * 5), TRUE);
            EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MAGIC_LV_1 + index * 5), TRUE);
            EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_EXP_1 + index * 5), TRUE);
            EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_MAGIC_EXP_1 + index * 5), TRUE);
            break;
        default:
            break;
    }
    return TRUE;
}
BOOL ApplyMagicLV(HWND hwndParent, __int32 index){
    WCHAR buffer[3] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_LV_1 + index * 5), buffer, 3);
    __int32 LV = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAGIC_TRANSPORT_LV +
            sizeof(__int32) * index), 
            (void*)&LV, sizeof(__int32));
    return TRUE;
}
BOOL ApplyMagicEXP(HWND hwndParent, __int32 index){
    WCHAR buffer[4] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MAGIC_EXP_1 + index * 5), buffer, 4);
    __int32 EXP = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAGIC_TRANSPORT_EXP +
            sizeof(__int32) * index), 
            (void*)&EXP, sizeof(__int32));
    return TRUE;
}
BOOL UnlockQuest(__int32 index){
    ULONG_PTR QuestAddr = 0;
    ReadVal(((void*)SF_Window.Base_hModule + 
            Addr_STATS_Base[SF_Window.SF_Version] + 
            STATS_QUEST_IS_UNLOCKED_P),
            (void*)&QuestAddr, sizeof(DWORD));
    __int32 Quest = 0;
    ReadVal((void*)(QuestAddr + sizeof(__int32) * index), 
            (void*)&Quest, sizeof(__int32));
    Quest = (Quest + 1) % 3;
    WriteVal((void*)(QuestAddr + sizeof(__int32) * index), 
            (void*)&Quest, sizeof(__int32));
    return TRUE;
}
BOOL UnlockGiantWarehouse(__int32 index){
    __int32 GW = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_G_WAREHOUSE_1_UNLOCK +
            sizeof(__int32) * index), 
            (void*)&GW, sizeof(__int32));
    GW ^= 1;
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_G_WAREHOUSE_1_UNLOCK +
            sizeof(__int32) * index), 
            (void*)&GW, sizeof(__int32));
    return TRUE;
}
BOOL GetAndDisplayGiantWarehouseIndex(HWND hwndParent){
    __int32 Index = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_G_WAREHOUSE_CURRENT_PAGE), 
            (void*)&Index, sizeof(__int32));
    WCHAR buffer[4] = {0};
    _itow_s(Index, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_G_WAREHOUSE_INDEX), buffer);
    return 0;
}
BOOL ApplyGiantWarehouseIndex(HWND hwndParent){
    WCHAR buffer[4] = {0};
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_G_WAREHOUSE_INDEX), buffer, 4);
    __int32 Index = _wtoi(buffer);
    if( (0 <= Index && Index <= 13) || (25 <= Index && Index <= 479)){
        // 0-13; 25-479
        WriteVal((void*)(Hack_Status.Character_Attribute_P + 
                CA_G_WAREHOUSE_CURRENT_PAGE), 
                (void*)&Index, sizeof(__int32));
    }
    return TRUE;
}


    // WCHAR buffer[3] = {0};
    // _itow(x, buffer, 10);
    // MessageBoxW(NULL, buffer, L"", 0);