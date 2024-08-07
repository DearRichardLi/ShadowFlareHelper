#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "SFHelperStd.h"
#include "SFHelperWindows.h"
#include "SFHelperResource.h"
#include "SFHelperException.h"
#include "SFHelperLanguage.h"

extern Hack_Statu_Info Hack_Status;
extern SF_Window_Info SF_Window;
extern LPCWSTR APP_WSTR[APP_WSTR_STRINGS_COUNT][AVAILABLE_LANGUAGE_COUNT];

extern HWND hwnd;


void ExceptionLog(){
    DWORD APP_WSTR_index = (Hack_Status.LastErrorCode >> 16) & 0xFF;

    SYSTEMTIME st;
    GetLocalTime(&st);
  
    FILE *file = fopen("__SFHelperError.log", "a"); 
    if (file == NULL) {
        MessageBoxW(NULL, 
                APP_WSTR[AWSTR_APP_LOG_TO_FILE_FAIL][Hack_Status.App_Language], 
                L"ERROR", MB_ICONERROR);
        return;
    } else{
        fwprintf_s(file, L"%04d-%02d-%02d %02d:%02d:%02d.%03d \t", 
                st.wYear, st.wMonth, st.wDay, 
                st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        fwprintf_s(file, L"0x%X\t\t%s\r\n", Hack_Status.LastErrorCode, 
                APP_WSTR[APP_WSTR_index][Hack_Status.App_Language]);
        fclose(file);
    }
}

void ExceptionHandler(){
    DWORD APP_WSTR_index = (Hack_Status.LastErrorCode >> 16) & 0xFF;
    DWORD msgType        = (Hack_Status.LastErrorCode >> 24) & 0x0F;
    // DWORD APP_WSTR_index = (Hack_Status.LastErrorCode & 0x00110000) >> 4;
    // DWORD msgType        = (Hack_Status.LastErrorCode & 0x01000000) >> 6;
    WCHAR logBuffer[128] = {0};
    swprintf_s(logBuffer, sizeof(logBuffer), L"%d %d", APP_WSTR_index, msgType);
    // MessageBoxW(hwnd, logBuffer, L"except wstr index", 0);

    switch((int)msgType){
    case SF_NORMAL: break;
    case SF_WARN  : // break;
    case SF_ERROR :
        ExceptionLog(Hack_Status.LastErrorCode, APP_WSTR_index);
    }
    MessageBoxW(hwnd, 
            APP_WSTR[APP_WSTR_index][Hack_Status.App_Language], 
            L"Exception", msgType==SF_NORMAL? MB_OK: 
            msgType==SF_WARN? MB_ICONINFORMATION : MB_ICONERROR);
    // "MB_OK" is a default uType.
    Hack_Status.LastErrorCode = APP_NORMAL; // del last error
}

void Debug_Printer(void){
    FILE *file = fopen("__SFHelperDebug.log", "a");
    WCHAR buffer[256] = {0};
    swprintf_s(buffer, sizeof(buffer),
L"Hack_Status\r\nApp_Lang:\t%u\r\nisBind_Game:\t%d\r\n\
Game_Mode:\t%u\r\nClient_Index:\t%u\r\nAttribute_P:\t0x%x\r\n\
isHooked:\t%d\r\nerrcode:\t0x%x\r\n\r\n",
    Hack_Status.App_Language,
    Hack_Status.isBind_Game,
    Hack_Status.Game_Mode,
    Hack_Status.Client_Index,
    Hack_Status.Character_Attribute_P,
    Hack_Status.isGlobal_Keyboard_Hooked,
    Hack_Status.LastErrorCode);
    fwprintf_s(file, buffer);
    MessageBoxW(NULL, buffer, L"Hack_Status", 0);

    swprintf_s(buffer, sizeof(buffer),
L"Window_Info\r\nSF_Ver:\t\t%u\r\nhWnd:\t\t0x%x\r\n\
PID:\t\t%u\r\nTID:\t\t%u\r\nSF_Handle:\t0x%x\r\n\
Module_Count:\t%u\r\nBase_hModule:\t0x%x\r\n\r\n",
    SF_Window.SF_Version,
    SF_Window.hWnd,
    SF_Window.PID,
    SF_Window.TID,
    SF_Window.SF_Handle,
    SF_Window.Module_Count,
    SF_Window.Base_hModule);
    fwprintf_s(file, buffer);
    MessageBoxW(NULL, buffer, L"SF_Window", 0);
    
    fclose(file);
}

