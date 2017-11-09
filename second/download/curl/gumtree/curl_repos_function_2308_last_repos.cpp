CURLcode Curl_auth_create_ntlm_type1_message(struct Curl_easy *data,
                                             const char *userp,
                                             const char *passwdp,
                                             struct ntlmdata *ntlm,
                                             char **outptr, size_t *outlen)
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

  size_t size;

  unsigned char ntlmbuf[NTLM_BUFSIZE];
  const char *host = "";              /* empty */
  const char *domain = "";            /* empty */
  size_t hostlen = 0;
  size_t domlen = 0;
  size_t hostoff = 0;
  size_t domoff = hostoff + hostlen;  /* This is 0: remember that host and
                                         domain are empty */
  (void)userp;
  (void)passwdp;

  /* Clean up any former leftovers and initialise to defaults */
  Curl_auth_ntlm_cleanup(ntlm);

#if defined(USE_NTRESPONSES) && defined(USE_NTLM2SESSION)
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
  return Curl_base64_encode(data, (char *)ntlmbuf, size, outptr, outlen);
}