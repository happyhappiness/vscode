static CURLcode
ossl_connect_step2(struct connectdata *conn,
                   int sockindex, long *timeout_ms)
{
  struct SessionHandle *data = conn->data;
  int err;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  DEBUGASSERT(ssl_connect_2 == connssl->connecting_state
             || ssl_connect_2_reading == connssl->connecting_state
             || ssl_connect_2_writing == connssl->connecting_state);

  /* Find out how much more time we're allowed */
  *timeout_ms = Curl_timeleft(conn, NULL, TRUE);

  if(*timeout_ms < 0) {
    /* no need to continue if time already is up */
    failf(data, "SSL connection timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }

  err = SSL_connect(connssl->handle);

  /* 1  is fine
     0  is "not successful but was shut down controlled"
     <0 is "handshake was not successful, because a fatal error occurred" */
  if(1 != err) {
    int detail = SSL_get_error(connssl->handle, err);

    if(SSL_ERROR_WANT_READ == detail) {
      connssl->connecting_state = ssl_connect_2_reading;
      return CURLE_OK;
    }
    else if(SSL_ERROR_WANT_WRITE == detail) {
      connssl->connecting_state = ssl_connect_2_writing;
      return CURLE_OK;
    }
    else {
      /* untreated error */
      unsigned long errdetail;
      char error_buffer[256]; /* OpenSSL documents that this must be at least
                                 256 bytes long. */
      CURLcode rc;
      const char *cert_problem = NULL;

      connssl->connecting_state = ssl_connect_2; /* the connection failed,
                                                    we're not waiting for
                                                    anything else. */

      errdetail = ERR_get_error(); /* Gets the earliest error code from the
                                      thread's error queue and removes the
                                      entry. */

      switch(errdetail) {
      case 0x1407E086:
        /* 1407E086:
           SSL routines:
           SSL2_SET_CERTIFICATE:
           certificate verify failed */
        /* fall-through */
      case 0x14090086:
        /* 14090086:
           SSL routines:
           SSL3_GET_SERVER_CERTIFICATE:
           certificate verify failed */
        cert_problem = "SSL certificate problem, verify that the CA cert is"
          " OK. Details:\n";
        rc = CURLE_SSL_CACERT;
        break;
      default:
        rc = CURLE_SSL_CONNECT_ERROR;
        break;
      }

      /* detail is already set to the SSL error above */

      /* If we e.g. use SSLv2 request-method and the server doesn't like us
       * (RST connection etc.), OpenSSL gives no explanation whatsoever and
       * the SO_ERROR is also lost.
       */
      if(CURLE_SSL_CONNECT_ERROR == rc && errdetail == 0) {
        failf(data, "Unknown SSL protocol error in connection to %s:%d ",
              conn->host.name, conn->port);
        return rc;
      }
      /* Could be a CERT problem */

      SSL_strerror(errdetail, error_buffer, sizeof(error_buffer));
      failf(data, "%s%s", cert_problem ? cert_problem : "", error_buffer);
      return rc;
    }
  }
  else {
    /* we have been connected fine, we're not waiting for anything else. */
    connssl->connecting_state = ssl_connect_3;

    /* Informational message */
    infof (data, "SSL connection using %s\n",
           SSL_get_cipher(connssl->handle));

    return CURLE_OK;
  }
}