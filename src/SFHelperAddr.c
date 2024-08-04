#include <windows.h>

#include "SFHelperAddr.h"
#include "SFHelperStd.h"

const ULONG_PTR Addr_STATS_Base[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8CDF4)  // CHT 0x8C844
    , ADDRENGCHN(0x8CDF4)  // CHS 0x8C8DC
    ,            0x8CDF4   // ENG 0x8CDF4
    , ADDRENGJPN(0x8CDF4)  // JPN 0x8C9F4
    , ADDRENGKOR(0x8CDF4)  // KOR 0x8C844
};
const ULONG_PTR Addr_ESC_Menu_Statu[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8D548)  // CHT 
    , ADDRENGCHN(0x8D548)  // CHS 
    ,            0x8D548   // ENG 
    , ADDRENGJPN(0x8D548)  // JPN 
    , ADDRENGKOR(0x8D548)  // KOR 
};
const ULONG_PTR Addr_Map_Name[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8D5F8)  // CHT 
    , ADDRENGCHN(0x8D5F8)  // CHS 
    ,            0x8D5F8   // ENG 
    , ADDRENGJPN(0x8D5F8)  // JPN 
    , ADDRENGKOR(0x8D5F8)  // KOR 
}; // map name len = 256
const ULONG_PTR Addr_Map_Gate_ID[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8D6F8)  // CHT 
    , ADDRENGCHN(0x8D6F8)  // CHS 
    ,            0x8D6F8   // ENG 
    , ADDRENGJPN(0x8D6F8)  // JPN 
    , ADDRENGKOR(0x8D6F8)  // KOR 
};
const ULONG_PTR Addr_Timer[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8DA70)  // CHT 
    , ADDRENGCHN(0x8DA70)  // CHS 
    ,            0x8DA70   // ENG 
    , ADDRENGJPN(0x8DA70)  // JPN 
    , ADDRENGKOR(0x8DA70)  // KOR 
};
const ULONG_PTR Addr_Map_ID[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8D7B4)  // CHT 
    , ADDRENGCHN(0x8D7B4)  // CHS 
    ,            0x8D7B4   // ENG 
    , ADDRENGJPN(0x8D7B4)  // JPN 
    , ADDRENGKOR(0x8D7B4)  // KOR 
};
const ULONG_PTR Addr_Change_Equipment[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8D7BC)  // CHT 
    , ADDRENGCHN(0x8D7BC)  // CHS 
    ,            0x8D7BC   // ENG 
    , ADDRENGJPN(0x8D7BC)  // JPN 
    , ADDRENGKOR(0x8D7BC)  // KOR 
};
const ULONG_PTR Addr_Freeze_Game[SF_VERSION_COUNT] ={
      ADDRENGCHT(0x8D8D4)  // CHT 
    , ADDRENGCHN(0x8D8D4)  // CHS 
    ,            0x8D8D4   // ENG 
    , ADDRENGJPN(0x8D8D4)  // JPN 
    , ADDRENGKOR(0x8D8D4)  // KOR 
};











// ULONG_PTR AddrCHTtoCHN(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT - (ULONG_PTR)0x98:  AddrCHT + (ULONG_PTR)0x98; }
// ULONG_PTR AddrCHTtoENG(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT - (ULONG_PTR)0x5B0: AddrCHT + (ULONG_PTR)0x5B0; }
// ULONG_PTR AddrCHTtoJPN(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT - (ULONG_PTR)0x1B0: AddrCHT + (ULONG_PTR)0x1B0; }
// ULONG_PTR AddrCHTtoKOR(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT - (ULONG_PTR)0x1B0: AddrCHT + (ULONG_PTR)0x1B0; }

// ULONG_PTR AddrCHNtoENG(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT - (ULONG_PTR)0x518: AddrCHT + (ULONG_PTR)0x518; }
// ULONG_PTR AddrCHNtoJPN(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT - (ULONG_PTR)0x118: AddrCHT + (ULONG_PTR)0x118; }
// ULONG_PTR AddrCHNtoKOR(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT + (ULONG_PTR)0x98:  AddrCHT - (ULONG_PTR)0x98; }

// ULONG_PTR AddrENGtoJPN(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT + (ULONG_PTR)0x400: AddrCHT - (ULONG_PTR)0x400; }
// ULONG_PTR AddrENGtoKOR(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT + (ULONG_PTR)0x5B0: AddrCHT - (ULONG_PTR)0x5B0; }

// ULONG_PTR AddrJPNtoKOR(ULONG_PTR AddrCHT, BOOL Reverse){ return Reverse?AddrCHT + (ULONG_PTR)0x1B0: AddrCHT - (ULONG_PTR)0x1B0; }
