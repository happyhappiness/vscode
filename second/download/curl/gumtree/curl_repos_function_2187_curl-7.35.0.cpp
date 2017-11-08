CURLcode Curl_nss_connect(struct connectdata *conn, int sockindex)
{
  PRErrorCode err = 0;
  PRFileDesc *model = NULL;
  PRBool ssl_no_cache;
  PRBool ssl_cbc_random_iv;
  struct SessionHandle *data = conn->data;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CURLcode curlerr;
  const int *cipher_to_enable;
  PRSocketOptionData sock_opt;
  long time_left;
  PRUint32 timeout;

  SSLVersionRange sslver = {
    SSL_LIBRARY_VERSION_3_0,      /* min */
    SSL_LIBRARY_VERSION_TLS_1_0   /* max */
  };

  if(connssl->state == ssl_connection_complete)
    return CURLE_OK;

  connssl->data = data;

  /* list of all NSS objects we need to destroy in Curl_nss_close() */
  connssl->obj_list = Curl_llist_alloc(nss_destroy_object);
  if(!connssl->obj_list)
    return CURLE_OUT_OF_MEMORY;

  /* FIXME. NSS doesn't support multiple databases open at the same time. */
  PR_Lock(nss_initlock);
  curlerr = nss_init(conn->data);
  if(CURLE_OK != curlerr) {
    PR_Unlock(nss_initlock);
    goto error;
  }

  curlerr = CURLE_SSL_CONNECT_ERROR;

  if(!mod) {
    char *configstring = aprintf("library=%s name=PEM", pem_library);
    if(!configstring) {
      PR_Unlock(nss_initlock);
      goto error;
    }
    mod = SECMOD_LoadUserModule(configstring, NULL, PR_FALSE);
    free(configstring);

    if(!mod || !mod->loaded) {
      if(mod) {
        SECMOD_DestroyModule(mod);
        mod = NULL;
      }
      infof(data, "WARNING: failed to load NSS PEM library %s. Using "
            "OpenSSL PEM certificates will not work.\n", pem_library);
    }
  }

  PK11_SetPasswordFunc(nss_get_password);
  PR_Unlock(nss_initlock);

  model = PR_NewTCPSocket();
  if(!model)
    goto error;
  model = SSL_ImportFD(NULL, model);

  if(SSL_OptionSet(model, SSL_SECURITY, PR_TRUE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_SERVER, PR_FALSE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_CLIENT, PR_TRUE) != SECSuccess)
    goto error;

  /* do not use SSL cache if disabled or we are not going to verify peer */
  ssl_no_cache = (conn->ssl_config.sessionid && data->set.ssl.verifypeer) ?
    PR_FALSE : PR_TRUE;
  if(SSL_OptionSet(model, SSL_NO_CACHE, ssl_no_cache) != SECSuccess)
    goto error;

  /* enable/disable the requested SSL version(s) */
  if(nss_init_sslver(&sslver, data) != CURLE_OK)
    goto error;
  if(SSL_VersionRangeSet(model, &sslver) != SECSuccess)
    goto error;

  ssl_cbc_random_iv = !data->set.ssl_enable_beast;
#ifdef SSL_CBC_RANDOM_IV
  /* unless the user explicitly asks to allow the protocol vulnerability, we
     use the work-around */
  if(SSL_OptionSet(model, SSL_CBC_RANDOM_IV, ssl_cbc_random_iv) != SECSuccess)
    infof(data, "warning: failed to set SSL_CBC_RANDOM_IV = %d\n",
          ssl_cbc_random_iv);
#else
  if(ssl_cbc_random_iv)
    infof(data, "warning: support for SSL_CBC_RANDOM_IV not compiled in\n");
#endif

  /* reset the flag to avoid an infinite loop */
  data->state.ssl_connect_retry = FALSE;

  /* enable all ciphers from enable_ciphers_by_default */
  cipher_to_enable = enable_ciphers_by_default;
  while(SSL_NULL_WITH_NULL_NULL != *cipher_to_enable) {
    if(SSL_CipherPrefSet(model, *cipher_to_enable, PR_TRUE) != SECSuccess) {
      curlerr = CURLE_SSL_CIPHER;
      goto error;
    }
    cipher_to_enable++;
  }

  if(data->set.ssl.cipher_list) {
    if(set_ciphers(data, model, data->set.ssl.cipher_list) != SECSuccess) {
      curlerr = CURLE_SSL_CIPHER;
      goto error;
    }
  }

  if(!data->set.ssl.verifypeer && data->set.ssl.verifyhost)
    infof(data, "warning: ignoring value of ssl.verifyhost\n");

  /* bypass the default SSL_AuthCertificate() hook in case we do not want to
   * verify peer */
  if(SSL_AuthCertificateHook(model, nss_auth_cert_hook, conn) != SECSuccess)
    goto error;

  data->set.ssl.certverifyresult=0; /* not checked yet */
  if(SSL_BadCertHook(model, BadCertHandler, conn) != SECSuccess)
    goto error;

  if(SSL_HandshakeCallback(model, HandshakeCallback, NULL) != SECSuccess)
    goto error;

  if(data->set.ssl.verifypeer) {
    const CURLcode rv = nss_load_ca_certificates(conn, sockindex);
    if(CURLE_OK != rv) {
      curlerr = rv;
      goto error;
    }
  }

  if(data->set.ssl.CRLfile) {
    if(SECSuccess != nss_load_crl(data->set.ssl.CRLfile)) {
      curlerr = CURLE_SSL_CRL_BADFILE;
      goto error;
    }
    infof(data,
          "  CRLfile: %s\n",
          data->set.ssl.CRLfile ? data->set.ssl.CRLfile : "none");
  }

  if(data->set.str[STRING_CERT]) {
    char *nickname = dup_nickname(data, STRING_CERT);
    if(nickname) {
      /* we are not going to use libnsspem.so to read the client cert */
      connssl->obj_clicert = NULL;
    }
    else {
      CURLcode rv = cert_stuff(conn, sockindex, data->set.str[STRING_CERT],
                               data->set.str[STRING_KEY]);
      if(CURLE_OK != rv) {
        /* failf() is already done in cert_stuff() */
        curlerr = rv;
        goto error;
      }
    }

    /* store the nickname for SelectClientCert() called during handshake */
    connssl->client_nickname = nickname;
  }
  else
    connssl->client_nickname = NULL;

  if(SSL_GetClientAuthDataHook(model, SelectClientCert,
                               (void *)connssl) != SECSuccess) {
    curlerr = CURLE_SSL_CERTPROBLEM;
    goto error;
  }

  /* Import our model socket  onto the existing file descriptor */
  connssl->handle = PR_ImportTCPSocket(sockfd);
  connssl->handle = SSL_ImportFD(model, connssl->handle);
  if(!connssl->handle)
    goto error;

  PR_Close(model); /* We don't need this any more */
  model = NULL;

  /* This is the password associated with the cert that we're using */
  if(data->set.str[STRING_KEY_PASSWD]) {
    SSL_SetPKCS11PinArg(connssl->handle, data->set.str[STRING_KEY_PASSWD]);
  }

  /* Force handshake on next I/O */
  SSL_ResetHandshake(connssl->handle, /* asServer */ PR_FALSE);

  SSL_SetURL(connssl->handle, conn->host.name);

  /* check timeout situation */
  time_left = Curl_timeleft(data, NULL, TRUE);
  if(time_left < 0L) {
    failf(data, "timed out before SSL handshake");
    curlerr = CURLE_OPERATION_TIMEDOUT;
    goto error;
  }
  timeout = PR_MillisecondsToInterval((PRUint32) time_left);

  /* Force the handshake now */
  if(SSL_ForceHandshakeWithTimeout(connssl->handle, timeout) != SECSuccess) {
    if(conn->data->set.ssl.certverifyresult == SSL_ERROR_BAD_CERT_DOMAIN)
      curlerr = CURLE_PEER_FAILED_VERIFICATION;
    else if(conn->data->set.ssl.certverifyresult!=0)
      curlerr = CURLE_SSL_CACERT;
    goto error;
  }

  /* switch the SSL socket into non-blocking mode */
  sock_opt.option = PR_SockOpt_Nonblocking;
  sock_opt.value.non_blocking = PR_TRUE;
  if(PR_SetSocketOption(connssl->handle, &sock_opt) != PR_SUCCESS)
    goto error;

  connssl->state = ssl_connection_complete;
  conn->recv[sockindex] = nss_recv;
  conn->send[sockindex] = nss_send;

  display_conn_info(conn, connssl->handle);

  if(data->set.str[STRING_SSL_ISSUERCERT]) {
    SECStatus ret = SECFailure;
    char *nickname = dup_nickname(data, STRING_SSL_ISSUERCERT);
    if(nickname) {
      /* we support only nicknames in case of STRING_SSL_ISSUERCERT for now */
      ret = check_issuer_cert(connssl->handle, nickname);
      free(nickname);
    }

    if(SECFailure == ret) {
      infof(data,"SSL certificate issuer check failed\n");
      curlerr = CURLE_SSL_ISSUER_ERROR;
      goto error;
    }
    else {
      infof(data, "SSL certificate issuer check ok\n");
    }
  }

  return CURLE_OK;

  error:
  /* reset the flag to avoid an infinite loop */
  data->state.ssl_connect_retry = FALSE;

  if(is_nss_error(curlerr)) {
    /* read NSPR error code */
    err = PR_GetError();
    if(is_cc_error(err))
      curlerr = CURLE_SSL_CERTPROBLEM;

    /* print the error number and error string */
    infof(data, "NSS error %d (%s)\n", err, nss_error_to_name(err));

    /* print a human-readable message describing the error if available */
    nss_print_error_message(data, err);
  }

  if(model)
    PR_Close(model);

  /* cleanup on connection failure */
  Curl_llist_destroy(connssl->obj_list, NULL);
  connssl->obj_list = NULL;

  if((sslver.min == SSL_LIBRARY_VERSION_3_0)
      && (sslver.max == SSL_LIBRARY_VERSION_TLS_1_0)
      && isTLSIntoleranceError(err)) {
    /* schedule reconnect through Curl_retry_request() */
    data->state.ssl_connect_retry = TRUE;
    infof(data, "Error in TLS handshake, trying SSLv3...\n");
    return CURLE_OK;
  }

  return curlerr;
}