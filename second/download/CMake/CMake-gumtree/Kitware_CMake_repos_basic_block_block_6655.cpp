{
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