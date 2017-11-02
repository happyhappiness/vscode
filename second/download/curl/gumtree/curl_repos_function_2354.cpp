static CURLcode
gtls_connect_step1(struct connectdata *conn,
                   int sockindex)
{
  struct SessionHandle *data = conn->data;
  gnutls_session_t session;
  int rc;
  void *ssl_sessionid;
  size_t ssl_idsize;
  bool sni = TRUE; /* default is SNI enabled */
#ifdef ENABLE_IPV6
  struct in6_addr addr;
#else
  struct in_addr addr;
#endif
#ifndef USE_GNUTLS_PRIORITY_SET_DIRECT
  static const int cipher_priority[] = {
  /* These two ciphers were added to GnuTLS as late as ver. 3.0.1,
     but this code path is only ever used for ver. < 2.12.0.
     GNUTLS_CIPHER_AES_128_GCM,
     GNUTLS_CIPHER_AES_256_GCM,
  */
    GNUTLS_CIPHER_AES_128_CBC,
    GNUTLS_CIPHER_AES_256_CBC,
    GNUTLS_CIPHER_CAMELLIA_128_CBC,
    GNUTLS_CIPHER_CAMELLIA_256_CBC,
    GNUTLS_CIPHER_3DES_CBC,
  };
  static const int cert_type_priority[] = { GNUTLS_CRT_X509, 0 };
  static int protocol_priority[] = { 0, 0, 0, 0 };
#else
#define GNUTLS_CIPHERS "NORMAL:-ARCFOUR-128:-CTYPE-ALL:+CTYPE-X509"
/* If GnuTLS was compiled without support for SRP it will error out if SRP is
   requested in the priority string, so treat it specially
 */
#define GNUTLS_SRP "+SRP"
  const char* prioritylist;
  const char *err = NULL;
#endif
#ifdef HAS_ALPN
  int protocols_size = 2;
  gnutls_datum_t protocols[2];
#endif

  if(conn->ssl[sockindex].state == ssl_connection_complete)
    /* to make us tolerant against being called more than once for the
       same connection */
    return CURLE_OK;

  if(!gtls_inited)
    Curl_gtls_init();

  /* GnuTLS only supports SSLv3 and TLSv1 */
  if(data->set.ssl.version == CURL_SSLVERSION_SSLv2) {
    failf(data, "GnuTLS does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }
  else if(data->set.ssl.version == CURL_SSLVERSION_SSLv3)
    sni = FALSE; /* SSLv3 has no SNI */

  /* allocate a cred struct */
  rc = gnutls_certificate_allocate_credentials(&conn->ssl[sockindex].cred);
  if(rc != GNUTLS_E_SUCCESS) {
    failf(data, "gnutls_cert_all_cred() failed: %s", gnutls_strerror(rc));
    return CURLE_SSL_CONNECT_ERROR;
  }

#ifdef USE_TLS_SRP
  if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
    infof(data, "Using TLS-SRP username: %s\n", data->set.ssl.username);

    rc = gnutls_srp_allocate_client_credentials(
           &conn->ssl[sockindex].srp_client_cred);
    if(rc != GNUTLS_E_SUCCESS) {
      failf(data, "gnutls_srp_allocate_client_cred() failed: %s",
            gnutls_strerror(rc));
      return CURLE_OUT_OF_MEMORY;
    }

    rc = gnutls_srp_set_client_credentials(conn->ssl[sockindex].
                                           srp_client_cred,
                                           data->set.ssl.username,
                                           data->set.ssl.password);
    if(rc != GNUTLS_E_SUCCESS) {
      failf(data, "gnutls_srp_set_client_cred() failed: %s",
            gnutls_strerror(rc));
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
  }
#endif

  if(data->set.ssl.CAfile) {
    /* set the trusted CA cert bundle file */
    gnutls_certificate_set_verify_flags(conn->ssl[sockindex].cred,
                                        GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT);

    rc = gnutls_certificate_set_x509_trust_file(conn->ssl[sockindex].cred,
                                                data->set.ssl.CAfile,
                                                GNUTLS_X509_FMT_PEM);
    if(rc < 0) {
      infof(data, "error reading ca cert file %s (%s)\n",
            data->set.ssl.CAfile, gnutls_strerror(rc));
      if(data->set.ssl.verifypeer)
        return CURLE_SSL_CACERT_BADFILE;
    }
    else
      infof(data, "found %d certificates in %s\n",
            rc, data->set.ssl.CAfile);
  }

  if(data->set.ssl.CRLfile) {
    /* set the CRL list file */
    rc = gnutls_certificate_set_x509_crl_file(conn->ssl[sockindex].cred,
                                              data->set.ssl.CRLfile,
                                              GNUTLS_X509_FMT_PEM);
    if(rc < 0) {
      failf(data, "error reading crl file %s (%s)",
            data->set.ssl.CRLfile, gnutls_strerror(rc));
      return CURLE_SSL_CRL_BADFILE;
    }
    else
      infof(data, "found %d CRL in %s\n",
            rc, data->set.ssl.CRLfile);
  }

  /* Initialize TLS session as a client */
  rc = gnutls_init(&conn->ssl[sockindex].session, GNUTLS_CLIENT);
  if(rc != GNUTLS_E_SUCCESS) {
    failf(data, "gnutls_init() failed: %d", rc);
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* convenient assign */
  session = conn->ssl[sockindex].session;

  if((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
#endif
     sni &&
     (gnutls_server_name_set(session, GNUTLS_NAME_DNS, conn->host.name,
                             strlen(conn->host.name)) < 0))
    infof(data, "WARNING: failed to configure server name indication (SNI) "
          "TLS extension\n");

  /* Use default priorities */
  rc = gnutls_set_default_priority(session);
  if(rc != GNUTLS_E_SUCCESS)
    return CURLE_SSL_CONNECT_ERROR;

#ifndef USE_GNUTLS_PRIORITY_SET_DIRECT
  rc = gnutls_cipher_set_priority(session, cipher_priority);
  if(rc != GNUTLS_E_SUCCESS)
    return CURLE_SSL_CONNECT_ERROR;

  /* Sets the priority on the certificate types supported by gnutls. Priority
   is higher for types specified before others. After specifying the types
   you want, you must append a 0. */
  rc = gnutls_certificate_type_set_priority(session, cert_type_priority);
  if(rc != GNUTLS_E_SUCCESS)
    return CURLE_SSL_CONNECT_ERROR;

  if(data->set.ssl.cipher_list != NULL) {
    failf(data, "can't pass a custom cipher list to older GnuTLS"
          " versions");
    return CURLE_SSL_CONNECT_ERROR;
  }

  switch (data->set.ssl.version) {
    case CURL_SSLVERSION_SSLv3:
      protocol_priority[0] = GNUTLS_SSL3;
      break;
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      protocol_priority[0] = GNUTLS_TLS1_0;
      protocol_priority[1] = GNUTLS_TLS1_1;
      protocol_priority[2] = GNUTLS_TLS1_2;
      break;
    case CURL_SSLVERSION_TLSv1_0:
      protocol_priority[0] = GNUTLS_TLS1_0;
      break;
    case CURL_SSLVERSION_TLSv1_1:
      protocol_priority[0] = GNUTLS_TLS1_1;
      break;
    case CURL_SSLVERSION_TLSv1_2:
      protocol_priority[0] = GNUTLS_TLS1_2;
    break;
      case CURL_SSLVERSION_SSLv2:
    default:
      failf(data, "GnuTLS does not support SSLv2");
      return CURLE_SSL_CONNECT_ERROR;
      break;
  }
  rc = gnutls_protocol_set_priority(session, protocol_priority);
  if(rc != GNUTLS_E_SUCCESS) {
    failf(data, "Did you pass a valid GnuTLS cipher list?");
    return CURLE_SSL_CONNECT_ERROR;
  }

#else
  /* Ensure +SRP comes at the *end* of all relevant strings so that it can be
   * removed if a run-time error indicates that SRP is not supported by this
   * GnuTLS version */
  switch (data->set.ssl.version) {
    case CURL_SSLVERSION_SSLv3:
      prioritylist = GNUTLS_CIPHERS ":-VERS-TLS-ALL:+VERS-SSL3.0";
      sni = false;
      break;
    case CURL_SSLVERSION_DEFAULT:
    case CURL_SSLVERSION_TLSv1:
      prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:" GNUTLS_SRP;
      break;
    case CURL_SSLVERSION_TLSv1_0:
      prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                     "+VERS-TLS1.0:" GNUTLS_SRP;
      break;
    case CURL_SSLVERSION_TLSv1_1:
      prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                     "+VERS-TLS1.1:" GNUTLS_SRP;
      break;
    case CURL_SSLVERSION_TLSv1_2:
      prioritylist = GNUTLS_CIPHERS ":-VERS-SSL3.0:-VERS-TLS-ALL:"
                     "+VERS-TLS1.2:" GNUTLS_SRP;
      break;
    case CURL_SSLVERSION_SSLv2:
    default:
      failf(data, "GnuTLS does not support SSLv2");
      return CURLE_SSL_CONNECT_ERROR;
      break;
  }
  rc = gnutls_priority_set_direct(session, prioritylist, &err);
  if((rc == GNUTLS_E_INVALID_REQUEST) && err) {
    if(!strcmp(err, GNUTLS_SRP)) {
      /* This GnuTLS was probably compiled without support for SRP.
       * Note that fact and try again without it. */
      int validprioritylen = curlx_uztosi(err - prioritylist);
      char *prioritycopy = strdup(prioritylist);
      if(!prioritycopy)
        return CURLE_OUT_OF_MEMORY;

      infof(data, "This GnuTLS does not support SRP\n");
      if(validprioritylen)
        /* Remove the :+SRP */
        prioritycopy[validprioritylen - 1] = 0;
      rc = gnutls_priority_set_direct(session, prioritycopy, &err);
      free(prioritycopy);
    }
  }
  if(rc != GNUTLS_E_SUCCESS) {
    failf(data, "Error %d setting GnuTLS cipher list starting with %s",
          rc, err);
    return CURLE_SSL_CONNECT_ERROR;
  }
#endif

#ifdef HAS_ALPN
  if(data->set.httpversion == CURL_HTTP_VERSION_2_0) {
    if(data->set.ssl_enable_alpn) {
      protocols[0].data = NGHTTP2_PROTO_VERSION_ID;
      protocols[0].size = NGHTTP2_PROTO_VERSION_ID_LEN;
      protocols[1].data = ALPN_HTTP_1_1;
      protocols[1].size = ALPN_HTTP_1_1_LENGTH;
      gnutls_alpn_set_protocols(session, protocols, protocols_size, 0);
      infof(data, "ALPN, offering %s, %s\n", NGHTTP2_PROTO_VERSION_ID,
            ALPN_HTTP_1_1);
      conn->ssl[sockindex].asked_for_h2 = TRUE;
    }
    else {
      infof(data, "SSL, can't negotiate HTTP/2.0 without ALPN\n");
    }
  }
#endif

  if(data->set.str[STRING_CERT]) {
    if(gnutls_certificate_set_x509_key_file(
         conn->ssl[sockindex].cred,
         data->set.str[STRING_CERT],
         data->set.str[STRING_KEY] ?
         data->set.str[STRING_KEY] : data->set.str[STRING_CERT],
         do_file_type(data->set.str[STRING_CERT_TYPE]) ) !=
       GNUTLS_E_SUCCESS) {
      failf(data, "error reading X.509 key or certificate file");
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

#ifdef USE_TLS_SRP
  /* put the credentials to the current session */
  if(data->set.ssl.authtype == CURL_TLSAUTH_SRP) {
    rc = gnutls_credentials_set(session, GNUTLS_CRD_SRP,
                                conn->ssl[sockindex].srp_client_cred);
    if(rc != GNUTLS_E_SUCCESS)
      failf(data, "gnutls_credentials_set() failed: %s", gnutls_strerror(rc));
  }
  else
#endif
    rc = gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE,
                                conn->ssl[sockindex].cred);

  /* set the connection handle (file descriptor for the socket) */
  gnutls_transport_set_ptr(session,
                           GNUTLS_INT_TO_POINTER_CAST(conn->sock[sockindex]));

  /* register callback functions to send and receive data. */
  gnutls_transport_set_push_function(session, Curl_gtls_push);
  gnutls_transport_set_pull_function(session, Curl_gtls_pull);

  /* lowat must be set to zero when using custom push and pull functions. */
  gnutls_transport_set_lowat(session, 0);

#ifdef HAS_OCSP
  if(data->set.ssl.verifystatus) {
    rc = gnutls_ocsp_status_request_enable_client(session, NULL, 0, NULL);
    if(rc != GNUTLS_E_SUCCESS) {
      failf(data, "gnutls_ocsp_status_request_enable_client() failed: %d", rc);
      return CURLE_SSL_CONNECT_ERROR;
    }
  }
#endif

  /* This might be a reconnect, so we check for a session ID in the cache
     to speed up things */

  if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, &ssl_idsize)) {
    /* we got a session id, use it! */
    gnutls_session_set_data(session, ssl_sessionid, ssl_idsize);

    /* Informational message */
    infof (data, "SSL re-using session ID\n");
  }

  return CURLE_OK;
}