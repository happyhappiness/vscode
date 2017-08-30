    32    start of data block



    */



    snprintf((char *)ntlmbuf, sizeof(ntlmbuf), "NTLMSSP%c"

             "\x01%c%c%c" /* 32-bit type = 1 */

             "%c%c%c%c"   /* 32-bit NTLM flag field */

             "%c%c"  /* domain length */

