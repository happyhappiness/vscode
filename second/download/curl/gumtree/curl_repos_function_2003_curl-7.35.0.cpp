static CURLcode
ossl_connect_step2(struct connectdata *conn, int sockindex)
{
  struct SessionHandle *data = conn->data;
  int err;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  DEBUGASSERT(ssl_connect_2 == connssl->connecting_state
             || ssl_connect_2_reading == connssl->connecting_state
             || ssl_connect_2_writing == connssl->connecting_state);

  ERR_clear_error();

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
      long lerr;

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
        rc = CURLE_SSL_CACERT;

        lerr = SSL_get_verify_result(connssl->handle);
        if(lerr != X509_V_OK) {
          snprintf(error_buffer, sizeof(error_buffer),
                   "SSL certificate problem: %s",
                   X509_verify_cert_error_string(lerr));
        }
        else
          cert_problem = "SSL certificate problem, verify that the CA cert is"
            " OK.";

        break;
      default:
        rc = CURLE_SSL_CONNECT_ERROR;
        SSL_strerror(errdetail, error_buffer, sizeof(error_buffer));
        break;
      }

      /* detail is already set to the SSL error above */

      /* If we e.g. use SSLv2 request-method and the server doesn't like us
       * (RST connection etc.), OpenSSL gives no explanation whatsoever and
       * the SO_ERROR is also lost.
       */
      if(CURLE_SSL_CONNECT_ERROR == rc && errdetail == 0) {
        failf(data, "Unknown SSL protocol error in connection to %s:%ld ",
              conn->host.name, conn->remote_port);
        return rc;
      }
      /* Could be a CERT problem */

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