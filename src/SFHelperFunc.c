#include <Windows.h>
#include <psapi.h> 
#include <pthread.h>

#include "SFHelperAddr.h"
#include "SFHelperStd.h"
#include "SFHelperException.h"
#include "SFHelperWindows.h"
#include "SFHelperLanguage.h"
#include "SFHelperFunc.h"

extern LPCWSTR SF_EXE_Filename;
extern const Version GameVersions[SF_VERSION_COUNT];
extern Hack_Statu_Info Hack_Status;
extern SF_Window_Info SF_Window;
extern Hook_Move_Info Hook_Move;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];

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
BOOL BindSF(void){
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
    if(    GetGameModeAndOnlineRole()
        && DisplayGameModeAndOnlineRole(hwndParent)
        && GetAndDisplayPlayerName(hwndParent)
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
            WCHAR buffer[2] = {L'\0'};
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
    char str[PLAYER_NAME_LEN];
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
LONG64 KeepNumWStrInRange(WCHAR* buf, size_t nSize, 
        LONG64 lBound, LONG64 hBound, BOOL _Modify, __int32 _Radix){
    LONG64 num = _wtoi64(buf);
    num = num<lBound? lBound: num>hBound? hBound: num;
    if(_Modify) 
        _i64tow_s(num, buf, nSize, _Radix);
    return num;
}
BOOL GetAndDisplayPlayerLV(HWND hwndParent){
    __int32 LV = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV), 
            (void*)&LV, sizeof(__int32));
    WCHAR buffer[4];
    _itow_s(LV, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_LV), buffer);
    return TRUE;
}
BOOL ApplyPlayerLV(HWND hwndParent){
    WCHAR buffer[4];
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
    WCHAR buffer[10];
    _itow_s(EXP, buffer, 10, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_EXP), buffer);
    return TRUE;
}
BOOL ApplyPlayerEXP(HWND hwndParent){
    WCHAR buffer[10];
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
    case 5:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 0, 0);
        break;
    case 6:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 1, 0);
        break;
    case 9:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 2, 0);
        break;
    case 16:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
                CB_SETCURSEL, 3, 0);
        break;
    }
    return TRUE;
}
BOOL ApplyPlayerProf(HWND hwndParent){
    __int32 Prof = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), 
            CB_GETCURSEL, 0, 0); 
        Prof = Prof == 0? 5:
                Prof == 1? 6:
                Prof == 2? 9:
                Prof == 3? 16: 16;
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
    case 5:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
                CB_SETCURSEL, 0, 0);
        break;
    case 6:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
                CB_SETCURSEL, 1, 0);
        break;
    case 9:
        SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
                CB_SETCURSEL, 2, 0);
        break;
    }
    return TRUE;
}
BOOL ApplyPlayerProfToBe(HWND hwndParent){
        __int32 ProfToBe = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), 
            CB_GETCURSEL, 0, 0); 
        ProfToBe = ProfToBe == 0? 5:
                ProfToBe == 1? 6:
                ProfToBe == 2? 9: 9;
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
    WCHAR buffer[3];
    _itow_s(CompanionLV, buffer, 3, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV), buffer);
    return TRUE;
}
BOOL ApplyCompanionLV(HWND hwndParent){
    WCHAR buffer[3];
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
    WCHAR buffer[4];
    _itow_s(CompanionEXP, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP), buffer);
    return TRUE;
}
BOOL ApplyCompanionEXP(HWND hwndParent){
    WCHAR buffer[4];
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
    WCHAR buffer[10];
    _itow_s(Hook_Move.X, buffer, 10, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_X), buffer);
    _itow_s(Hook_Move.Y, buffer, 10, 10);
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
    if(GetForegroundWindow() == SF_Window.hWnd && 
            (ks->flags == 0 || ks->flags == 1)){
        GetPlayerPositionX();
        GetPlayerPositionY();
        // MessageBoxW(NULL, L"pressdown", L"press", 0);
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
            if(Hook_Move.isMiniMapOpen)
                break;
        case VK_NUMPAD2: case VK_NUMPAD5:     // numpad 2 & 5 
            PlayerMoveAxisX(TRUE); 
            PlayerMoveAxisY(TRUE); 
            break;
        case VK_LEFT:                         // Left arrow
            if(Hook_Move.isMiniMapOpen)
                break;
        case VK_NUMPAD4:                      // numpad 4
            PlayerMoveAxisX(FALSE); 
            PlayerMoveAxisY(TRUE); 
            break;
        case VK_RIGHT:                        // Right arrow
            if(Hook_Move.isMiniMapOpen)
                break;
        case VK_NUMPAD6:                      // numpad 6
            PlayerMoveAxisX(TRUE); 
            PlayerMoveAxisY(FALSE); 
            break;
        case VK_UP:                           // UP arrow
            if(Hook_Move.isMiniMapOpen)
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
    while(Hack_Status.isBind_Game){
        DWORD flag = WaitForSingleObject(SF_Window.SF_Handle, 
                DEFAULT_CHECK_GAME_CLOSED_WAIT_MILLISECONDS);
        if(flag == 0){
            Hack_Status.isBind_Game = FALSE;
            Hack_Status.LastErrorCode = ERR_SF_CLOSED;
        } else{
            DWORD GameLogin = 0;
            ReadVal((void*)(Hack_Status.Character_Attribute_P), 
                    (void*)&GameLogin, sizeof(DWORD));
            if(GameLogin > 1){
                Hack_Status.isBind_Game = FALSE;
                Hack_Status.LastErrorCode = ERR_SF_LOGOUT;
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
}
void SFHelperJoinThread(pthread_t t, void **res){
    if(pthread_join(t, res) != 0){
        Hack_Status.LastErrorCode = ERR_APP_JOIN_THREAD_FAIL;
    }
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
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_MAP_ID), 
            (void*)&MapID, sizeof(__int32));
    WCHAR buffer[9];
    _itow_s(MapID, buffer, 9, 10);
    WCHAR buffer2[9];
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
BOOL DisplayMoveDistance(HWND hwndParent){
    WCHAR buffer[5];
    _itow_s(Hook_Move.Move_Distance, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DISTANCE), buffer);
    return TRUE;
}
BOOL DisplayMoveDelay(HWND hwndParent){
    WCHAR buffer[5];
    _itow_s(Hook_Move.Move_Delay, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_MOVE_DELAY), buffer);
    return TRUE;
}
BOOL DisplayRefreshDelay(HWND hwndParent){
    WCHAR buffer[5];
    _itow_s(Hack_Status.Data_Refresh_Delay, buffer, 5, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_REFRESH_DELAY), buffer);
    return TRUE;
}

