static CURLcode
polarssl_connect_step3(struct connectdata *conn,
                     int sockindex)
{
  CURLcode result = CURLE_OK;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct SessionHandle *data = conn->data;
  void *old_ssl_sessionid = NULL;
  ssl_session *our_ssl_sessionid = &conn->ssl[sockindex].ssn ;
  bool incache;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  /* Save the current session data for possible re-use */
  incache = !(Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL));
  if(incache) {
    if(old_ssl_sessionid != our_ssl_sessionid) {
      infof(data, "old SSL session ID is stale, removing\n");
      Curl_ssl_delsessionid(conn, old_ssl_sessionid);
      incache = FALSE;
    }
  }

  if(!incache) {
    void *new_session = malloc(sizeof(ssl_session));

    if(new_session) {
      memcpy(new_session, our_ssl_sessionid, sizeof(ssl_session));

      result = Curl_ssl_addsessionid(conn, new_session, sizeof(ssl_session));
    }
    else
      result = CURLE_OUT_OF_MEMORY;

    if(result) {
      failf(data, "failed to store ssl session");
      return result;
    }
  }

  connssl->connecting_state = ssl_connect_done;

  return CURLE_OK;
}