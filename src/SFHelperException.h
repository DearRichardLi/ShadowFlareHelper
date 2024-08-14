#ifndef _SF_HELPER_EXCEPTION
#define _SF_HELPER_EXCEPTION

#define SF_NORMAL 0x0
#define SF_WARN   0x1
#define SF_ERROR  0x2

/* 16 lower bits for errcode
 * 8 bits for the APP_Str array index, corresponding in SFHelperLanguage.h
 * 4 bits for: Severity level (msgType: NORMAL 0/WARN 1/ERROR 2)
 * highest 4 bits: unused, set to b0001
 */
#define APP_NORMAL                          0x00000000
#define ERR_APP_LOG_TO_FILE_FAILED          0x11210001
#define ERR_SF_SFEXE_ALREADY_RUNNING        0x11220002
#define ERR_SF_SFEXE_NOT_FOUND              0x11230003
#define ERR_SF_GET_WINDOW_FAILED            0x11250004
#define ERR_SF_GET_TID_FAILED               0x11260005
#define ERR_SF_GET_PID_FAILED               0x11270006
#define ERR_SF_GET_HANDLE_FAILED            0x11280007
#define ERR_SF_GET_PROCESS_MODULES_FAILED   0x11290008
#define ERR_APP_READ_MEMORY_FAILED          0x12310009
#define ERR_APP_WRITE_MEMORY_FAILED         0x1232000A
#define ERR_APP_PERMISSION_DENIED           0x1234000B
#define ERR_APP_KEYBOARD_HOOK_FAIL          0x1237000C
#define ERR_APP_CREATE_THREAD_FAIL          0x1238000D
#define ERR_APP_JOIN_THREAD_FAIL            0x1239000E
#define ERR_SF_CLOSED                       0x113C000F
#define ERR_SF_LOGOUT                       0x113D0010
#define ERR_SF_NOT_LOGIN                    0x113E0011
#define ERR_SF_CURSOR_NULL                  0x11420012
#define ERR_SF_BE_RICH_NOT_MONEY            0x11430013

void ExceptionLog();
void ExceptionHandler();
void Debug_Printer(void);


#endif /* SFHelperException.h */