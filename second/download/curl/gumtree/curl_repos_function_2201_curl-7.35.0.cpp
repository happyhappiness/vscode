static CURLcode
polarssl_connect_step1(struct connectdata *conn,
                     int sockindex)
{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data* connssl = &conn->ssl[sockindex];

  bool sni = TRUE; /* default is SNI enabled */
  int ret = -1;
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif
  void *old_session = NULL;
  size_t old_session_size = 0;

  char errorbuf[128];
  memset(errorbuf, 0, sizeof(errorbuf));


  /* PolarSSL only supports SSLv3 and TLSv1 */
  if(data->set.ssl.version == CURL_SSLVERSION_SSLv2) {
    failf(data, "PolarSSL does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }
  else if(data->set.ssl.version == CURL_SSLVERSION_SSLv3)
    sni = FALSE; /* SSLv3 has no SNI */

#if POLARSSL_VERSION_NUMBER<0x01010000
  havege_init(&connssl->hs);
#else
#ifdef THREADING_SUPPORT
  entropy_init_mutex(&entropy);

  if((ret = ctr_drbg_init(&connssl->ctr_drbg, entropy_func_mutex, &entropy,
                               connssl->ssn.id, connssl->ssn.length)) != 0) {
#ifdef POLARSSL_ERROR_C
     error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
     failf(data, "Failed - PolarSSL: ctr_drbg_init returned (-0x%04X) %s\n",
                                                            -ret, errorbuf);
  }
#else
  entropy_init(&connssl->entropy);

  if((ret = ctr_drbg_init(&connssl->ctr_drbg, entropy_func, &connssl->entropy,
                                connssl->ssn.id, connssl->ssn.length)) != 0) {
#ifdef POLARSSL_ERROR_C
     error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
     failf(data, "Failed - PolarSSL: ctr_drbg_init returned (-0x%04X) %s\n",
                                                            -ret, errorbuf);
  }
#endif /* THREADING_SUPPORT */
#endif /* POLARSSL_VERSION_NUMBER<0x01010000 */

  /* Load the trusted CA */
  memset(&connssl->cacert, 0, sizeof(x509_cert));

  if(data->set.str[STRING_SSL_CAFILE]) {
    ret = x509parse_crtfile(&connssl->cacert,
                            data->set.str[STRING_SSL_CAFILE]);

    if(ret<0) {
#ifdef POLARSSL_ERROR_C
      error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
      failf(data, "Error reading ca cert file %s - PolarSSL: (-0x%04X) %s",
            data->set.str[STRING_SSL_CAFILE], -ret, errorbuf);

      if(data->set.ssl.verifypeer)
        return CURLE_SSL_CACERT_BADFILE;
    }
  }

  /* Load the client certificate */
  memset(&connssl->clicert, 0, sizeof(x509_cert));

  if(data->set.str[STRING_CERT]) {
    ret = x509parse_crtfile(&connssl->clicert,
                            data->set.str[STRING_CERT]);

    if(ret) {
#ifdef POLARSSL_ERROR_C
      error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
      failf(data, "Error reading client cert file %s - PolarSSL: (-0x%04X) %s",
            data->set.str[STRING_CERT], -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load the client private key */
  if(data->set.str[STRING_KEY]) {
    ret = x509parse_keyfile(&connssl->rsa,
                            data->set.str[STRING_KEY],
                            data->set.str[STRING_KEY_PASSWD]);

    if(ret) {
#ifdef POLARSSL_ERROR_C
      error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
      failf(data, "Error reading private key %s - PolarSSL: (-0x%04X) %s",
            data->set.str[STRING_KEY], -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }
  }

  /* Load the CRL */
  memset(&connssl->crl, 0, sizeof(x509_crl));

  if(data->set.str[STRING_SSL_CRLFILE]) {
    ret = x509parse_crlfile(&connssl->crl,
                            data->set.str[STRING_SSL_CRLFILE]);

    if(ret) {
#ifdef POLARSSL_ERROR_C
      error_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* POLARSSL_ERROR_C */
      failf(data, "Error reading CRL file %s - PolarSSL: (-0x%04X) %s",
            data->set.str[STRING_SSL_CRLFILE], -ret, errorbuf);

      return CURLE_SSL_CRL_BADFILE;
    }
  }

  infof(data, "PolarSSL: Connecting to %s:%d\n",
        conn->host.name, conn->remote_port);

  if(ssl_init(&connssl->ssl)) {
    failf(data, "PolarSSL: ssl_init failed");
    return CURLE_SSL_CONNECT_ERROR;
  }

  ssl_set_endpoint(&connssl->ssl, SSL_IS_CLIENT);
  ssl_set_authmode(&connssl->ssl, SSL_VERIFY_OPTIONAL);

#if POLARSSL_VERSION_NUMBER<0x01010000
  ssl_set_rng(&connssl->ssl, havege_rand,
              &connssl->hs);
#else
  ssl_set_rng(&connssl->ssl, ctr_drbg_random,
              &connssl->ctr_drbg);
#endif /* POLARSSL_VERSION_NUMBER<0x01010000 */
  ssl_set_bio(&connssl->ssl,
              net_recv, &conn->sock[sockindex],
              net_send, &conn->sock[sockindex]);


#if POLARSSL_VERSION_NUMBER<0x01000000
  ssl_set_ciphers(&connssl->ssl, ssl_default_ciphers);
#else
  ssl_set_ciphersuites(&connssl->ssl, ssl_default_ciphersuites);
#endif
  if(!Curl_ssl_getsessionid(conn, &old_session, &old_session_size)) {
    memcpy(&connssl->ssn, old_session, old_session_size);
    infof(data, "PolarSSL re-using session\n");
  }

/* PolarSSL SVN revision r1316 to r1317, matching <1.2.0 is to cover Ubuntu's
   1.1.4 version and the like */
#if POLARSSL_VERSION_NUMBER<0x01020000
  ssl_set_session(&connssl->ssl, 1, 600,
                  &connssl->ssn);
#else
  ssl_set_session(&connssl->ssl,
                  &connssl->ssn);
#endif

  ssl_set_ca_chain(&connssl->ssl,
                   &connssl->cacert,
                   &connssl->crl,
                   conn->host.name);

  ssl_set_own_cert(&connssl->ssl,
                   &connssl->clicert, &connssl->rsa);

  if(!Curl_inet_pton(AF_INET, conn->host.name, &addr) &&
#ifdef ENABLE_IPV6
     !Curl_inet_pton(AF_INET6, conn->host.name, &addr) &&
#endif
     sni && ssl_set_hostname(&connssl->ssl, conn->host.name)) {
     infof(data, "WARNING: failed to configure "
                 "server name indication (SNI) TLS extension\n");
  }

#ifdef POLARSSL_DEBUG
  ssl_set_dbg(&connssl->ssl, polarssl_debug, data);
#endif

  connssl->connecting_state = ssl_connect_2;

  return CURLE_OK;
}