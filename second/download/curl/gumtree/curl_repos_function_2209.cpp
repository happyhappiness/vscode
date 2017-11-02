static CURLcode
cyassl_connect_step3(struct connectdata *conn,
                     int sockindex)
{
  CURLcode result = CURLE_OK;
  void *old_ssl_sessionid=NULL;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  bool incache;
  SSL_SESSION *our_ssl_sessionid;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  our_ssl_sessionid = SSL_get_session(connssl->handle);

  incache = !(Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL));
  if(incache) {
    if(old_ssl_sessionid != our_ssl_sessionid) {
      infof(data, "old SSL session ID is stale, removing\n");
      Curl_ssl_delsessionid(conn, old_ssl_sessionid);
      incache = FALSE;
    }
  }

  if(!incache) {
    result = Curl_ssl_addsessionid(conn, our_ssl_sessionid,
                                   0 /* unknown size */);
    if(result) {
      failf(data, "failed to store ssl session");
      return result;
    }
  }

  connssl->connecting_state = ssl_connect_done;

  return result;
}