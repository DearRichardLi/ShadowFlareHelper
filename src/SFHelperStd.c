#include "SFHelperStd.h"


LPCWSTR APP_VERSION = L"0.4.0";
extern LPCWSTR APP_VERSION;
LPCWSTR GitHub_Address = L"https://github.com/DearRichardLi/ShadowFlareHelper";
extern LPCWSTR GitHub_Address;
LPCWSTR SF_EXE_Filename = L"ShadowFlare.exe";
extern LPCWSTR SF_EXE_Filename;

const Version GameVersions[SF_VERSION_COUNT] = {
      //{L"Lan", L"Version",   L"Info",                   L"Window Title"}, /* This line is to align the array index 0 */
      {L"CHT", L"2.004.000", L"繁體中文 CHT 2.004.000", L"ShadowFlare for Window98/Me/2000/XP"},
      {L"CHS", L"2.004.000", L"简体中文 CHN 2.004.000", L"ShadowFlare for Window98/Me/2000/XP"},
      {L"ENG", L"2.004.000", L"ENGLISH  ENG 2.004.000", L"ShadowFlare for Window98/Me/2000"},
      {L"JPN", L"1.004.003", L"日本語   JPN 1.004.003", L"SHADOW FLARE for Window98/Me/2000"},
      {L"KOR", L"2.004.001", L"Korean   KOR 2.004.001", L"ShadowFlare for Windows98/Me/2000/XP"}
        /*
         * NOTICE: I don't have the ORIGINAL KOR ShadowFlare.exe
         * I only got a copy from the Chinese Community
         * Which the exe is packed (shelled?) by a member
         * I'm not sure whether this packed Korean version addresses are 
         * same as the original KOR copy.
         */
};
extern const Version GameVersions[SF_VERSION_COUNT];








