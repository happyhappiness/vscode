static int kill_session(struct curl_ssl_session *session)
{
  if(session->sessionid) {
    /* defensive check */

    /* free the ID the SSL-layer specific way */
#ifdef USE_SSLEAY
    Curl_ossl_session_free(session->sessionid);
#else
    Curl_gtls_session_free(session->sessionid);
#endif
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