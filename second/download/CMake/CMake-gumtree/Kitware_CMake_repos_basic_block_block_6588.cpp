{
    /* check allowed time left */
    timeout_ms = Curl_timeleft(data, NULL, duringconnect);

    if(timeout_ms < 0) {
      /* no need to continue if time already is up */
      failf(data, "SSL connection timeout");
      return CURLE_OPERATION_TIMEDOUT;
    }

    /* if ssl is expecting something, check if it's available. */
    if(connssl->connecting_state == ssl_connect_2_reading
       || connssl->connecting_state == ssl_connect_2_writing) {

      curl_socket_t writefd = ssl_connect_2_writing==
        connssl->connecting_state?sockfd:CURL_SOCKET_BAD;
      curl_socket_t readfd = ssl_connect_2_reading==
        connssl->connecting_state?sockfd:CURL_SOCKET_BAD;

      what = Curl_socket_check(readfd, CURL_SOCKET_BAD, writefd,
                               nonblocking?0:
                               timeout_ms?timeout_ms:1000);
      if(what < 0) {
        /* fatal error */
        failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
        return CURLE_SSL_CONNECT_ERROR;
      }
      else if(0 == what) {
        if(nonblocking)
          return CURLE_OK;
        else if(timeout_ms) {
          /* timeout */
          failf(data, "SSL connection timeout at %ld", (long)timeout_ms);
          return CURLE_OPERATION_TIMEDOUT;
        }
      }
      /* socket is readable or writable */
    }

    rc = gnutls_handshake(session);

    if((rc == GNUTLS_E_AGAIN) || (rc == GNUTLS_E_INTERRUPTED)) {
      connssl->connecting_state =
        gnutls_record_get_direction(session)?
        ssl_connect_2_writing:ssl_connect_2_reading;
      continue;
    }
    else if((rc < 0) && !gnutls_error_is_fatal(rc)) {
      const char *strerr = NULL;

      if(rc == GNUTLS_E_WARNING_ALERT_RECEIVED) {
        int alert = gnutls_alert_get(session);
        strerr = gnutls_alert_get_name(alert);
      }

      if(strerr == NULL)
        strerr = gnutls_strerror(rc);

      infof(data, "gnutls_handshake() warning: %s\n", strerr);
      continue;
    }
    else if(rc < 0) {
      const char *strerr = NULL;

      if(rc == GNUTLS_E_FATAL_ALERT_RECEIVED) {
        int alert = gnutls_alert_get(session);
        strerr = gnutls_alert_get_name(alert);
      }

      if(strerr == NULL)
        strerr = gnutls_strerror(rc);

      failf(data, "gnutls_handshake() failed: %s", strerr);
      return CURLE_SSL_CONNECT_ERROR;
    }

    /* Reset our connect state machine */
    connssl->connecting_state = ssl_connect_1;
    return CURLE_OK;
  }