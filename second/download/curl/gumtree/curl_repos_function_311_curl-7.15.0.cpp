CURLcode
Curl_ossl_connect(struct connectdata *conn,
                  int sockindex)
{
  CURLcode retcode = CURLE_OK;

  struct SessionHandle *data = conn->data;
  int err;
  long lerr;
  int what;
  char * str;
  SSL_METHOD *req_method;
  void *ssl_sessionid=NULL;
  ASN1_TIME *certdate;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(!ssl_seeded || data->set.ssl.random_file || data->set.ssl.egdsocket) {
    /* Make funny stuff to get random input */
    random_the_seed(data);

    ssl_seeded = TRUE;
  }

  /* check to see if we've been told to use an explicit SSL/TLS version */
  switch(data->set.ssl.version) {
  default:
  case CURL_SSLVERSION_DEFAULT:
    /* we try to figure out version */
    req_method = SSLv23_client_method();
    break;
  case CURL_SSLVERSION_TLSv1:
    req_method = TLSv1_client_method();
    break;
  case CURL_SSLVERSION_SSLv2:
    req_method = SSLv2_client_method();
    break;
  case CURL_SSLVERSION_SSLv3:
    req_method = SSLv3_client_method();
    break;
  }

  connssl->ctx = SSL_CTX_new(req_method);

  if(!connssl->ctx) {
    failf(data, "SSL: couldn't create a context!");
    return CURLE_OUT_OF_MEMORY;
  }

#ifdef SSL_CTRL_SET_MSG_CALLBACK
  if (data->set.fdebug) {
    if (!SSL_CTX_callback_ctrl(connssl->ctx, SSL_CTRL_SET_MSG_CALLBACK,
                               ssl_tls_trace)) {
      failf(data, "SSL: couldn't set callback!");
      return CURLE_SSL_CONNECT_ERROR;
    }

    if (!SSL_CTX_ctrl(connssl->ctx, SSL_CTRL_SET_MSG_CALLBACK_ARG, 0, conn)) {
      failf(data, "SSL: couldn't set callback argument!");
      return CURLE_SSL_CONNECT_ERROR;
    }
  }
#endif

  /* OpenSSL contains code to work-around lots of bugs and flaws in various
     SSL-implementations. SSL_CTX_set_options() is used to enabled those
     work-arounds. The man page for this option states that SSL_OP_ALL enables
     ll the work-arounds and that "It is usually safe to use SSL_OP_ALL to
     enable the bug workaround options if compatibility with somewhat broken
     implementations is desired."

  */
  SSL_CTX_set_options(connssl->ctx, SSL_OP_ALL);

#if 0
  /*
   * Not sure it's needed to tell SSL_connect() that socket is
   * non-blocking. It doesn't seem to care, but just return with
   * SSL_ERROR_WANT_x.
   */
  if (data->state.used_interface == Curl_if_multi)
    SSL_CTX_ctrl(connssl->ctx, BIO_C_SET_NBIO, 1, NULL);
#endif

  if(data->set.cert) {
    if(!cert_stuff(conn,
                   connssl->ctx,
                   data->set.cert,
                   data->set.cert_type,
                   data->set.key,
                   data->set.key_type)) {
      /* failf() is already done in cert_stuff() */
      return CURLE_SSL_CERTPROBLEM;
    }
  }

  if(data->set.ssl.cipher_list) {
    if(!SSL_CTX_set_cipher_list(connssl->ctx,
                                data->set.ssl.cipher_list)) {
      failf(data, "failed setting cipher list");
      return CURLE_SSL_CIPHER;
    }
  }

  if (data->set.ssl.CAfile || data->set.ssl.CApath) {
    /* tell SSL where to find CA certificates that are used to verify
       the servers certificate. */
    if (!SSL_CTX_load_verify_locations(connssl->ctx, data->set.ssl.CAfile,
                                       data->set.ssl.CApath)) {
      if (data->set.ssl.verifypeer) {
        /* Fail if we insist on successfully verifying the server. */
        failf(data,"error setting certificate verify locations:\n"
              "  CAfile: %s\n  CApath: %s\n",
              data->set.ssl.CAfile ? data->set.ssl.CAfile : "none",
              data->set.ssl.CApath ? data->set.ssl.CApath : "none");
        return CURLE_SSL_CACERT;
      }
      else {
        /* Just continue with a warning if no strict  certificate verification
           is required. */
        infof(data, "error setting certificate verify locations,"
              " continuing anyway:\n");
      }
    }
    else {
      /* Everything is fine. */
      infof(data, "successfully set certificate verify locations:\n");
    }
    infof(data,
          "  CAfile: %s\n"
          "  CApath: %s\n",
          data->set.ssl.CAfile ? data->set.ssl.CAfile : "none",
          data->set.ssl.CApath ? data->set.ssl.CApath : "none");
  }
  /* SSL always tries to verify the peer, this only says whether it should
   * fail to connect if the verification fails, or if it should continue
   * anyway. In the latter case the result of the verification is checked with
   * SSL_get_verify_result() below. */
  SSL_CTX_set_verify(connssl->ctx,
                     data->set.ssl.verifypeer?SSL_VERIFY_PEER:SSL_VERIFY_NONE,
                     cert_verify_callback);

  /* give application a chance to interfere with SSL set up. */
  if(data->set.ssl.fsslctx) {
    retcode = (*data->set.ssl.fsslctx)(data, connssl->ctx,
                                       data->set.ssl.fsslctxp);
    if(retcode) {
      failf(data,"error signaled by ssl ctx callback");
      return retcode;
    }
  }

  /* Lets make an SSL structure */
  connssl->handle = SSL_new(connssl->ctx);
  if (!connssl->handle) {
    failf(data, "SSL: couldn't create a context (handle)!");
    return CURLE_OUT_OF_MEMORY;
  }
  SSL_set_connect_state(connssl->handle);

  connssl->server_cert = 0x0;

  /* Check if there's a cached ID we can/should use here! */
  if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL)) {
    /* we got a session id, use it! */
    if (!SSL_set_session(connssl->handle, ssl_sessionid)) {
      failf(data, "SSL: SSL_set_session failed: %s",
            ERR_error_string(ERR_get_error(),NULL));
      return CURLE_SSL_CONNECT_ERROR;
    }
    /* Informational message */
    infof (data, "SSL re-using session ID\n");
  }

  /* pass the raw socket into the SSL layers */
  if (!SSL_set_fd(connssl->handle, sockfd)) {
     failf(data, "SSL: SSL_set_fd failed: %s",
           ERR_error_string(ERR_get_error(),NULL));
     return CURLE_SSL_CONNECT_ERROR;
  }

  while(1) {
    int writefd;
    int readfd;
    long timeout_ms;
    long has_passed;

    /* Find out if any timeout is set. If not, use 300 seconds.
       Otherwise, figure out the most strict timeout of the two possible one
       and then how much time that has elapsed to know how much time we
       allow for the connect call */
    if(data->set.timeout || data->set.connecttimeout) {

      /* get the most strict timeout of the ones converted to milliseconds */
      if(data->set.timeout &&
         (data->set.timeout>data->set.connecttimeout))
        timeout_ms = data->set.timeout*1000;
      else
        timeout_ms = data->set.connecttimeout*1000;
    }
    else
      /* no particular time-out has been set */
      timeout_ms= DEFAULT_CONNECT_TIMEOUT;

    /* Evaluate in milliseconds how much time that has passed */
    has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);

    /* subtract the passed time */
    timeout_ms -= has_passed;

    if(timeout_ms < 0) {
      /* a precaution, no need to continue if time already is up */
      failf(data, "SSL connection timeout");
      return CURLE_OPERATION_TIMEOUTED;
    }

    readfd = CURL_SOCKET_BAD;
    writefd = CURL_SOCKET_BAD;

    err = SSL_connect(connssl->handle);

    /* 1  is fine
       0  is "not successful but was shut down controlled"
       <0 is "handshake was not successful, because a fatal error occurred" */
    if(1 != err) {
      int detail = SSL_get_error(connssl->handle, err);

      if(SSL_ERROR_WANT_READ == detail)
        readfd = sockfd;
      else if(SSL_ERROR_WANT_WRITE == detail)
        writefd = sockfd;
      else {
        /* untreated error */
        unsigned long errdetail;
        char error_buffer[120]; /* OpenSSL documents that this must be at least
                                   120 bytes long. */
        CURLcode rc;
        const char *cert_problem = NULL;

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
        if (CURLE_SSL_CONNECT_ERROR == rc && errdetail == 0) {
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
    else
      /* we have been connected fine, get out of the connect loop */
      break;

    while(1) {
      what = Curl_select(readfd, writefd, (int)timeout_ms);
      if(what > 0)
        /* reabable or writable, go loop in the outer loop */
        break;
      else if(0 == what) {
        /* timeout */
        failf(data, "SSL connection timeout");
        return CURLE_OPERATION_TIMEDOUT;
      }
      else {
        /* anything that gets here is fatally bad */
        failf(data, "select on SSL socket, errno: %d", Curl_ourerrno());
        return CURLE_SSL_CONNECT_ERROR;
      }
    } /* while()-loop for the select() */
  } /* while()-loop for the SSL_connect() */

  /* Informational message */
  infof (data, "SSL connection using %s\n",
         SSL_get_cipher(connssl->handle));

  if(!ssl_sessionid) {
    /* Since this is not a cached session ID, then we want to stach this one
       in the cache! */
    SSL_SESSION *ssl_sessionid;
#ifdef HAVE_SSL_GET1_SESSION
    ssl_sessionid = SSL_get1_session(connssl->handle);

    /* SSL_get1_session() will increment the reference
       count and the session will stay in memory until explicitly freed with
       SSL_SESSION_free(3), regardless of its state.
       This function was introduced in openssl 0.9.5a. */
#else
    ssl_sessionid = SSL_get_session(connssl->handle);

    /* if SSL_get1_session() is unavailable, use SSL_get_session().
       This is an inferior option because the session can be flushed
       at any time by openssl. It is included only so curl compiles
       under versions of openssl < 0.9.5a.

       WARNING: How curl behaves if it's session is flushed is
       untested.
    */
#endif
    retcode = Curl_ssl_addsessionid(conn, ssl_sessionid,
                                    0 /* unknown size */);
    if(retcode) {
      failf(data, "failed to store ssl session");
      return retcode;
    }
  }


  /* Get server's certificate (note: beware of dynamic allocation) - opt */
  /* major serious hack alert -- we should check certificates
   * to authenticate the server; otherwise we risk man-in-the-middle
   * attack
   */

  connssl->server_cert = SSL_get_peer_certificate(connssl->handle);
  if(!connssl->server_cert) {
    failf(data, "SSL: couldn't get peer certificate!");
    return CURLE_SSL_PEER_CERTIFICATE;
  }
  infof (data, "Server certificate:\n");

  str = X509_NAME_oneline(X509_get_subject_name(connssl->server_cert),
                          NULL, 0);
  if(!str) {
    failf(data, "SSL: couldn't get X509-subject!");
    X509_free(connssl->server_cert);
    connssl->server_cert = NULL;
    return CURLE_SSL_CONNECT_ERROR;
  }
  infof(data, "\t subject: %s\n", str);
  CRYPTO_free(str);

  certdate = X509_get_notBefore(connssl->server_cert);
  Curl_ASN1_UTCTIME_output(conn, "\t start date: ", certdate);

  certdate = X509_get_notAfter(connssl->server_cert);
  Curl_ASN1_UTCTIME_output(conn, "\t expire date: ", certdate);

  if(data->set.ssl.verifyhost) {
    retcode = verifyhost(conn, connssl->server_cert);
    if(retcode) {
      X509_free(connssl->server_cert);
      connssl->server_cert = NULL;
      return retcode;
    }
  }

  str = X509_NAME_oneline(X509_get_issuer_name(connssl->server_cert),
                          NULL, 0);
  if(!str) {
    failf(data, "SSL: couldn't get X509-issuer name!");
    retcode = CURLE_SSL_CONNECT_ERROR;
  }
  else {
    infof(data, "\t issuer: %s\n", str);
    CRYPTO_free(str);

    /* We could do all sorts of certificate verification stuff here before
       deallocating the certificate. */

    lerr = data->set.ssl.certverifyresult=
      SSL_get_verify_result(connssl->handle);
    if(data->set.ssl.certverifyresult != X509_V_OK) {
      if(data->set.ssl.verifypeer) {
        /* We probably never reach this, because SSL_connect() will fail
           and we return earlyer if verifypeer is set? */
        failf(data, "SSL certificate verify result: %s (%ld)",
              X509_verify_cert_error_string(lerr), lerr);
        retcode = CURLE_SSL_PEER_CERTIFICATE;
      }
      else
        infof(data, "SSL certificate verify result: %s (%ld),"
              " continuing anyway.\n",
              X509_verify_cert_error_string(err), lerr);
    }
    else
      infof(data, "SSL certificate verify ok.\n");
  }

  X509_free(connssl->server_cert);
  connssl->server_cert = NULL;
  return retcode;
}