CURLcode Curl_ntlm_create_type3_message(struct SessionHandle *data,
                                        const char *userp,
                                        const char *passwdp,
                                        struct ntlmdata *ntlm,
                                        char **outptr,
                                        size_t *outlen)
{
  /* NTLM type-3 message structure:

          Index  Description            Content
            0    NTLMSSP Signature      Null-terminated ASCII "NTLMSSP"
                                        (0x4e544c4d53535000)
            8    NTLM Message Type      long (0x03000000)
           12    LM/LMv2 Response       security buffer
           20    NTLM/NTLMv2 Response   security buffer
           28    Target Name            security buffer
           36    User Name              security buffer
           44    Workstation Name       security buffer
          (52)   Session Key            security buffer (*)
          (60)   Flags                  long (*)
          (64)   OS Version Structure   8 bytes (*)
  52 (64) (72)   Start of data block
                                          (*) -> Optional
  */

  unsigned char ntlmbuf[NTLM_BUFSIZE];
  size_t size;

#ifdef USE_WINDOWS_SSPI
  SecBuffer type_2;
  SecBuffer type_3;
  SecBufferDesc type_2_desc;
  SecBufferDesc type_3_desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  TimeStamp tsDummy; /* For Windows 9x compatibility of SSPI calls */

  (void)passwdp;
  (void)userp;
  (void)data;

  type_2_desc.ulVersion = type_3_desc.ulVersion  = SECBUFFER_VERSION;
  type_2_desc.cBuffers  = type_3_desc.cBuffers   = 1;
  type_2_desc.pBuffers  = &type_2;
  type_3_desc.pBuffers  = &type_3;

  type_2.BufferType = SECBUFFER_TOKEN;
  type_2.pvBuffer   = ntlm->type_2;
  type_2.cbBuffer   = ntlm->n_type_2;
  type_3.BufferType = SECBUFFER_TOKEN;
  type_3.pvBuffer   = ntlmbuf;
  type_3.cbBuffer   = NTLM_BUFSIZE;

  status = s_pSecFn->InitializeSecurityContext(&ntlm->handle,
                                               &ntlm->c_handle,
                                               (TCHAR *) TEXT(""),
                                               ISC_REQ_CONFIDENTIALITY |
                                               ISC_REQ_REPLAY_DETECT |
                                               ISC_REQ_CONNECTION,
                                               0, SECURITY_NETWORK_DREP,
                                               &type_2_desc,
                                               0, &ntlm->c_handle,
                                               &type_3_desc,
                                               &attrs, &tsDummy);
  if(status != SEC_E_OK)
    return CURLE_RECV_ERROR;

  size = type_3.cbBuffer;

  Curl_ntlm_sspi_cleanup(ntlm);

#else
  int lmrespoff;
  unsigned char lmresp[24]; /* fixed-size */
#if USE_NTRESPONSES
  int ntrespoff;
  unsigned char ntresp[24]; /* fixed-size */
#endif
  bool unicode = (ntlm->flags & NTLMFLAG_NEGOTIATE_UNICODE) ? TRUE : FALSE;
  char host[HOSTNAME_MAX + 1] = "";
  const char *user;
  const char *domain = "";
  size_t hostoff = 0;
  size_t useroff = 0;
  size_t domoff = 0;
  size_t hostlen = 0;
  size_t userlen = 0;
  size_t domlen = 0;
  CURLcode res;

  user = strchr(userp, '\\');
  if(!user)
    user = strchr(userp, '/');

  if(user) {
    domain = userp;
    domlen = (user - domain);
    user++;
  }
  else
    user = userp;

  if(user)
    userlen = strlen(user);

  /* Get the machine's un-qualified host name as NTLM doesn't like the fully
     qualified domain name */
  if(Curl_gethostname(host, sizeof(host))) {
    infof(data, "gethostname() failed, continuing without!\n");
    hostlen = 0;
  }
  else {
    hostlen = strlen(host);
  }

  if(unicode) {
    domlen = domlen * 2;
    userlen = userlen * 2;
    hostlen = hostlen * 2;
  }

#if USE_NTLM2SESSION
  /* We don't support NTLM2 if we don't have USE_NTRESPONSES */
  if(ntlm->flags & NTLMFLAG_NEGOTIATE_NTLM2_KEY) {
    unsigned char ntbuffer[0x18];
    unsigned char tmp[0x18];
    unsigned char md5sum[MD5_DIGEST_LENGTH];
    unsigned char entropy[8];

    /* Need to create 8 bytes random data */
    Curl_ssl_random(data, entropy, sizeof(entropy));

    /* 8 bytes random data as challenge in lmresp */
    memcpy(lmresp, entropy, 8);

    /* Pad with zeros */
    memset(lmresp + 8, 0, 0x10);

    /* Fill tmp with challenge(nonce?) + entropy */
    memcpy(tmp, &ntlm->nonce[0], 8);
    memcpy(tmp + 8, entropy, 8);

    Curl_ssl_md5sum(tmp, 16, md5sum, MD5_DIGEST_LENGTH);

    /* We shall only use the first 8 bytes of md5sum, but the des
       code in Curl_ntlm_core_lm_resp only encrypt the first 8 bytes */
    if(CURLE_OUT_OF_MEMORY ==
       Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer))
      return CURLE_OUT_OF_MEMORY;
    Curl_ntlm_core_lm_resp(ntbuffer, md5sum, ntresp);

    /* End of NTLM2 Session code */
  }
  else
