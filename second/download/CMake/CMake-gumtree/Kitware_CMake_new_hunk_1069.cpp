    */

  {
#ifdef USE_WINDOWS_SSPI
    SecBuffer type_2, type_3;
    SecBufferDesc type_2_desc, type_3_desc;
    SECURITY_STATUS status;
    ULONG attrs;
    TimeStamp tsDummy; /* For Windows 9x compatibility of SPPI calls */

    type_2_desc.ulVersion  = type_3_desc.ulVersion  = SECBUFFER_VERSION;
    type_2_desc.cBuffers   = type_3_desc.cBuffers   = 1;
    type_2_desc.pBuffers   = &type_2;
    type_3_desc.pBuffers   = &type_3;

    type_2.BufferType = SECBUFFER_TOKEN;
    type_2.pvBuffer   = ntlm->type_2;
    type_2.cbBuffer   = ntlm->n_type_2;
    type_3.BufferType = SECBUFFER_TOKEN;
    type_3.pvBuffer   = ntlmbuf;
    type_3.cbBuffer   = sizeof(ntlmbuf);

    status = s_pSecFn->InitializeSecurityContext(&ntlm->handle, &ntlm->c_handle,
                                       (char *) host,
                                       ISC_REQ_CONFIDENTIALITY |
                                       ISC_REQ_REPLAY_DETECT |
                                       ISC_REQ_CONNECTION,
                                       0, SECURITY_NETWORK_DREP, &type_2_desc,
                                       0, &ntlm->c_handle, &type_3_desc,
                                       &attrs, &tsDummy);

    if (status != SEC_E_OK)
      return CURLE_RECV_ERROR;

    size = type_3.cbBuffer;

    ntlm_sspi_cleanup(ntlm);

#else
    int lmrespoff;
    unsigned char lmresp[24]; /* fixed-size */
#if USE_NTRESPONSES
    int ntrespoff;
    unsigned char ntresp[24]; /* fixed-size */
#endif
    size_t useroff;
    const char *user;
    size_t userlen;

    user = strchr(userp, '\\');
    if(!user)
      user = strchr(userp, '/');

    if (user) {
      domain = userp;
      domlen = (user - domain);
      user++;
    }
    else
      user = userp;
    userlen = strlen(user);

    if (gethostname(host, HOSTNAME_MAX)) {
      infof(conn->data, "gethostname() failed, continuing without!");
      hostlen = 0;
    }
    else {
      /* If the workstation if configured with a full DNS name (i.e.
       * workstation.somewhere.net) gethostname() returns the fully qualified
       * name, which NTLM doesn't like.
       */
      char *dot = strchr(host, '.');
      if (dot)
        *dot = '\0';
      hostlen = strlen(host);
    }

#if USE_NTLM2SESSION
    /* We don't support NTLM2 if we don't have USE_NTRESPONSES */
    if (ntlm->flags & NTLMFLAG_NEGOTIATE_NTLM2_KEY) {
      unsigned char ntbuffer[0x18];
      unsigned char tmp[0x18];
      unsigned char md5sum[MD5_DIGEST_LENGTH];
      MD5_CTX MD5;
      unsigned char random[8];

      /* Need to create 8 bytes random data */
      Curl_ossl_seed(conn->data); /* Initiate the seed if not already done */
      RAND_bytes(random,8);

      /* 8 bytes random data as challenge in lmresp */
      memcpy(lmresp,random,8);
      /* Pad with zeros */
      memset(lmresp+8,0,0x10);

      /* Fill tmp with challenge(nonce?) + random */
      memcpy(tmp,&ntlm->nonce[0],8);
      memcpy(tmp+8,random,8);

      MD5_Init(&MD5);
      MD5_Update(&MD5, tmp, 16);
      MD5_Final(md5sum, &MD5);
      /* We shall only use the first 8 bytes of md5sum,
         but the des code in lm_resp only encrypt the first 8 bytes */
      mk_nt_hash(conn->data, passwdp, ntbuffer);
      lm_resp(ntbuffer, md5sum, ntresp);

      /* End of NTLM2 Session code */
    }
    else {
#endif

#if USE_NTRESPONSES
      unsigned char ntbuffer[0x18];
#endif
      unsigned char lmbuffer[0x18];

#if USE_NTRESPONSES
      mk_nt_hash(conn->data, passwdp, ntbuffer);
      lm_resp(ntbuffer, &ntlm->nonce[0], ntresp);
#endif

      mk_lm_hash(conn->data, passwdp, lmbuffer);
      lm_resp(lmbuffer, &ntlm->nonce[0], lmresp);
      /* A safer but less compatible alternative is:
       *   lm_resp(ntbuffer, &ntlm->nonce[0], lmresp);
       * See http://davenport.sourceforge.net/ntlm.html#ntlmVersion2 */
#if USE_NTLM2SESSION
    }
#endif

    lmrespoff = 64; /* size of the message header */
#if USE_NTRESPONSES
    ntrespoff = lmrespoff + 0x18;
    domoff = ntrespoff + 0x18;
#else
    domoff = lmrespoff + 0x18;
#endif
    useroff = domoff + domlen;
    hostoff = useroff + userlen;

    /* Create the big type-3 message binary blob */
    size = snprintf((char *)ntlmbuf, sizeof(ntlmbuf),
                    NTLMSSP_SIGNATURE "%c"
                    "\x03%c%c%c" /* type-3, 32 bits */

                    "%c%c" /* LanManager length */
                    "%c%c" /* LanManager allocated space */
                    "%c%c" /* LanManager offset */
                    "%c%c" /* 2 zeroes */

