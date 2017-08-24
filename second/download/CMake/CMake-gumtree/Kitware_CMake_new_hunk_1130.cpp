             SHORTPAIR(hostlen),
             SHORTPAIR(hostoff),
             0,0,
             host /* this is empty */, domain /* this is empty */);

    /* initial packet length */
    size = 32 + hostlen + domlen;
#endif

    DEBUG_OUT({
      fprintf(stderr, "**** TYPE1 header flags=0x%02.2x%02.2x%02.2x%02.2x 0x%08.8x ",
              LONGQUARTET(NTLMFLAG_NEGOTIATE_OEM|
                          NTLMFLAG_REQUEST_TARGET|
                          NTLMFLAG_NEGOTIATE_NTLM_KEY|
                          NTLM2FLAG|
                          NTLMFLAG_NEGOTIATE_ALWAYS_SIGN),
              NTLMFLAG_NEGOTIATE_OEM|
              NTLMFLAG_REQUEST_TARGET|
              NTLMFLAG_NEGOTIATE_NTLM_KEY|
              NTLM2FLAG|
              NTLMFLAG_NEGOTIATE_ALWAYS_SIGN);
      print_flags(stderr,
                  NTLMFLAG_NEGOTIATE_OEM|
                  NTLMFLAG_REQUEST_TARGET|
                  NTLMFLAG_NEGOTIATE_NTLM_KEY|
                  NTLM2FLAG|
                  NTLMFLAG_NEGOTIATE_ALWAYS_SIGN);
      fprintf(stderr, "\n****\n");
    });

    /* now size is the size of the base64 encoded package size */
    size = Curl_base64_encode(NULL, (char *)ntlmbuf, size, &base64);

    if(size >0 ) {
      Curl_safefree(*allocuserpwd);
      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                              proxy?"Proxy-":"",
                              base64);
      DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));
      free(base64);
    }
    else
