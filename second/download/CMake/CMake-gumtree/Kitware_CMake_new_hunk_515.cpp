
  /* not set means empty */
  if(!userp)
    userp = "";

  if(!passwdp)
    passwdp = "";

#if defined(USE_WINDOWS_SSPI)
  have_chlg = digest->input_token ? TRUE : FALSE;
#else
  have_chlg = digest->nonce ? TRUE : FALSE;
#endif

  if(!have_chlg) {
    authp->done = FALSE;
    return CURLE_OK;
  }

  /* So IE browsers < v7 cut off the URI part at the query part when they
     evaluate the MD5 and some (IIS?) servers work with them so we may need to
