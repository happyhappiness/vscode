    32    start of data block



    */

#if USE_NTLM2SESSION

#define NTLM2FLAG NTLMFLAG_NEGOTIATE_NTLM2_KEY

#else

#define NTLM2FLAG 0

#endif

    snprintf((char *)ntlmbuf, sizeof(ntlmbuf), NTLMSSP_SIGNATURE "%c"

             "\x01%c%c%c" /* 32-bit type = 1 */

             "%c%c%c%c"   /* 32-bit NTLM flag field */

             "%c%c"  /* domain length */

