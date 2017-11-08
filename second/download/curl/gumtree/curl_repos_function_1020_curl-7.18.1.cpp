static int kill_session(struct curl_ssl_session *session)
{
  if(session->sessionid) {
    /* defensive check */

    /* free the ID the SSL-layer specific way */
#ifdef USE_SSLEAY
    Curl_ossl_session_free(session->sessionid);
#else
#ifdef USE_GNUTLS
    Curl_gtls_session_free(session->sessionid);
#else
#ifdef USE_QSOSSL
    /* No session handling for QsoSSL. */
#else
#ifdef USE_NSS
    /* NSS has its own session ID cache */
#endif /* USE_NSS */
#endif /* USE_QSOSSL */
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
    session->sessionid=NULL;
    session->age = 0; /* fresh */

    Curl_free_ssl_config(&session->ssl_config);

    Curl_safefree(session->name);
    session->name = NULL; /* no name */

    return 0; /* ok */
  }
  else
    return 1;
}