    */



  {

    int lmrespoff;

    int ntrespoff;

    int useroff;

    unsigned char lmresp[0x18]; /* fixed-size */

#ifdef USE_NTRESPONSES

    unsigned char ntresp[0x18]; /* fixed-size */

#endif

    const char *user;

    int userlen;



    user = strchr(userp, '\\');

    if(!user)

      user = strchr(userp, '/');



    if (user) {

      domain = userp;

      domlen = (int)(user - domain);

      user++;

    }

    else

      user = userp;

    userlen = (int)strlen(user);



    mkhash(passwdp, &ntlm->nonce[0], lmresp

#ifdef USE_NTRESPONSES

           , ntresp

#endif

      );



    domoff = 64; /* always */

    useroff = domoff + domlen;

    hostoff = useroff + userlen;

    lmrespoff = hostoff + hostlen;

    ntrespoff = lmrespoff + 0x18;



    /* Create the big type-3 message binary blob */

    size = snprintf((char *)ntlmbuf, sizeof(ntlmbuf),

                    "NTLMSSP%c"

                    "\x03%c%c%c" /* type-3, 32 bits */



                    "%c%c%c%c" /* LanManager length + allocated space */

                    "%c%c" /* LanManager offset */

                    "%c%c" /* 2 zeroes */



