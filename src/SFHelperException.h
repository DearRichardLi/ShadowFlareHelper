#ifndef _SF_HELPER_EXCEPTION
#define _SF_HELPER_EXCEPTION

#define SF_NORMAL 0x0
#define SF_WARN   0x1
#define SF_ERROR  0x2

/* 16 lower bits for errcode
 * 8 bits for the APP_Str array index, corresponding in SFHelperLanguage.h
 * 4 bits for: Severity level (msgType: NORMAL 0/WARN 1/ERROR 2)
 * highest 4 bits: set to b0001
 */
#define APP_NORMAL                          0x00000000
#define ERR_APP_LOG_TO_FILE_FAILED          0x11210000
#define ERR_SF_SFEXE_ALREADY_RUNNING        0x11220001
#define ERR_SF_SFEXE_NOT_FOUND              0x11230002
#define ERR_SF_GET_WINDOW_FAILED 			0x11250003
#define ERR_SF_GET_TID_FAILED				0x11260004
#define ERR_SF_GET_PID_FAILED				0x11270005
#define ERR_SF_GET_HANDLE_FAILED 			0x11280006
#define ERR_SF_GET_PROCESS_MODULES_FAILED 	0x11290007
#define ERR_APP_READ_MEMORY_FAILED          0x12310008
#define ERR_APP_WRITE_MEMORY_FAILED         0x12320009
#define ERR_APP_PERMISSION_DENIED           0x1234000A


#define ERR_SF_READ_MEMORY_FAILED 			0x10010010
#define ERR_SF_KEYBOARD_HOOK_FAILED 		0x10010020
#define ERR_SF_CLOSED						0x10010030

void ExceptionLog();
void ExceptionHandler();
void Debug_Printer(void);


#endif /* SFHelperException.h */