static CURLcode
mbed_connect_step1(struct connectdata *conn,
                   int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data* connssl = &conn->ssl[sockindex];
  const char * const ssl_cafile = SSL_CONN_CONFIG(CAfile);
  const bool verifypeer = SSL_CONN_CONFIG(verifypeer);
  const char * const ssl_capath = SSL_CONN_CONFIG(CApath);
  char * const ssl_cert = SSL_SET_OPTION(cert);
  const char * const ssl_crlfile = SSL_SET_OPTION(CRLfile);
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
  const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
  int ret = -1;
  char errorbuf[128];
  errorbuf[0] = 0;

  /* mbedTLS only supports SSLv3 and TLSv1 */
  if(SSL_CONN_CONFIG(version) == CURL_SSLVERSION_SSLv2) {
    failf(data, "mbedTLS does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef THREADING_SUPPORT
  entropy_init_mutex(&ts_entropy);
  mbedtls_ctr_drbg_init(&BACKEND->ctr_drbg);

  ret = mbedtls_ctr_drbg_seed(&BACKEND->ctr_drbg, entropy_func_mutex,
                              &ts_entropy, NULL, 0);
  if(ret) {
#ifdef MBEDTLS_ERROR_C
    mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
    failf(data, "Failed - mbedTLS: ctr_drbg_init returned (-0x%04X) %s\n",
          -ret, errorbuf);
  }
#else
  mbedtls_entropy_init(&BACKEND->entropy);
  mbedtls_ctr_drbg_init(&BACKEND->ctr_drbg);

  ret = mbedtls_ctr_drbg_seed(&BACKEND->ctr_drbg, mbedtls_entropy_func,
                              &BACKEND->entropy, NULL, 0);
  if(ret) {
#ifdef MBEDTLS_ERROR_C
    mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
    failf(data, "Failed - mbedTLS: ctr_drbg_init returned (-0x%04X) %s\n",
          -ret, errorbuf);
  }
#endif /* THREADING_SUPPORT */

  /* Load the trusted CA */
  mbedtls_x509_crt_init(&BACKEND->cacert);

  if(ssl_cafile) {
    ret = mbedtls_x509_crt_parse_file(&BACKEND->cacert, ssl_cafile);

    if(ret<0) {
#ifdef MBEDTLS_ERROR_C
      mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
      failf(data, "Error reading ca cert file %s - mbedTLS: (-0x%04X) %s",
            ssl_cafile, -ret, errorbuf);

      if(verifypeer)
        return CURLE_SSL_CACERT_BADFILE;
    }
  }

  if(ssl_capath) {
    ret = mbedtls_x509_crt_parse_path(&BACKEND->cacert, ssl_capath);

    if(ret<0) {
#ifdef MBEDTLS_ERROR_C
      mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
      failf(data, "Error reading ca cert path %s - mbedTLS: (-0x%04X) %s",
            ssl_capath, -ret, errorbuf);

      if(verifypeer)
        return CURLE_SSL_CACERT_BADFILE;
    }
  }

  /* Load the client certificate */
  mbedtls_x509_crt_init(&BACKEND->clicert);

  if(ssl_cert) {
    ret = mbedtls_x509_crt_parse_file(&BACKEND->clicert, ssl_cert);

    if(ret) {
#ifdef MBEDTLS_ERROR_C
      mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
      failf(data, "Error reading client cert file %s - mbedTLS: (-0x%04X) %s",
            ssl_cert, -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load the client private key */
  mbedtls_pk_init(&BACKEND->pk);

  if(SSL_SET_OPTION(key)) {
    ret = mbedtls_pk_parse_keyfile(&BACKEND->pk, SSL_SET_OPTION(key),
                                   SSL_SET_OPTION(key_passwd));
    if(ret == 0 && !mbedtls_pk_can_do(&BACKEND->pk, MBEDTLS_PK_RSA))
      ret = MBEDTLS_ERR_PK_TYPE_MISMATCH;

    if(ret) {
#ifdef MBEDTLS_ERROR_C
      mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
      failf(data, "Error reading private key %s - mbedTLS: (-0x%04X) %s",
            SSL_SET_OPTION(key), -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load the CRL */
  mbedtls_x509_crl_init(&BACKEND->crl);

  if(ssl_crlfile) {
    ret = mbedtls_x509_crl_parse_file(&BACKEND->crl, ssl_crlfile);

    if(ret) {
#ifdef MBEDTLS_ERROR_C
      mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
      failf(data, "Error reading CRL file %s - mbedTLS: (-0x%04X) %s",
            ssl_crlfile, -ret, errorbuf);

      return CURLE_SSL_CRL_BADFILE;
    }
  }

  infof(data, "mbedTLS: Connecting to %s:%d\n", hostname, port);

  mbedtls_ssl_config_init(&BACKEND->config);

  mbedtls_ssl_init(&BACKEND->ssl);
  if(mbedtls_ssl_setup(&BACKEND->ssl, &BACKEND->config)) {
    failf(data, "mbedTLS: ssl_init failed");
    return CURLE_SSL_CONNECT_ERROR;
  }
  ret = mbedtls_ssl_config_defaults(&BACKEND->config,
                                    MBEDTLS_SSL_IS_CLIENT,
                                    MBEDTLS_SSL_TRANSPORT_STREAM,
                                    MBEDTLS_SSL_PRESET_DEFAULT);
  if(ret) {
    failf(data, "mbedTLS: ssl_config failed");
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* new profile with RSA min key len = 1024 ... */
  mbedtls_ssl_conf_cert_profile(&BACKEND->config,
                                &mbedtls_x509_crt_profile_fr);

  switch(SSL_CONN_CONFIG(version)) {
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    mbedtls_ssl_conf_min_version(&BACKEND->config, MBEDTLS_SSL_MAJOR_VERSION_3,
                                 MBEDTLS_SSL_MINOR_VERSION_1);
    infof(data, "mbedTLS: Set min SSL version to TLS 1.0\n");
    break;
  case CURL_SSLVERSION_SSLv3:
    mbedtls_ssl_conf_min_version(&BACKEND->config, MBEDTLS_SSL_MAJOR_VERSION_3,
                                 MBEDTLS_SSL_MINOR_VERSION_0);
    mbedtls_ssl_conf_max_version(&BACKEND->config, MBEDTLS_SSL_MAJOR_VERSION_3,
                                 MBEDTLS_SSL_MINOR_VERSION_0);
    infof(data, "mbedTLS: Set SSL version to SSLv3\n");
    break;
  case CURL_SSLVERSION_TLSv1_0:
  case CURL_SSLVERSION_TLSv1_1:
  case CURL_SSLVERSION_TLSv1_2:
  case CURL_SSLVERSION_TLSv1_3:
    {
      CURLcode result = set_ssl_version_min_max(conn, sockindex);
      if(result != CURLE_OK)
        return result;
      break;
    }
  default:
    failf(data, "Unrecognized parameter passed via CURLOPT_SSLVERSION");
    return CURLE_SSL_CONNECT_ERROR;
  }

  mbedtls_ssl_conf_authmode(&BACKEND->config, MBEDTLS_SSL_VERIFY_OPTIONAL);

  mbedtls_ssl_conf_rng(&BACKEND->config, mbedtls_ctr_drbg_random,
                       &BACKEND->ctr_drbg);
  mbedtls_ssl_set_bio(&BACKEND->ssl, &conn->sock[sockindex],
                      mbedtls_net_send,
                      mbedtls_net_recv,
                      NULL /*  rev_timeout() */);

  mbedtls_ssl_conf_ciphersuites(&BACKEND->config,
                                mbedtls_ssl_list_ciphersuites());

#if defined(MBEDTLS_SSL_RENEGOTIATION)
  mbedtls_ssl_conf_renegotiation(&BACKEND->config,
                                 MBEDTLS_SSL_RENEGOTIATION_ENABLED);
#endif

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
  mbedtls_ssl_conf_session_tickets(&BACKEND->config,
                                   MBEDTLS_SSL_SESSION_TICKETS_DISABLED);
#endif

  /* Check if there's a cached ID we can/should use here! */
  if(SSL_SET_OPTION(primary.sessionid)) {
    void *old_session = NULL;

    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, &old_session, NULL, sockindex)) {
      ret = mbedtls_ssl_set_session(&BACKEND->ssl, old_session);
      if(ret) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "mbedtls_ssl_set_session returned -0x%x", -ret);
        return CURLE_SSL_CONNECT_ERROR;
      }
      infof(data, "mbedTLS re-using session\n");
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  mbedtls_ssl_conf_ca_chain(&BACKEND->config,
                            &BACKEND->cacert,
                            &BACKEND->crl);

  if(SSL_SET_OPTION(key)) {
    mbedtls_ssl_conf_own_cert(&BACKEND->config,
                              &BACKEND->clicert, &BACKEND->pk);
  }
  if(mbedtls_ssl_set_hostname(&BACKEND->ssl, hostname)) {
    /* mbedtls_ssl_set_hostname() sets the name to use in CN/SAN checks *and*
       the name to set in the SNI extension. So even if curl connects to a
       host specified as an IP address, this function must be used. */
    failf(data, "couldn't set hostname in mbedTLS");
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef HAS_ALPN
  if(conn->bits.tls_enable_alpn) {
    const char **p = &BACKEND->protocols[0];
#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2)
      *p++ = NGHTTP2_PROTO_VERSION_ID;
#endif
    *p++ = ALPN_HTTP_1_1;
    *p = NULL;
    /* this function doesn't clone the protocols array, which is why we need
       to keep it around */
    if(mbedtls_ssl_conf_alpn_protocols(&BACKEND->config,
                                       &BACKEND->protocols[0])) {
      failf(data, "Failed setting ALPN protocols");
      return CURLE_SSL_CONNECT_ERROR;
    }
    for(p = &BACKEND->protocols[0]; *p; ++p)
      infof(data, "ALPN, offering %s\n", *p);
  }
#endif

#ifdef MBEDTLS_DEBUG
  /* In order to make that work in mbedtls MBEDTLS_DEBUG_C must be defined. */
  mbedtls_ssl_conf_dbg(&BACKEND->config, mbed_debug, data);
  /* - 0 No debug
   * - 1 Error
   * - 2 State change
   * - 3 Informational
   * - 4 Verbose
   */
  mbedtls_debug_set_threshold(4);
#endif

  /* give application a chance to interfere with mbedTLS set up. */
  if(data->set.ssl.fsslctx) {
    ret = (*data->set.ssl.fsslctx)(data, &BACKEND->config,
                                   data->set.ssl.fsslctxp);
    if(ret) {
      failf(data, "error signaled by ssl ctx callback");
      return ret;
    }
  }

  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}