{
    void *ssl_sessionid;
    size_t ssl_idsize;

    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, &ssl_idsize, sockindex)) {
      /* we got a session id, use it! */
      gnutls_session_set_data(session, ssl_sessionid, ssl_idsize);

      /* Informational message */
      infof(data, "SSL re-using session ID\n");
    }
    Curl_ssl_sessionid_unlock(conn);
  }