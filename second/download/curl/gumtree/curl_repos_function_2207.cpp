static CURLcode
cyassl_connect_step1(struct connectdata *conn,
                     int sockindex)
{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data* conssl = &conn->ssl[sockindex];
  SSL_METHOD* req_method = NULL;
  void* ssl_sessionid = NULL;
  curl_socket_t sockfd = conn->sock[sockindex];

  if(conssl->state == ssl_connection_complete)
    return CURLE_OK;

  /* CyaSSL doesn't support SSLv2 */
  if(data->set.ssl.version == CURL_SSLVERSION_SSLv2) {
    failf(data, "CyaSSL does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* check to see if we've been told to use an explicit SSL/TLS version */
  switch(data->set.ssl.version) {
  default:
  case CURL_SSLVERSION_DEFAULT:
  case CURL_SSLVERSION_TLSv1:
    infof(data, "CyaSSL cannot be configured to use TLS 1.0-1.2, "
          "TLS 1.0 is used exclusively\n");
    req_method = TLSv1_client_method();
    break;
  case CURL_SSLVERSION_TLSv1_0:
    req_method = TLSv1_client_method();
    break;
  case CURL_SSLVERSION_TLSv1_1:
    req_method = TLSv1_1_client_method();
    break;
  case CURL_SSLVERSION_TLSv1_2:
    req_method = TLSv1_2_client_method();
    break;
  case CURL_SSLVERSION_SSLv3:
    req_method = SSLv3_client_method();
    break;
  }

  if(!req_method) {
    failf(data, "SSL: couldn't create a method!");
    return CURLE_OUT_OF_MEMORY;
  }

  if(conssl->ctx)
    SSL_CTX_free(conssl->ctx);
  conssl->ctx = SSL_CTX_new(req_method);

  if(!conssl->ctx) {
    failf(data, "SSL: couldn't create a context!");
    return CURLE_OUT_OF_MEMORY;
  }

#ifndef NO_FILESYSTEM
  /* load trusted cacert */
  if(data->set.str[STRING_SSL_CAFILE]) {
    if(!SSL_CTX_load_verify_locations(conssl->ctx,
                                      data->set.str[STRING_SSL_CAFILE],
                                      data->set.str[STRING_SSL_CAPATH])) {
      if(data->set.ssl.verifypeer) {
        /* Fail if we insist on successfully verifying the server. */
        failf(data,"error setting certificate verify locations:\n"
              "  CAfile: %s\n  CApath: %s",
              data->set.str[STRING_SSL_CAFILE]?
              data->set.str[STRING_SSL_CAFILE]: "none",
              data->set.str[STRING_SSL_CAPATH]?
              data->set.str[STRING_SSL_CAPATH] : "none");
        return CURLE_SSL_CACERT_BADFILE;
      }
      else {
        /* Just continue with a warning if no strict certificate
           verification is required. */
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
          data->set.str[STRING_SSL_CAFILE] ? data->set.str[STRING_SSL_CAFILE]:
          "none",
          data->set.str[STRING_SSL_CAPATH] ? data->set.str[STRING_SSL_CAPATH]:
          "none");
  }

  /* Load the client certificate, and private key */
  if(data->set.str[STRING_CERT] && data->set.str[STRING_KEY]) {
    int file_type = do_file_type(data->set.str[STRING_CERT_TYPE]);

    if(SSL_CTX_use_certificate_file(conssl->ctx, data->set.str[STRING_CERT],
                                     file_type) != 1) {
      failf(data, "unable to use client certificate (no key or wrong pass"
            " phrase?)");
      return CURLE_SSL_CONNECT_ERROR;
    }

    file_type = do_file_type(data->set.str[STRING_KEY_TYPE]);
    if(SSL_CTX_use_PrivateKey_file(conssl->ctx, data->set.str[STRING_KEY],
                                    file_type) != 1) {
      failf(data, "unable to set private key");
      return CURLE_SSL_CONNECT_ERROR;
    }
  }
#else
  if(CyaSSL_no_filesystem_verify(conssl->ctx)!= SSL_SUCCESS) {
    return CURLE_SSL_CONNECT_ERROR;
  }
#endif /* NO_FILESYSTEM */

  /* SSL always tries to verify the peer, this only says whether it should
   * fail to connect if the verification fails, or if it should continue
   * anyway. In the latter case the result of the verification is checked with
   * SSL_get_verify_result() below. */
  SSL_CTX_set_verify(conssl->ctx,
                     data->set.ssl.verifypeer?SSL_VERIFY_PEER:SSL_VERIFY_NONE,
                     NULL);

  /* Let's make an SSL structure */
  if(conssl->handle)
    SSL_free(conssl->handle);
  conssl->handle = SSL_new(conssl->ctx);
  if(!conssl->handle) {
    failf(data, "SSL: couldn't create a context (handle)!");
    return CURLE_OUT_OF_MEMORY;
  }

  /* Check if there's a cached ID we can/should use here! */
  if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, NULL)) {
    /* we got a session id, use it! */
    if(!SSL_set_session(conssl->handle, ssl_sessionid)) {
      failf(data, "SSL: SSL_set_session failed: %s",
            ERR_error_string(SSL_get_error(conssl->handle, 0),NULL));
      return CURLE_SSL_CONNECT_ERROR;
    }
    /* Informational message */
    infof (data, "SSL re-using session ID\n");
  }

  /* pass the raw socket into the SSL layer */
  if(!SSL_set_fd(conssl->handle, (int)sockfd)) {
    failf(data, "SSL: SSL_set_fd failed");
    return CURLE_SSL_CONNECT_ERROR;
  }

  conssl->connecting_state = ssl_connect_2;
  return CURLE_OK;
}