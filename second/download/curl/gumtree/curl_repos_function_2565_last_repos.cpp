void Curl_ssl_kill_session(struct curl_ssl_session *session)
{
  if(session->sessionid) {
    /* defensive check */

    /* free the ID the SSL-layer specific way */
    Curl_ssl->session_free(session->sessionid);

    session->sessionid = NULL;
    session->age = 0; /* fresh */

    Curl_free_primary_ssl_config(&session->ssl_config);

    Curl_safefree(session->name);
    Curl_safefree(session->conn_to_host);
  }
}