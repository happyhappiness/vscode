static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;
  void *old_ssl_sessionid = NULL;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  bool incache;
  SSL_SESSION *our_ssl_sessionid;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

#ifdef HAVE_SSL_GET1_SESSION
  our_ssl_sessionid = SSL_get1_session(connssl->handle);

  /* SSL_get1_session() will increment the reference
     count and the session will stay in memory until explicitly freed with
     SSL_SESSION_free(3), regardless of its state.
     This function was introduced in openssl 0.9.5a. */
#else
  our_ssl_sessionid = SSL_get_session(connssl->handle);

  /* if SSL_get1_session() is unavailable, use SSL_get_session().
     This is an inferior option because the session can be flushed
     at any time by openssl. It is included only so curl compiles
     under versions of openssl < 0.9.5a.

     WARNING: How curl behaves if it's session is flushed is
     untested.
  */
#endif

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
#ifdef HAVE_SSL_GET1_SESSION
  else {
    /* Session was incache, so refcount already incremented earlier.
     * Avoid further increments with each SSL_get1_session() call.
     * This does not free the session as refcount remains > 0
     */
    SSL_SESSION_free(our_ssl_sessionid);
  }
#endif

  /*
   * We check certificates to authenticate the server; otherwise we risk
   * man-in-the-middle attack; NEVERTHELESS, if we're told explicitly not to
   * verify the peer ignore faults and failures from the server cert
   * operations.
   */

  result = servercert(conn, connssl,
                      (data->set.ssl.verifypeer || data->set.ssl.verifyhost));

  if(!result)
    connssl->connecting_state = ssl_connect_done;

  return result;
}