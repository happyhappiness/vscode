CURLcode Curl_output_ntlm(struct connectdata *conn,
                          bool proxy)
{
  const char *domain=""; /* empty */
  const char *host=""; /* empty */
#ifndef USE_WINDOWS_SSPI
  int domlen=(int)strlen(domain);
  int hostlen = (int)strlen(host);
  int hostoff; /* host name offset */
  int domoff;  /* domain name offset */
#endif
  size_t size;
  char *base64=NULL;
  unsigned char ntlmbuf[256]; /* enough, unless the host/domain is very long */

  /* point to the address of the pointer that holds the string to sent to the
     server, which is for a plain host or for a HTTP proxy */
  char **allocuserpwd;

  /* point to the name and password for this */
  char *userp;
  char *passwdp;
  /* point to the correct struct with this */
  struct ntlmdata *ntlm;
  struct auth *authp;

  curlassert(conn);
  curlassert(conn->data);

  if(proxy) {
    allocuserpwd = &conn->allocptr.proxyuserpwd;
    userp = conn->proxyuser;
    passwdp = conn->proxypasswd;
    ntlm = &conn->proxyntlm;
    authp = &conn->data->state.authproxy;
  }
  else {
    allocuserpwd = &conn->allocptr.userpwd;
    userp = conn->user;
    passwdp = conn->passwd;
    ntlm = &conn->ntlm;
    authp = &conn->data->state.authhost;
  }
  authp->done = FALSE;

  /* not set means empty */
  if(!userp)
    userp=(char *)"";

  if(!passwdp)
    passwdp=(char *)"";

  switch(ntlm->state) {
  case NTLMSTATE_TYPE1:
  default: /* for the weird cases we (re)start here */
#ifdef USE_WINDOWS_SSPI
  {
    SecBuffer buf;
    SecBufferDesc desc;
    SECURITY_STATUS status;
    ULONG attrs;
    const char *user;
    int domlen;

    ntlm_sspi_cleanup(ntlm);

    user = strchr(userp, '\\');
    if (!user)
      user = strchr(userp, '/');

    if (user) {
      domain = userp;
      domlen = user - userp;
      user++;
    }
    else {
      user = userp;
      domain = "";
      domlen = 0;
    }

    if (user && *user) {
      /* note: initialize all of this before doing the mallocs so that
       * it can be cleaned up later without leaking memory.
       */
      ntlm->p_identity = &ntlm->identity;
      memset(ntlm->p_identity, 0, sizeof(*ntlm->p_identity));
      if ((ntlm->identity.User = (unsigned char *)strdup(user)) == NULL)
        return CURLE_OUT_OF_MEMORY;
      ntlm->identity.UserLength = strlen(user);
      if ((ntlm->identity.Password = (unsigned char *)strdup(passwdp)) == NULL)
        return CURLE_OUT_OF_MEMORY;
      ntlm->identity.PasswordLength = strlen(passwdp);
      if ((ntlm->identity.Domain = malloc(domlen+1)) == NULL)
        return CURLE_OUT_OF_MEMORY;
      strncpy((char *)ntlm->identity.Domain, domain, domlen);
      ntlm->identity.Domain[domlen] = '\0';
      ntlm->identity.DomainLength = domlen;
      ntlm->identity.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
    }
    else {
      ntlm->p_identity = NULL;
    }

    if (AcquireCredentialsHandle(
          NULL, (char *)"NTLM", SECPKG_CRED_OUTBOUND, NULL, ntlm->p_identity,
          NULL, NULL, &ntlm->handle, NULL
        ) != SEC_E_OK) {
      return CURLE_OUT_OF_MEMORY;
    }

    desc.ulVersion = SECBUFFER_VERSION;
    desc.cBuffers  = 1;
    desc.pBuffers  = &buf;
    buf.cbBuffer   = sizeof(ntlmbuf);
    buf.BufferType = SECBUFFER_TOKEN;
    buf.pvBuffer   = ntlmbuf;

    status = InitializeSecurityContext(&ntlm->handle, NULL, (char *) host,
                                       ISC_REQ_CONFIDENTIALITY |
                                       ISC_REQ_REPLAY_DETECT |
                                       ISC_REQ_CONNECTION,
                                       0, SECURITY_NETWORK_DREP, NULL, 0,
                                       &ntlm->c_handle, &desc, &attrs, NULL
                                      );

    if (status == SEC_I_COMPLETE_AND_CONTINUE ||
        status == SEC_I_CONTINUE_NEEDED) {
      CompleteAuthToken(&ntlm->c_handle, &desc);
    }
    else if (status != SEC_E_OK) {
      FreeCredentialsHandle(&ntlm->handle);
      return CURLE_RECV_ERROR;
    }

    ntlm->has_handles = 1;
    size = buf.cbBuffer;
  }
#else
    hostoff = 32;
    domoff = hostoff + hostlen;

    /* Create and send a type-1 message:

    Index Description          Content
    0     NTLMSSP Signature    Null-terminated ASCII "NTLMSSP"
                               (0x4e544c4d53535000)
    8     NTLM Message Type    long (0x01000000)
    12    Flags                long
    16    Supplied Domain      security buffer(*)
    24    Supplied Workstation security buffer(*)
    32    start of data block

    */

    snprintf((char *)ntlmbuf, sizeof(ntlmbuf), "NTLMSSP%c"
             "\x01%c%c%c" /* 32-bit type = 1 */
             "%c%c%c%c"   /* 32-bit NTLM flag field */
             "%c%c"  /* domain length */
             "%c%c"  /* domain allocated space */
             "%c%c"  /* domain name offset */
             "%c%c"  /* 2 zeroes */
             "%c%c"  /* host length */
             "%c%c"  /* host allocated space */
             "%c%c"  /* host name offset */
             "%c%c"  /* 2 zeroes */
             "%s"   /* host name */
             "%s",  /* domain string */
             0,     /* trailing zero */
             0,0,0, /* part of type-1 long */

             LONGQUARTET(
               NTLMFLAG_NEGOTIATE_OEM|      /*   2 */
               NTLMFLAG_NEGOTIATE_NTLM_KEY  /* 200 */
               /* equals 0x0202 */
               ),
             SHORTPAIR(domlen),
             SHORTPAIR(domlen),
             SHORTPAIR(domoff),
             0,0,
             SHORTPAIR(hostlen),
             SHORTPAIR(hostlen),
             SHORTPAIR(hostoff),
             0,0,
             host, domain);

    /* initial packet length */
    size = 32 + hostlen + domlen;
#endif

    /* now keeper of the base64 encoded package size */
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

    break;

  case NTLMSTATE_TYPE2:
    /* We received the type-2 already, create a type-3 message:

    Index   Description            Content
    0       NTLMSSP Signature      Null-terminated ASCII "NTLMSSP"
                                   (0x4e544c4d53535000)
    8       NTLM Message Type      long (0x03000000)
    12      LM/LMv2 Response       security buffer(*)
    20      NTLM/NTLMv2 Response   security buffer(*)
    28      Domain Name            security buffer(*)
    36      User Name              security buffer(*)
    44      Workstation Name       security buffer(*)
    (52)    Session Key (optional) security buffer(*)
    (60)    Flags (optional)       long
    52 (64) start of data block

    */

  {
#ifdef USE_WINDOWS_SSPI
    SecBuffer type_2, type_3;
    SecBufferDesc type_2_desc, type_3_desc;
    SECURITY_STATUS status;
    ULONG attrs;

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

    status = InitializeSecurityContext(&ntlm->handle, &ntlm->c_handle,
                                       (char *) host,
                                       ISC_REQ_CONFIDENTIALITY |
                                       ISC_REQ_REPLAY_DETECT |
                                       ISC_REQ_CONNECTION,
                                       0, SECURITY_NETWORK_DREP, &type_2_desc,
                                       0, &ntlm->c_handle, &type_3_desc,
                                       &attrs, NULL);

    if (status != SEC_E_OK)
      return CURLE_RECV_ERROR;

    size = type_3.cbBuffer;

    ntlm_sspi_cleanup(ntlm);

#else
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

#endif

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
  break;

  case NTLMSTATE_TYPE3:
    /* connection is already authenticated,
     * don't send a header in future requests */
    if(*allocuserpwd) {
      free(*allocuserpwd);
      *allocuserpwd=NULL;
    }
    authp->done = TRUE;
    break;
  }

  return CURLE_OK;
}