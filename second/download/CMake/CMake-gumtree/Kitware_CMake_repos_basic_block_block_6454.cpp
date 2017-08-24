f(!Curl_ssl_getsessionid(conn, (void **)&ssl_sessionid,
                              &ssl_sessionid_len, sockindex)) {
      /* we got a session id, use it! */
      err = SSLSetPeerID(connssl->ssl_ctx, ssl_sessionid, ssl_sessionid_len);
      Curl_ssl_sessionid_unlock(conn);
      if(err != noErr) {
        failf(data, "SSL: SSLSetPeerID() failed: OSStatus %d", err);
        return CURLE_SSL_CONNECT_ERROR;
      }
      /* Informational message */
      infof(data, "SSL re-using session ID\n");
    }
    /* If there isn't one, then let's make one up! This has to be done prior
       to starting the handshake. */
    else {
      CURLcode result;
      ssl_sessionid =
        aprintf("%s:%d:%d:%s:%hu", ssl_cafile,
                verifypeer, SSL_CONN_CONFIG(verifyhost), hostname, port);
      ssl_sessionid_len = strlen(ssl_sessionid);

      err = SSLSetPeerID(connssl->ssl_ctx, ssl_sessionid, ssl_sessionid_len);
      if(err != noErr) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "SSL: SSLSetPeerID() failed: OSStatus %d", err);
        return CURLE_SSL_CONNECT_ERROR;
      }

      result = Curl_ssl_addsessionid(conn, ssl_sessionid, ssl_sessionid_len,
                                     sockindex);
      Curl_ssl_sessionid_unlock(conn);
      if(result) {
        failf(data, "failed to store ssl session");
        return result;
      }
    }