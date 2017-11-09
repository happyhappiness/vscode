static CURLcode
cyassl_connect_step2(struct connectdata *conn,
                     int sockindex)
{
  int ret = -1;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data* connssl = &conn->ssl[sockindex];
  const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;
  const char * const dispname = SSL_IS_PROXY() ?
    conn->http_proxy.host.dispname : conn->host.dispname;
  const char * const pinnedpubkey = SSL_IS_PROXY() ?
                        data->set.str[STRING_SSL_PINNEDPUBLICKEY_PROXY] :
                        data->set.str[STRING_SSL_PINNEDPUBLICKEY_ORIG];

  conn->recv[sockindex] = cyassl_recv;
  conn->send[sockindex] = cyassl_send;

  /* Enable RFC2818 checks */
  if(SSL_CONN_CONFIG(verifyhost)) {
    ret = CyaSSL_check_domain_name(BACKEND->handle, hostname);
    if(ret == SSL_FAILURE)
      return CURLE_OUT_OF_MEMORY;
  }

  ret = SSL_connect(BACKEND->handle);
  if(ret != 1) {
    char error_buffer[CYASSL_MAX_ERROR_SZ];
    int  detail = SSL_get_error(BACKEND->handle, ret);

    if(SSL_ERROR_WANT_READ == detail) {
      connssl->connecting_state = ssl_connect_2_reading;
      return CURLE_OK;
    }
    else if(SSL_ERROR_WANT_WRITE == detail) {
      connssl->connecting_state = ssl_connect_2_writing;
      return CURLE_OK;
    }
    /* There is no easy way to override only the CN matching.
     * This will enable the override of both mismatching SubjectAltNames
     * as also mismatching CN fields */
    else if(DOMAIN_NAME_MISMATCH == detail) {
#if 1
      failf(data, "\tsubject alt name(s) or common name do not match \"%s\"\n",
            dispname);
      return CURLE_PEER_FAILED_VERIFICATION;
#else
      /* When the CyaSSL_check_domain_name() is used and you desire to continue
       * on a DOMAIN_NAME_MISMATCH, i.e. 'conn->ssl_config.verifyhost == 0',
       * CyaSSL version 2.4.0 will fail with an INCOMPLETE_DATA error. The only
       * way to do this is currently to switch the CyaSSL_check_domain_name()
       * in and out based on the 'conn->ssl_config.verifyhost' value. */
      if(SSL_CONN_CONFIG(verifyhost)) {
        failf(data,
              "\tsubject alt name(s) or common name do not match \"%s\"\n",
              dispname);
        return CURLE_PEER_FAILED_VERIFICATION;
      }
      else {
        infof(data,
              "\tsubject alt name(s) and/or common name do not match \"%s\"\n",
              dispname);
        return CURLE_OK;
      }
#endif
    }
#if LIBCYASSL_VERSION_HEX >= 0x02007000 /* 2.7.0 */
    else if(ASN_NO_SIGNER_E == detail) {
      if(SSL_CONN_CONFIG(verifypeer)) {
        failf(data, "\tCA signer not available for verification\n");
        return CURLE_SSL_CACERT_BADFILE;
      }
      else {
        /* Just continue with a warning if no strict certificate
           verification is required. */
        infof(data, "CA signer not available for verification, "
                    "continuing anyway\n");
      }
    }
#endif
    else {
      failf(data, "SSL_connect failed with error %d: %s", detail,
          ERR_error_string(detail, error_buffer));
      return CURLE_SSL_CONNECT_ERROR;
    }
  }

  if(pinnedpubkey) {
#ifdef KEEP_PEER_CERT
    X509 *x509;
    const char *x509_der;
    int x509_der_len;
    curl_X509certificate x509_parsed;
    curl_asn1Element *pubkey;
    CURLcode result;

    x509 = SSL_get_peer_certificate(BACKEND->handle);
    if(!x509) {
      failf(data, "SSL: failed retrieving server certificate");
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }

    x509_der = (const char *)CyaSSL_X509_get_der(x509, &x509_der_len);
    if(!x509_der) {
      failf(data, "SSL: failed retrieving ASN.1 server certificate");
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }

    memset(&x509_parsed, 0, sizeof x509_parsed);
    if(Curl_parseX509(&x509_parsed, x509_der, x509_der + x509_der_len))
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;

    pubkey = &x509_parsed.subjectPublicKeyInfo;
    if(!pubkey->header || pubkey->end <= pubkey->header) {
      failf(data, "SSL: failed retrieving public key from server certificate");
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }

    result = Curl_pin_peer_pubkey(data,
                                  pinnedpubkey,
                                  (const unsigned char *)pubkey->header,
                                  (size_t)(pubkey->end - pubkey->header));
    if(result) {
      failf(data, "SSL: public key does not match pinned public key!");
      return result;
    }
#else
    failf(data, "Library lacks pinning support built-in");
    return CURLE_NOT_BUILT_IN;
#endif
  }

#ifdef HAVE_ALPN
  if(conn->bits.tls_enable_alpn) {
    int rc;
    char *protocol = NULL;
    unsigned short protocol_len = 0;

    rc = wolfSSL_ALPN_GetProtocol(BACKEND->handle, &protocol, &protocol_len);

    if(rc == SSL_SUCCESS) {
      infof(data, "ALPN, server accepted to use %.*s\n", protocol_len,
            protocol);

      if(protocol_len == ALPN_HTTP_1_1_LENGTH &&
         !memcmp(protocol, ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH))
        conn->negnpn = CURL_HTTP_VERSION_1_1;
#ifdef USE_NGHTTP2
      else if(data->set.httpversion >= CURL_HTTP_VERSION_2 &&
              protocol_len == NGHTTP2_PROTO_VERSION_ID_LEN &&
              !memcmp(protocol, NGHTTP2_PROTO_VERSION_ID,
                      NGHTTP2_PROTO_VERSION_ID_LEN))
        conn->negnpn = CURL_HTTP_VERSION_2;
#endif
      else
        infof(data, "ALPN, unrecognized protocol %.*s\n", protocol_len,
              protocol);
    }
    else if(rc == SSL_ALPN_NOT_FOUND)
      infof(data, "ALPN, server did not agree to a protocol\n");
    else {
      failf(data, "ALPN, failure getting protocol, error %d", rc);
      return CURLE_SSL_CONNECT_ERROR;
    }
  }
#endif /* HAVE_ALPN */

  connssl->connecting_state = ssl_connect_3;
#if (LIBCYASSL_VERSION_HEX >= 0x03009010)
  infof(data, "SSL connection using %s / %s\n",
        wolfSSL_get_version(BACKEND->handle),
        wolfSSL_get_cipher_name(BACKEND->handle));
#else
  infof(data, "SSL connected\n");
#endif

  return CURLE_OK;
}