#endif
  {

#if USE_NTRESPONSES
    unsigned char ntbuffer[0x18];
#endif
    unsigned char lmbuffer[0x18];

#if USE_NTRESPONSES
    if(CURLE_OUT_OF_MEMORY ==
       Curl_ntlm_core_mk_nt_hash(data, passwdp, ntbuffer))
      return CURLE_OUT_OF_MEMORY;
    Curl_ntlm_core_lm_resp(ntbuffer, &ntlm->nonce[0], ntresp);
#endif

    Curl_ntlm_core_mk_lm_hash(data, passwdp, lmbuffer);
    Curl_ntlm_core_lm_resp(lmbuffer, &ntlm->nonce[0], lmresp);
    /* A safer but less compatible alternative is:
     *   Curl_ntlm_core_lm_resp(ntbuffer, &ntlm->nonce[0], lmresp);
     * See http://davenport.sourceforge.net/ntlm.html#ntlmVersion2 */
  }

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
  size = snprintf((char *)ntlmbuf, NTLM_BUFSIZE,
                  NTLMSSP_SIGNATURE "%c"
                  "\x03%c%c%c"  /* 32-bit type = 3 */

                  "%c%c"  /* LanManager length */
                  "%c%c"  /* LanManager allocated space */
                  "%c%c"  /* LanManager offset */
                  "%c%c"  /* 2 zeroes */

                  "%c%c"  /* NT-response length */
                  "%c%c"  /* NT-response allocated space */
                  "%c%c"  /* NT-response offset */
                  "%c%c"  /* 2 zeroes */

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
                  "%c%c"  /* 2 zeroes */

                  "%c%c"  /* session key length (unknown purpose) */
                  "%c%c"  /* session key allocated space (unknown purpose) */
                  "%c%c"  /* session key offset (unknown purpose) */
                  "%c%c"  /* 2 zeroes */

                  "%c%c%c%c",  /* flags */

                  /* domain string */
                  /* user string */
                  /* host string */
                  /* LanManager response */
                  /* NT response */

                  0,                /* zero termination */
                  0, 0, 0,          /* type-3 long, the 24 upper bits */

                  SHORTPAIR(0x18),  /* LanManager response length, twice */
                  SHORTPAIR(0x18),
                  SHORTPAIR(lmrespoff),
                  0x0, 0x0,

#if USE_NTRESPONSES
                  SHORTPAIR(0x18),  /* NT-response length, twice */
                  SHORTPAIR(0x18),
                  SHORTPAIR(ntrespoff),
                  0x0, 0x0,
#else
                  0x0, 0x0,
                  0x0, 0x0,
                  0x0, 0x0,
                  0x0, 0x0,
#endif
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
                  0x0, 0x0,

                  0x0, 0x0,
                  0x0, 0x0,
                  0x0, 0x0,
                  0x0, 0x0,

                  LONGQUARTET(ntlm->flags));

  DEBUGASSERT(size == 64);
  DEBUGASSERT(size == (size_t)lmrespoff);

  /* We append the binary hashes */
  if(size < (NTLM_BUFSIZE - 0x18)) {
    memcpy(&ntlmbuf[size], lmresp, 0x18);
    size += 0x18;
  }

  DEBUG_OUT({
    fprintf(stderr, "**** TYPE3 header lmresp=");
    ntlm_print_hex(stderr, (char *)&ntlmbuf[lmrespoff], 0x18);
  });

#if USE_NTRESPONSES
  if(size < (NTLM_BUFSIZE - 0x18)) {
    DEBUGASSERT(size == (size_t)ntrespoff);
    memcpy(&ntlmbuf[size], ntresp, 0x18);
    size += 0x18;
  }

  DEBUG_OUT({
    fprintf(stderr, "\n   ntresp=");
    ntlm_print_hex(stderr, (char *)&ntlmbuf[ntrespoff], 0x18);
  });

#endif

  DEBUG_OUT({
    fprintf(stderr, "\n   flags=0x%02.2x%02.2x%02.2x%02.2x 0x%08.8x ",
            LONGQUARTET(ntlm->flags), ntlm->flags);
    ntlm_print_flags(stderr, ntlm->flags);
    fprintf(stderr, "\n****\n");
  });

  /* Make sure that the domain, user and host strings fit in the
     buffer before we copy them there. */
  if(size + userlen + domlen + hostlen >= NTLM_BUFSIZE) {
    failf(data, "user + domain + host name too big");
    return CURLE_OUT_OF_MEMORY;
  }

  DEBUGASSERT(size == domoff);
  if(unicode)
    unicodecpy(&ntlmbuf[size], domain, domlen / 2);
  else
    memcpy(&ntlmbuf[size], domain, domlen);

  size += domlen;

  DEBUGASSERT(size == useroff);
  if(unicode)
    unicodecpy(&ntlmbuf[size], user, userlen / 2);
  else
    memcpy(&ntlmbuf[size], user, userlen);

  size += userlen;

  DEBUGASSERT(size == hostoff);
  if(unicode)
    unicodecpy(&ntlmbuf[size], host, hostlen / 2);
  else
    memcpy(&ntlmbuf[size], host, hostlen);

  size += hostlen;

  /* Convert domain, user, and host to ASCII but leave the rest as-is */
  res = Curl_convert_to_network(data, (char *)&ntlmbuf[domoff],
                                size - domoff);
  if(res)
    return CURLE_CONV_FAILED;

#endif

  /* Return with binary blob encoded into base64 */
  return Curl_base64_encode(NULL, (char *)ntlmbuf, size, outptr, outlen);
}