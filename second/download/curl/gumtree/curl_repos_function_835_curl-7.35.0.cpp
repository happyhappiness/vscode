CURLcode Curl_ntlm_create_type1_message(const char *userp,
                                        const char *passwdp,
                                        struct ntlmdata *ntlm,
                                        char **outptr,
                                        size_t *outlen)
{
  /* NTLM type-1 message structure:

       Index  Description            Content
         0    NTLMSSP Signature      Null-terminated ASCII "NTLMSSP"
                                     (0x4e544c4d53535000)
         8    NTLM Message Type      long (0x01000000)
        12    Flags                  long
       (16)   Supplied Domain        security buffer (*)
       (24)   Supplied Workstation   security buffer (*)
       (32)   OS Version Structure   8 bytes (*)
  (32) (40)   Start of data block    (*)
                                     (*) -> Optional
  */

  unsigned char ntlmbuf[NTLM_BUFSIZE];
  size_t size;

#ifdef USE_WINDOWS_SSPI

  SecBuffer buf;
  SecBufferDesc desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  xcharp_u useranddomain;
  xcharp_u user, dup_user;
  xcharp_u domain, dup_domain;
  xcharp_u passwd, dup_passwd;
  size_t domlen = 0;
  TimeStamp tsDummy; /* For Windows 9x compatibility of SSPI calls */

  domain.const_tchar_ptr = TEXT("");

  Curl_ntlm_sspi_cleanup(ntlm);

  if(userp && *userp) {

    /* null initialize ntlm identity's data to allow proper cleanup */
    ntlm->p_identity = &ntlm->identity;
    memset(ntlm->p_identity, 0, sizeof(*ntlm->p_identity));

    useranddomain.tchar_ptr = Curl_convert_UTF8_to_tchar((char *)userp);
    if(!useranddomain.tchar_ptr)
      return CURLE_OUT_OF_MEMORY;

    user.const_tchar_ptr = _tcschr(useranddomain.const_tchar_ptr, TEXT('\\'));
    if(!user.const_tchar_ptr)
      user.const_tchar_ptr = _tcschr(useranddomain.const_tchar_ptr, TEXT('/'));

    if(user.tchar_ptr) {
      domain.tchar_ptr = useranddomain.tchar_ptr;
      domlen = user.tchar_ptr - useranddomain.tchar_ptr;
      user.tchar_ptr++;
    }
    else {
      user.tchar_ptr = useranddomain.tchar_ptr;
      domain.const_tchar_ptr = TEXT("");
      domlen = 0;
    }

    /* setup ntlm identity's user and length */
    dup_user.tchar_ptr = _tcsdup(user.tchar_ptr);
    if(!dup_user.tchar_ptr) {
      Curl_unicodefree(useranddomain.tchar_ptr);
      return CURLE_OUT_OF_MEMORY;
    }
    ntlm->identity.User = dup_user.tbyte_ptr;
    ntlm->identity.UserLength = curlx_uztoul(_tcslen(dup_user.tchar_ptr));
    dup_user.tchar_ptr = NULL;

    /* setup ntlm identity's domain and length */
    dup_domain.tchar_ptr = malloc(sizeof(TCHAR) * (domlen + 1));
    if(!dup_domain.tchar_ptr) {
      Curl_unicodefree(useranddomain.tchar_ptr);
      return CURLE_OUT_OF_MEMORY;
    }
    _tcsncpy(dup_domain.tchar_ptr, domain.tchar_ptr, domlen);
    *(dup_domain.tchar_ptr + domlen) = TEXT('\0');
    ntlm->identity.Domain = dup_domain.tbyte_ptr;
    ntlm->identity.DomainLength = curlx_uztoul(domlen);
    dup_domain.tchar_ptr = NULL;

    Curl_unicodefree(useranddomain.tchar_ptr);

    /* setup ntlm identity's password and length */
    passwd.tchar_ptr = Curl_convert_UTF8_to_tchar((char *)passwdp);
    if(!passwd.tchar_ptr)
      return CURLE_OUT_OF_MEMORY;
    dup_passwd.tchar_ptr = _tcsdup(passwd.tchar_ptr);
    if(!dup_passwd.tchar_ptr) {
      Curl_unicodefree(passwd.tchar_ptr);
      return CURLE_OUT_OF_MEMORY;
    }
    ntlm->identity.Password = dup_passwd.tbyte_ptr;
    ntlm->identity.PasswordLength =
      curlx_uztoul(_tcslen(dup_passwd.tchar_ptr));
    dup_passwd.tchar_ptr = NULL;

    Curl_unicodefree(passwd.tchar_ptr);

    /* setup ntlm identity's flags */
    ntlm->identity.Flags = SECFLAG_WINNT_AUTH_IDENTITY;
  }
  else
    ntlm->p_identity = NULL;

  status = s_pSecFn->AcquireCredentialsHandle(NULL,
                                              (TCHAR *) TEXT("NTLM"),
                                              SECPKG_CRED_OUTBOUND, NULL,
                                              ntlm->p_identity, NULL, NULL,
                                              &ntlm->handle, &tsDummy);
  if(status != SEC_E_OK)
    return CURLE_OUT_OF_MEMORY;

  desc.ulVersion = SECBUFFER_VERSION;
  desc.cBuffers  = 1;
  desc.pBuffers  = &buf;
  buf.cbBuffer   = NTLM_BUFSIZE;
  buf.BufferType = SECBUFFER_TOKEN;
  buf.pvBuffer   = ntlmbuf;

  status = s_pSecFn->InitializeSecurityContext(&ntlm->handle, NULL,
                                               (TCHAR *) TEXT(""),
                                               ISC_REQ_CONFIDENTIALITY |
                                               ISC_REQ_REPLAY_DETECT |
                                               ISC_REQ_CONNECTION,
                                               0, SECURITY_NETWORK_DREP,
                                               NULL, 0,
                                               &ntlm->c_handle, &desc,
                                               &attrs, &tsDummy);

  if(status == SEC_I_COMPLETE_AND_CONTINUE ||
     status == SEC_I_CONTINUE_NEEDED)
    s_pSecFn->CompleteAuthToken(&ntlm->c_handle, &desc);
  else if(status != SEC_E_OK) {
    s_pSecFn->FreeCredentialsHandle(&ntlm->handle);
    return CURLE_RECV_ERROR;
  }

  ntlm->has_handles = 1;
  size = buf.cbBuffer;

#else

  const char *host = "";              /* empty */
  const char *domain = "";            /* empty */
  size_t hostlen = 0;
  size_t domlen = 0;
  size_t hostoff = 0;
  size_t domoff = hostoff + hostlen;  /* This is 0: remember that host and
                                         domain are empty */
  (void)userp;
  (void)passwdp;
  (void)ntlm;

#if USE_NTLM2SESSION
#define NTLM2FLAG NTLMFLAG_NEGOTIATE_NTLM2_KEY
#else
#define NTLM2FLAG 0
#endif
  snprintf((char *)ntlmbuf, NTLM_BUFSIZE,
           NTLMSSP_SIGNATURE "%c"
           "\x01%c%c%c" /* 32-bit type = 1 */
           "%c%c%c%c"   /* 32-bit NTLM flag field */
           "%c%c"       /* domain length */
           "%c%c"       /* domain allocated space */
           "%c%c"       /* domain name offset */
           "%c%c"       /* 2 zeroes */
           "%c%c"       /* host length */
           "%c%c"       /* host allocated space */
           "%c%c"       /* host name offset */
           "%c%c"       /* 2 zeroes */
           "%s"         /* host name */
           "%s",        /* domain string */
           0,           /* trailing zero */
           0, 0, 0,     /* part of type-1 long */

           LONGQUARTET(NTLMFLAG_NEGOTIATE_OEM |
                       NTLMFLAG_REQUEST_TARGET |
                       NTLMFLAG_NEGOTIATE_NTLM_KEY |
                       NTLM2FLAG |
                       NTLMFLAG_NEGOTIATE_ALWAYS_SIGN),
           SHORTPAIR(domlen),
           SHORTPAIR(domlen),
           SHORTPAIR(domoff),
           0, 0,
           SHORTPAIR(hostlen),
           SHORTPAIR(hostlen),
           SHORTPAIR(hostoff),
           0, 0,
           host,  /* this is empty */
           domain /* this is empty */);

  /* Initial packet length */
  size = 32 + hostlen + domlen;

#endif

  DEBUG_OUT({
    fprintf(stderr, "* TYPE1 header flags=0x%02.2x%02.2x%02.2x%02.2x "
            "0x%08.8x ",
            LONGQUARTET(NTLMFLAG_NEGOTIATE_OEM |
                        NTLMFLAG_REQUEST_TARGET |
                        NTLMFLAG_NEGOTIATE_NTLM_KEY |
                        NTLM2FLAG |
                        NTLMFLAG_NEGOTIATE_ALWAYS_SIGN),
            NTLMFLAG_NEGOTIATE_OEM |
            NTLMFLAG_REQUEST_TARGET |
            NTLMFLAG_NEGOTIATE_NTLM_KEY |
            NTLM2FLAG |
            NTLMFLAG_NEGOTIATE_ALWAYS_SIGN);
    ntlm_print_flags(stderr,
                     NTLMFLAG_NEGOTIATE_OEM |
                     NTLMFLAG_REQUEST_TARGET |
                     NTLMFLAG_NEGOTIATE_NTLM_KEY |
                     NTLM2FLAG |
                     NTLMFLAG_NEGOTIATE_ALWAYS_SIGN);
    fprintf(stderr, "\n****\n");
  });

  /* Return with binary blob encoded into base64 */
  return Curl_base64_encode(NULL, (char *)ntlmbuf, size, outptr, outlen);
}