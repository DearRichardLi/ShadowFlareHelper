#include <Windows.h>
#include <psapi.h> 

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
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];

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
void OpenSFLogger(HWND hwndEditInitLog){
    if(Hack_Status.LastErrorCode == ERR_SF_SFEXE_ALREADY_RUNNING){
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_SF_RUNNING][Hack_Status.App_Language], TRUE);
        return;
    } else if(Hack_Status.LastErrorCode == ERR_SF_SFEXE_NOT_FOUND){
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_SFEXE_NOT_FOUND][Hack_Status.App_Language], TRUE);
        return;
    } else{
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_SFEXE_FOUND][Hack_Status.App_Language], TRUE);
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
    int bRet = EnumProcessModulesEx(SF_Window.SF_Handle, (HMODULE*)hModule, sizeof(hModule), &dwRet, 0x03);
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
    for(int i = 0; i < Module_Num; i++){
        GetModuleBaseNameW(SF_Window.SF_Handle, hModule[i], lpBaseName, sizeof(lpBaseName));
        fwprintf_s(file, L"%-3d %-50s: %#x\n", i, lpBaseName, hModule[i]);
    }
    fclose(file);
    */
    return TRUE;
}

void BindSFLogger(HWND hwndEditInitLog){
    ClearText(hwndEditInitLog);
    WCHAR logBuffer[128] = {0};
    SYSTEMTIME st;
    GetLocalTime(&st);
    swprintf_s(logBuffer, sizeof(logBuffer), 
            L"%02d:%02d:%02d.%03d", 
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    AppendText(hwndEditInitLog, logBuffer, TRUE);
    if(SF_Window.hWnd == NULL){ // ----Failed to find ShadowFlare.exe Window---- //
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_SFWND_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Found ShadowFlare.exe Window---- //
    swprintf_s(logBuffer, sizeof(logBuffer), L"0x%x", (void*)SF_Window.hWnd); //%p to print full LONG_PTR
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_SFWND_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditInitLog, logBuffer, TRUE);
    if(SF_Window.TID == 0){ // ----Failed to get TID---- //
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_TID_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Got TID---- //
    swprintf_s(logBuffer, sizeof(logBuffer), L"%d", (int)SF_Window.TID);
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_TID_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditInitLog, logBuffer, TRUE);
    if(SF_Window.PID == 0){ // ----Failed to get PID---- //
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_PID_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Got PID---- //
    swprintf_s(logBuffer, sizeof(logBuffer), L"%d", (int)SF_Window.PID);
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_PID_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditInitLog, logBuffer, TRUE);
    if(SF_Window.SF_Handle == (HANDLE)0){ // ----Failed to get HANDLE---- // 
        if(GetLastError() == 5){ // ----Permission Denied---- // 
            AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_PERMISSION_DENIED][Hack_Status.App_Language], TRUE);
        } else{
            AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_HANDLE_FAIL][Hack_Status.App_Language], TRUE);
        }
        return;
    } 
        // ----Got HANDLE---- // 
    swprintf_s(logBuffer, sizeof(logBuffer), L"%u", SF_Window.SF_Handle);
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_HANDLE_SUC][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditInitLog, logBuffer, TRUE);
    if(SF_Window.Module_Count == 0){ // ----Failed to get Process Modules---- //
        AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_MODULE_FAIL][Hack_Status.App_Language], TRUE);
        return;
    }
        // ----Got the entry of Shadowflare.exe---- //
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_GET_MODULE_SUC][Hack_Status.App_Language], TRUE);
        // ----Base Addr is the Addr of 1st Module---- //
    swprintf_s(logBuffer, sizeof(logBuffer), L"0x%x", (void *)SF_Window.Base_hModule);
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_SF_BASE_ADDR][Hack_Status.App_Language], FALSE);
    AppendText(hwndEditInitLog, logBuffer, TRUE);
        // Bind Success
    AppendText(hwndEditInitLog, APP_WSTR[AWSTR_APP_SF_BIND_SUC][Hack_Status.App_Language], 1);
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
void ReadAndSetValues(HWND hwndTab){
    GetGameModeAndOnlineRole();
    DisplayGameModeAndOnlineRole(hwndTab);
    BYTE Player_Name[PLAYER_NAME_LEN] = {0}; //Player name max_len is 20 bytes in SF
    GetPlayerName(Player_Name);
    DisplayPlayerName(hwndTab, Player_Name);
    GetAndDisplayPlayerLV(hwndTab);
    GetAndDisplayPlayerSex(hwndTab);
    GetAndDisplayPlayerEXP(hwndTab);
    GetAndDisplayPlayerProf(hwndTab);
    GetAndDisplayPlayerProfToBe(hwndTab);
    GetAndDisplayCompanionLV(hwndTab);
    GetAndDisplayCompanionID(hwndTab);
    GetAndDisplayCompanionEXP(hwndTab);

}
void GetGameModeAndOnlineRole(void){
    ULONG_PTR Addr1 = 0;
    ReadVal( ((void*)SF_Window.Base_hModule + 
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

    if(Hack_Status.LastErrorCode != 0){
        ExceptionHandler();
    }
}
void DisplayGameModeAndOnlineRole(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_GAMEMODE), TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_GAMEMODE),   TRUE);
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
        EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_ONLINEROLE), TRUE);
        EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_ONLINEROLE),   TRUE);
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
    }
}
void GetPlayerName(BYTE *str){
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_NAME), 
            (void*)str, sizeof(char) * PLAYER_NAME_LEN);
}
void DisplayPlayerName(HWND hwndTab, BYTE *str){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PLAYER_NAME),       TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME),         TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_PLAYER_NAME), TRUE);
    WCHAR wstr[PLAYER_NAME_LEN] = {0};
    switch(SF_Window.SF_Version){
    case 0: // CHT encoding: Big 5
        MultiByteToWideChar(950, 0, str, -1, wstr, PLAYER_NAME_LEN);
        break;
    case 1: // CHN encoding: GBK
        MultiByteToWideChar(936, 0, str, -1, wstr, PLAYER_NAME_LEN);
        break;
    case 2: // ENG encoding: ANSI
        MultiByteToWideChar(437, 0, str, -1, wstr, PLAYER_NAME_LEN);
        break;
    case 3: // JPN encoding: Shift-JIS
        MultiByteToWideChar(932, 0, str, -1, wstr, PLAYER_NAME_LEN);
        break;
    case 4: // KOR endocing: Euc-kr?? 51949(euc) or 949?
        // MultiByteToWideChar(949, 0, str, -1, wstr, PLAYER_NAME_LEN);
        MultiByteToWideChar(51949, 0, str, -1, wstr, PLAYER_NAME_LEN);
    }
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME), wstr);
}
void ApplyPlayerName(HWND hwndTab){
    /*
     * funny here. IDN weather it is because my PC is CN locale.
     * No need to Get window text with WCHAR and transform to multybyte.
     * just need to Get with ANSI version. seems there is a auto transform
     */
    HWND hwndParent = GetParent(hwndTab);
    // WCHAR wstr[PLAYER_NAME_LEN];
    BYTE str[PLAYER_NAME_LEN];
    GetWindowTextA(GetDlgItem(hwndParent, IDC_EDIT_PLAYER_NAME), str, PLAYER_NAME_LEN);
    // switch(SF_Window.SF_Version){
    // case 0: // CHT encoding: Big 5
    //     WideCharToMultiByte(950, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
    //     break;
    // case 1: // CHN encoding: GBK
    //     WideCharToMultiByte(936, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
    //     break;
    // case 2: // ENG encoding: ANSI
    //     WideCharToMultiByte(437, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
    //     break;
    // case 3: // JPN encoding: Shift-JIS
    //     WideCharToMultiByte(932, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
    //     break;
    // case 4: // KOR endocing: Euc-kr?? 51949(euc) or 949?
    //     // WideCharToMultiByte(949, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
    //     WideCharToMultiByte(51949, 0, wstr, PLAYER_NAME_LEN, str, -1, NULL, NULL);
    // }
    // MessageBoxW(NULL, wstr, L"wstr", 0);
    // MessageBoxA(NULL, str, "str", 0);
    if(str[PLAYER_NAME_LEN-1] != 0){
        str[PLAYER_NAME_LEN-1] = 0;
        AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
                APP_WSTR[AWSTR_APP_STRING_OVERFLOW][Hack_Status.App_Language], TRUE);
    }
    WriteVal((void*)(Hack_Status.Character_Attribute_P + CA_PLAYER_NAME), 
            (void*)str, sizeof(char) * PLAYER_NAME_LEN);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + CA_PLAYER_NAME_2), 
            (void*)str, sizeof(char) * PLAYER_NAME_LEN);
}

