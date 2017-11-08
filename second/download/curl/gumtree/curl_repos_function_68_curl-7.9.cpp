static int Kill_Single_Session(struct curl_ssl_session *session)
{
  if(session->sessionid) {
    /* defensive check */

    /* free the ID */
    SSL_SESSION_free(session->sessionid);
    session->sessionid=NULL;
    session->age = 0; /* fresh */
    free(session->name);
    session->name = NULL; /* no name */

    return 0; /* ok */
  }
  else
    return 1;
}