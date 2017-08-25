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

                    "%c%c" /* NT-response length */
                    "%c%c" /* NT-response allocated space */
                    "%c%c" /* NT-response offset */
                    "%c%c" /* 2 zeroes */

                    "%c%c"  /* domain length */
                    "%c%c"  /* domain allocated space */
                    "%c%c"  /* domain name offset */
                    "%c%c"  /* 2 zeroes */

                    "%c%c"  /* user length */
                    "%c%c"  /* user allocated space */
                    "%c%c"  /* user offset */
                    "%c%c"  /* 2 zeroes */

                    "%c%c"  /* host length */
                    "%c%c"  /* host allocated space */
                    "%c%c"  /* host offset */
                    "%c%c%c%c%c%c"  /* 6 zeroes */

                    "\xff\xff"  /* message length */
                    "%c%c"  /* 2 zeroes */

                    "\x01\x82" /* flags */
                    "%c%c"  /* 2 zeroes */

                    /* domain string */
                    /* user string */
                    /* host string */
                    /* LanManager response */
                    /* NT response */
                    ,
                    0, /* zero termination */
                    0,0,0, /* type-3 long, the 24 upper bits */

                    SHORTPAIR(0x18),  /* LanManager response length, twice */
                    SHORTPAIR(0x18),
                    SHORTPAIR(lmrespoff),
                    0x0, 0x0,

#ifdef USE_NTRESPONSES
                    SHORTPAIR(0x18),  /* NT-response length, twice */
                    SHORTPAIR(0x18),
#else
                    0x0, 0x0,
                    0x0, 0x0,
#endif
                    SHORTPAIR(ntrespoff),
                    0x0, 0x0,

                    SHORTPAIR(domlen),
                    SHORTPAIR(domlen),
                    SHORTPAIR(domoff),
                    0x0, 0x0,

                    SHORTPAIR(userlen),
                    SHORTPAIR(userlen),
                    SHORTPAIR(useroff),
                    0x0, 0x0,

                    SHORTPAIR(hostlen),
                    SHORTPAIR(hostlen),
                    SHORTPAIR(hostoff),
                    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

                    0x0, 0x0,

                    0x0, 0x0);

    /* size is now 64 */
    size=64;
    ntlmbuf[62]=ntlmbuf[63]=0;

    memcpy(&ntlmbuf[size], domain, domlen);
    size += domlen;

    memcpy(&ntlmbuf[size], user, userlen);
    size += userlen;

    /* we append the binary hashes to the end of the blob */
    if(size < ((int)sizeof(ntlmbuf) - 0x18)) {
      memcpy(&ntlmbuf[size], lmresp, 0x18);
      size += 0x18;
    }

#ifdef USE_NTRESPONSES
    if(size < ((int)sizeof(ntlmbuf) - 0x18)) {
      memcpy(&ntlmbuf[size], ntresp, 0x18);
      size += 0x18;
    }
#endif

    ntlmbuf[56] = (unsigned char)(size & 0xff);
    ntlmbuf[57] = (unsigned char)(size >> 8);

    /* convert the binary blob into base64 */
    size = Curl_base64_encode((char *)ntlmbuf, size, &base64);

    if(size >0 ) {
      Curl_safefree(*allocuserpwd);
      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                              proxy?"Proxy-":"",
                              base64);
      free(base64);
    }
    else
      return CURLE_OUT_OF_MEMORY; /* FIX TODO */

    ntlm->state = NTLMSTATE_TYPE3; /* we sent a type-3 */
    authp->done = TRUE;
  }