static CURLcode pkp_pin_peer_pubkey(X509* cert, const char *pinnedpubkey)
{
  /* Scratch */
  int len1 = 0, len2 = 0;
  unsigned char *buff1 = NULL, *temp = NULL;

  /* Result is returned to caller */
  CURLcode result = CURLE_SSL_PINNEDPUBKEYNOTMATCH;

  /* if a path wasn't specified, don't pin */
  if(!pinnedpubkey)
    return CURLE_OK;

  if(!cert)
    return result;

  do {
    /* Begin Gyrations to get the subjectPublicKeyInfo     */
    /* Thanks to Viktor Dukhovni on the OpenSSL mailing list */

    /* http://groups.google.com/group/mailing.openssl.users/browse_thread
     /thread/d61858dae102c6c7 */
    len1 = i2d_X509_PUBKEY(X509_get_X509_PUBKEY(cert), NULL);
    if(len1 < 1)
      break; /* failed */

    /* http://www.openssl.org/docs/crypto/buffer.html */
    buff1 = temp = OPENSSL_malloc(len1);
    if(!buff1)
      break; /* failed */

    /* http://www.openssl.org/docs/crypto/d2i_X509.html */
    len2 = i2d_X509_PUBKEY(X509_get_X509_PUBKEY(cert), &temp);

    /*
     * These checks are verifying we got back the same values as when we
     * sized the buffer.Its pretty weak since they should always be the
     * same. But it gives us something to test.
     */
    if((len1 != len2) || !temp || ((temp - buff1) != len1))
      break; /* failed */

    /* End Gyrations */

    /* The one good exit point */
    result = Curl_pin_peer_pubkey(pinnedpubkey, buff1, len1);
  } while(0);

  /* http://www.openssl.org/docs/crypto/buffer.html */
  if(buff1)
    OPENSSL_free(buff1);

  return result;
}