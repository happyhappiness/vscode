{
    /* We finished successfully our part of authentication, but server
     * rejected it (since we're again here). Exit with an error since we
     * can't invent anything better */
    Curl_auth_spnego_cleanup(nego);
    return CURLE_LOGIN_DENIED;
  }