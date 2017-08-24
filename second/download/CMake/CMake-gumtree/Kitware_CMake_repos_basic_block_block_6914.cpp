f(SSL_SET_OPTION(cert)) {
    char *nickname = dup_nickname(data, SSL_SET_OPTION(cert));
    if(nickname) {
      /* we are not going to use libnsspem.so to read the client cert */
      connssl->obj_clicert = NULL;
    }
    else {
      CURLcode rv = cert_stuff(conn, sockindex, SSL_SET_OPTION(cert),
                               SSL_SET_OPTION(key));
      if(rv) {
        /* failf() is already done in cert_stuff() */
        result = rv;
        goto error;
      }
    }

    /* store the nickname for SelectClientCert() called during handshake */
    connssl->client_nickname = nickname;
  }
  else
    connssl->client_nickname = NULL