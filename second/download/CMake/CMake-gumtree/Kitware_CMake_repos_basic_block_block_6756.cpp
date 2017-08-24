{
    /* unable to cache CRL */
    PR_Unlock(nss_crllock);
    return CURLE_SSL_CRL_BADFILE;
  }