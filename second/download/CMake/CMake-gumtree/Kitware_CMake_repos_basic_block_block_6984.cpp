{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data* connssl = &conn->ssl[sockindex];
  const char *capath = SSL_CONN_CONFIG(CApath);
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
  const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
  int ret = -1;
  char errorbuf[128];
  errorbuf[0]=0;

  /* PolarSSL only supports SSLv3 and TLSv1 */
  if(SSL_CONN_CONFIG(version) == CURL_SSLVERSION_SSLv2) {
    failf(data, "PolarSSL does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef THREADING_SUPPORT
  entropy_init_mutex(&entropy);

  if((ret = ctr_drbg_init(&connssl->ctr_drbg, entropy_func_mutex, &entropy,
                          NULL, 0)) != 0) {
    error_strerror(ret, errorbuf, sizeof(errorbuf));
    failf(data, "Failed - PolarSSL: ctr_drbg_init returned (-0x%04X) %s\n",
          -ret, errorbuf);
  }
#else
  entropy_init(&connssl->entropy);

  if((ret = ctr_drbg_init(&connssl->ctr_drbg, entropy_func, &connssl->entropy,
                          NULL, 0)) != 0) {
    error_strerror(ret, errorbuf, sizeof(errorbuf));
    failf(data, "Failed - PolarSSL: ctr_drbg_init returned (-0x%04X) %s\n",
          -ret, errorbuf);
  }
#endif /* THREADING_SUPPORT */

  /* Load the trusted CA */
  memset(&connssl->cacert, 0, sizeof(x509_crt));

  if(SSL_CONN_CONFIG(CAfile)) {
    ret = x509_crt_parse_file(&connssl->cacert,
                              SSL_CONN_CONFIG(CAfile));

    if(ret<0) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading ca cert file %s - PolarSSL: (-0x%04X) %s",
            SSL_CONN_CONFIG(CAfile), -ret, errorbuf);

      if(SSL_CONN_CONFIG(verifypeer))
        return CURLE_SSL_CACERT_BADFILE;
    }
  }

  if(capath) {
    ret = x509_crt_parse_path(&connssl->cacert, capath);

    if(ret<0) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading ca cert path %s - PolarSSL: (-0x%04X) %s",
            capath, -ret, errorbuf);

      if(SSL_CONN_CONFIG(verifypeer))
        return CURLE_SSL_CACERT_BADFILE;
    }
  }

  /* Load the client certificate */
  memset(&connssl->clicert, 0, sizeof(x509_crt));

  if(SSL_SET_OPTION(cert)) {
    ret = x509_crt_parse_file(&connssl->clicert,
                              SSL_SET_OPTION(cert));

    if(ret) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading client cert file %s - PolarSSL: (-0x%04X) %s",
            SSL_SET_OPTION(cert), -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load the client private key */
  if(SSL_SET_OPTION(key)) {
    pk_context pk;
    pk_init(&pk);
    ret = pk_parse_keyfile(&pk, SSL_SET_OPTION(key),
                           SSL_SET_OPTION(key_passwd));
    if(ret == 0 && !pk_can_do(&pk, POLARSSL_PK_RSA))
      ret = POLARSSL_ERR_PK_TYPE_MISMATCH;
    if(ret == 0)
      rsa_copy(&connssl->rsa, pk_rsa(pk));
    else
      rsa_free(&connssl->rsa);
    pk_free(&pk);

    if(ret) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading private key %s - PolarSSL: (-0x%04X) %s",
            SSL_SET_OPTION(key), -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load the CRL */
  memset(&connssl->crl, 0, sizeof(x509_crl));

  if(SSL_SET_OPTION(CRLfile)) {
    ret = x509_crl_parse_file(&connssl->crl,
                              SSL_SET_OPTION(CRLfile));

    if(ret) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading CRL file %s - PolarSSL: (-0x%04X) %s",
            SSL_SET_OPTION(CRLfile), -ret, errorbuf);

      return CURLE_SSL_CRL_BADFILE;
    }
  }

  infof(data, "PolarSSL: Connecting to %s:%d\n", hostname, port);

  if(ssl_init(&connssl->ssl)) {
    failf(data, "PolarSSL: ssl_init failed");
    return CURLE_SSL_CONNECT_ERROR;
  }

  switch(SSL_CONN_CONFIG(version)) {
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    ssl_set_min_version(&connssl->ssl, SSL_MAJOR_VERSION_3,
                        SSL_MINOR_VERSION_1);
    break;
  case CURL_SSLVERSION_SSLv3:
    ssl_set_min_version(&connssl->ssl, SSL_MAJOR_VERSION_3,
                        SSL_MINOR_VERSION_0);
    ssl_set_max_version(&connssl->ssl, SSL_MAJOR_VERSION_3,
                        SSL_MINOR_VERSION_0);
    infof(data, "PolarSSL: Forced min. SSL Version to be SSLv3\n");
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

  ssl_set_endpoint(&connssl->ssl, SSL_IS_CLIENT);
  ssl_set_authmode(&connssl->ssl, SSL_VERIFY_OPTIONAL);

  ssl_set_rng(&connssl->ssl, ctr_drbg_random,
              &connssl->ctr_drbg);
  ssl_set_bio(&connssl->ssl,
              net_recv, &conn->sock[sockindex],
              net_send, &conn->sock[sockindex]);

  ssl_set_ciphersuites(&connssl->ssl, ssl_list_ciphersuites());

  /* Check if there's a cached ID we can/should use here! */
  if(SSL_SET_OPTION(primary.sessionid)) {
    void *old_session = NULL;

    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, &old_session, NULL, sockindex)) {
      ret = ssl_set_session(&connssl->ssl, old_session);
      if(ret) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "ssl_set_session returned -0x%x", -ret);
        return CURLE_SSL_CONNECT_ERROR;
      }
      infof(data, "PolarSSL re-using session\n");
    }
    Curl_ssl_sessionid_unlock(conn);
  }

  ssl_set_ca_chain(&connssl->ssl,
                   &connssl->cacert,
                   &connssl->crl,
                   hostname);

  ssl_set_own_cert_rsa(&connssl->ssl,
                       &connssl->clicert, &connssl->rsa);

  if(ssl_set_hostname(&connssl->ssl, hostname)) {
    /* ssl_set_hostname() sets the name to use in CN/SAN checks *and* the name
       to set in the SNI extension. So even if curl connects to a host
       specified as an IP address, this function must be used. */
    failf(data, "couldn't set hostname in PolarSSL");
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef HAS_ALPN
  if(conn->bits.tls_enable_alpn) {
    static const char *protocols[3];
    int cur = 0;

#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2) {
      protocols[cur++] = NGHTTP2_PROTO_VERSION_ID;
      infof(data, "ALPN, offering %s\n", NGHTTP2_PROTO_VERSION_ID);
    }
#endif

    protocols[cur++] = ALPN_HTTP_1_1;
    infof(data, "ALPN, offering %s\n", ALPN_HTTP_1_1);

    protocols[cur] = NULL;

    ssl_set_alpn_protocols(&connssl->ssl, protocols);
  }
#endif

#ifdef POLARSSL_DEBUG
  ssl_set_dbg(&connssl->ssl, polarssl_debug, data);
#endif

  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}