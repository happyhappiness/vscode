{
    /* we always unconditionally get the session id here, as even if we
       already got it from the cache and asked to use it in the connection, it
       might've been rejected and then a new one is in use now and we need to
       detect that. */
    bool incache;
    void *ssl_sessionid;
    void *connect_sessionid;
    size_t connect_idsize = 0;

    /* get the session ID data size */
    gnutls_session_get_data(session, NULL, &connect_idsize);
    connect_sessionid = malloc(connect_idsize); /* get a buffer for it */

    if(connect_sessionid) {
      /* extract session ID to the allocated buffer */
      gnutls_session_get_data(session, connect_sessionid, &connect_idsize);

      Curl_ssl_sessionid_lock(conn);
      incache = !(Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL,
                                        sockindex));
      if(incache) {
        /* there was one before in the cache, so instead of risking that the
           previous one was rejected, we just kill that and store the new */
        Curl_ssl_delsessionid(conn, ssl_sessionid);
      }

      /* store this session id */
      result = Curl_ssl_addsessionid(conn, connect_sessionid, connect_idsize,
                                     sockindex);
      Curl_ssl_sessionid_unlock(conn);
      if(result) {
        free(connect_sessionid);
        result = CURLE_OUT_OF_MEMORY;
      }
    }
    else
      result = CURLE_OUT_OF_MEMORY;
  }