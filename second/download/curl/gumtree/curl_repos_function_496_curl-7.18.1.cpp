static CURLcode
ossl_connect_step3(struct connectdata *conn,
                   int sockindex)
{
  CURLcode retcode = CURLE_OK;
  void *ssl_sessionid=NULL;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  if(Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL)) {
    /* Since this is not a cached session ID, then we want to stach this one
       in the cache! */
    SSL_SESSION *our_ssl_sessionid;
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
    retcode = Curl_ssl_addsessionid(conn, our_ssl_sessionid,
                                    0 /* unknown size */);
    if(retcode) {
      failf(data, "failed to store ssl session");
      return retcode;
    }
  }


  /*
   * We check certificates to authenticate the server; otherwise we risk
   * man-in-the-middle attack; NEVERTHELESS, if we're told explicitly not to
   * verify the peer ignore faults and failures from the server cert
   * operations.
   */

  if(!data->set.ssl.verifypeer)
    (void)servercert(conn, connssl, FALSE);
  else
    retcode = servercert(conn, connssl, TRUE);

  if(CURLE_OK == retcode)
    connssl->connecting_state = ssl_connect_done;
  return retcode;
}