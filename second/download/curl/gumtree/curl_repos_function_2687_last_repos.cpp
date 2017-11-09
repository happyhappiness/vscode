static CURLcode
polarssl_connect_step3(struct connectdata *conn,
                       int sockindex)
{
  CURLcode retcode = CURLE_OK;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct Curl_easy *data = conn->data;

  DEBUGASSERT(ssl_connect_3 == connssl->connecting_state);

  if(SSL_SET_OPTION(primary.sessionid)) {
    int ret;
    ssl_session *our_ssl_sessionid;
    void *old_ssl_sessionid = NULL;

    our_ssl_sessionid = malloc(sizeof(ssl_session));
    if(!our_ssl_sessionid)
      return CURLE_OUT_OF_MEMORY;

    memset(our_ssl_sessionid, 0, sizeof(ssl_session));

    ret = ssl_get_session(&BACKEND->ssl, our_ssl_sessionid);
    if(ret) {
      failf(data, "ssl_get_session returned -0x%x", -ret);
      return CURLE_SSL_CONNECT_ERROR;
    }

    /* If there's already a matching session in the cache, delete it */
    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, &old_ssl_sessionid, NULL, sockindex))
      Curl_ssl_delsessionid(conn, old_ssl_sessionid);

    retcode = Curl_ssl_addsessionid(conn, our_ssl_sessionid, 0, sockindex);
    Curl_ssl_sessionid_unlock(conn);
    if(retcode) {
      free(our_ssl_sessionid);
      failf(data, "failed to store ssl session");
      return retcode;
    }
  }

  connssl->connecting_state = ssl_connect_done;

  return CURLE_OK;
}