LONG64 KeepNumWStrInRange(WCHAR* buf, size_t nSize, 
        LONG64 lBound, LONG64 hBound, BOOL _Modify, int _Radix){
    LONG64 num = _wtoi64(buf);
    num = num<lBound? lBound: num>hBound? hBound: num;
    if(_Modify) 
        _i64tow_s(num, buf, nSize, _Radix);
    return num;
}
void GetAndDisplayPlayerLV(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_LV), TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_LV),   TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_LV), TRUE);
    __int32 LV = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV), 
            (void*)&LV, sizeof(__int32));
    WCHAR buffer[4];
    _itow_s(LV, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_LV), buffer);
}
void ApplyPlayerLV(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    WCHAR buffer[4];
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_LV), buffer, 4);
    __int32 LV = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV), 
            (void*)&LV, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_LV_2), 
            (void*)&LV, sizeof(__int32));
}
void GetAndDisplayPlayerSex(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_SEX),   TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), TRUE);
    __int32 Sex = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_SEX), 
            (void*)&Sex, sizeof(__int32));
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), 
            CB_SETCURSEL, Sex, 0);
}
void ApplyPlayerSex(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    __int32 Sex = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_SEX), 
            CB_GETCURSEL, 0, 0); 
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_SEX), 
            (void*)&Sex, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_SEX_2), 
            (void*)&Sex, sizeof(__int32));
    AppendText(GetDlgItem(hwndParent, IDC_EDIT_INIT_LOG), 
            APP_WSTR[AWSTR_APP_HINT_RELOAD_SAVEFILE][Hack_Status.App_Language], 
            TRUE);
}
void GetAndDisplayPlayerEXP(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_EXP),       TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_EXP),         TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_EXP), TRUE);
    __int32 EXP = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_EXP), 
            (void*)&EXP, sizeof(__int32));
    WCHAR buffer[10];
    _itow_s(EXP, buffer, 10, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_EXP), buffer);
}
void ApplyPlayerEXP(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    WCHAR buffer[10];
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_EXP), buffer, 10);
    __int32 EXP = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_PLAYER_EXP), 
            (void*)&EXP, sizeof(__int32));
}
void GetAndDisplayPlayerProf(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF),   TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF), TRUE);
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
}
void ApplyPlayerProf(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
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
}
void GetAndDisplayPlayerProfToBe(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_PROF_TO_BE),   TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_PROF_TO_BE), TRUE);
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

}
void ApplyPlayerProfToBe(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
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
}
void GetAndDisplayCompanionLV(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_LV), TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV),   TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_UPDOWN_COMPANION_LV), TRUE);
    __int32 CompanionLV = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_LV), 
            (void*)&CompanionLV, sizeof(__int32));
    WCHAR buffer[3];
    _itow_s(CompanionLV, buffer, 3, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV), buffer);
}
void ApplyCompanionLV(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    WCHAR buffer[3];
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_LV), buffer, 3);
    __int32 CompanionLV = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_LV), 
            (void*)&CompanionLV, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_LV_2), 
            (void*)&CompanionLV, sizeof(__int32));
}
void GetAndDisplayCompanionID(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_ID),   TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), TRUE);
    __int32 CompanionID = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_ID), 
            (void*)&CompanionID, sizeof(__int32));
    SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), 
            CB_SETCURSEL, CompanionID, 0);

}
void ApplyCompanionID(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    __int32 CompanionID = SendMessageW(GetDlgItem(hwndParent, IDC_COMBOBOX_COMPANION_ID), 
            CB_GETCURSEL, 0, 0); 
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_ID), 
            (void*)&CompanionID, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_ID_2), 
            (void*)&CompanionID, sizeof(__int32));
    
}
void GetAndDisplayCompanionEXP(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    EnableWindow(GetDlgItem(hwndParent, IDC_STATIC_COMPANION_EXP),       TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP),         TRUE);
    EnableWindow(GetDlgItem(hwndParent, IDC_BUTTON_APPLY_COMPANION_EXP), TRUE);
    __int32 CompanionEXP = 0;
    ReadVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_EXP), 
            (void*)&CompanionEXP, sizeof(__int32));
    WCHAR buffer[4];
    _itow_s(CompanionEXP, buffer, 4, 10);
    SetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP), buffer);
}
void ApplyCompanionEXP(HWND hwndTab){
    HWND hwndParent = GetParent(hwndTab);
    WCHAR buffer[4];
    GetWindowTextW(GetDlgItem(hwndParent, IDC_EDIT_COMPANION_EXP), buffer, 4);
    __int32 CompanionEXP = _wtoi(buffer);
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_EXP), 
            (void*)&CompanionEXP, sizeof(__int32));
    WriteVal((void*)(Hack_Status.Character_Attribute_P + 
            CA_COMPANION_EXP_2), 
            (void*)&CompanionEXP, sizeof(__int32));
}



