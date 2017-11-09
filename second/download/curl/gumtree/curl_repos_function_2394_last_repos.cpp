static CURLcode ossl_connect_step3(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  if(SSL_SET_OPTION(primary.sessionid)) {
    bool incache;
    SSL_SESSION *our_ssl_sessionid;
    void *old_ssl_sessionid = NULL;

    our_ssl_sessionid = SSL_get1_session(BACKEND->handle);

    /* SSL_get1_session() will increment the reference count and the session
        will stay in memory until explicitly freed with SSL_SESSION_free(3),
        regardless of its state. */

    Curl_ssl_sessionid_lock(conn);
    incache = !(Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL,
                                      sockindex));
    if(incache) {
      if(old_ssl_sessionid != our_ssl_sessionid) {
        infof(data, "old SSL session ID is stale, removing\n");
        Curl_ssl_delsessionid(conn, old_ssl_sessionid);
        incache = FALSE;
      }
    }

    if(!incache) {
      result = Curl_ssl_addsessionid(conn, our_ssl_sessionid,
                                      0 /* unknown size */, sockindex);
      if(result) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "failed to store ssl session");
        return result;
      }
    }
    else {
      /* Session was incache, so refcount already incremented earlier.
        * Avoid further increments with each SSL_get1_session() call.
        * This does not free the session as refcount remains > 0
        */
      SSL_SESSION_free(our_ssl_sessionid);
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  /*
   * We check certificates to authenticate the server; otherwise we risk
   * man-in-the-middle attack; NEVERTHELESS, if we're told explicitly not to
   * verify the peer ignore faults and failures from the server cert
   * operations.
   */

  result = servercert(conn, connssl, (SSL_CONN_CONFIG(verifypeer) ||
                                      SSL_CONN_CONFIG(verifyhost)));

  if(!result)
    connssl->connecting_state = ssl_connect_done;

  return result;
}