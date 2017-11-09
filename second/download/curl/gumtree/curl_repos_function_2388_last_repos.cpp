static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
{
  struct Curl_easy *data = conn->data;
  int err;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  long * const certverifyresult = SSL_IS_PROXY() ?
    &data->set.proxy_ssl.certverifyresult : &data->set.ssl.certverifyresult;
  DEBUGASSERT(ssl_connect_2 == connssl->connecting_state
              || ssl_connect_2_reading == connssl->connecting_state
              || ssl_connect_2_writing == connssl->connecting_state);

  ERR_clear_error();

  err = SSL_connect(BACKEND->handle);
  /* If keylogging is enabled but the keylog callback is not supported then log
     secrets here, immediately after SSL_connect by using tap_ssl_key. */
#if defined(ENABLE_SSLKEYLOGFILE) && !defined(HAVE_KEYLOG_CALLBACK)
  tap_ssl_key(BACKEND->handle, &BACKEND->tap_state);
#endif

  /* 1  is fine
     0  is "not successful but was shut down controlled"
     <0 is "handshake was not successful, because a fatal error occurred" */
  if(1 != err) {
    int detail = SSL_get_error(BACKEND->handle, err);

    if(SSL_ERROR_WANT_READ == detail) {
      connssl->connecting_state = ssl_connect_2_reading;
      return CURLE_OK;
    }
    if(SSL_ERROR_WANT_WRITE == detail) {
      connssl->connecting_state = ssl_connect_2_writing;
      return CURLE_OK;
    }
    else {
      /* untreated error */
      unsigned long errdetail;
      char error_buffer[256]="";
      CURLcode result;
      long lerr;
      int lib;
      int reason;

      /* the connection failed, we're not waiting for anything else. */
      connssl->connecting_state = ssl_connect_2;

      /* Get the earliest error code from the thread's error queue and removes
         the entry. */
      errdetail = ERR_get_error();

      /* Extract which lib and reason */
      lib = ERR_GET_LIB(errdetail);
      reason = ERR_GET_REASON(errdetail);

      if((lib == ERR_LIB_SSL) &&
         (reason == SSL_R_CERTIFICATE_VERIFY_FAILED)) {
        result = CURLE_SSL_CACERT;

        lerr = SSL_get_verify_result(BACKEND->handle);
        if(lerr != X509_V_OK) {
          *certverifyresult = lerr;
          snprintf(error_buffer, sizeof(error_buffer),
                   "SSL certificate problem: %s",
                   X509_verify_cert_error_string(lerr));
        }
        else
          /* strcpy() is fine here as long as the string fits within
             error_buffer */
          strcpy(error_buffer, "SSL certificate verification failed");
      }
      else {
        result = CURLE_SSL_CONNECT_ERROR;
        ossl_strerror(errdetail, error_buffer, sizeof(error_buffer));
      }

      /* detail is already set to the SSL error above */

      /* If we e.g. use SSLv2 request-method and the server doesn't like us
       * (RST connection etc.), OpenSSL gives no explanation whatsoever and
       * the SO_ERROR is also lost.
       */
      if(CURLE_SSL_CONNECT_ERROR == result && errdetail == 0) {
        const char * const hostname = SSL_IS_PROXY() ?
          conn->http_proxy.host.name : conn->host.name;
        const long int port = SSL_IS_PROXY() ? conn->port : conn->remote_port;
        failf(data, OSSL_PACKAGE " SSL_connect: %s in connection to %s:%ld ",
              SSL_ERROR_to_str(detail), hostname, port);
        return result;
      }

      /* Could be a CERT problem */
      failf(data, "%s", error_buffer);

      return result;
    }
  }
  else {
    /* we have been connected fine, we're not waiting for anything else. */
    connssl->connecting_state = ssl_connect_3;

    /* Informational message */
    infof(data, "SSL connection using %s / %s\n",
          get_ssl_version_txt(BACKEND->handle),
          SSL_get_cipher(BACKEND->handle));

#ifdef HAS_ALPN
    /* Sets data and len to negotiated protocol, len is 0 if no protocol was
     * negotiated
     */
    if(conn->bits.tls_enable_alpn) {
      const unsigned char *neg_protocol;
      unsigned int len;
      SSL_get0_alpn_selected(BACKEND->handle, &neg_protocol, &len);
      if(len != 0) {
        infof(data, "ALPN, server accepted to use %.*s\n", len, neg_protocol);

#ifdef USE_NGHTTP2
        if(len == NGHTTP2_PROTO_VERSION_ID_LEN &&
           !memcmp(NGHTTP2_PROTO_VERSION_ID, neg_protocol, len)) {
          conn->negnpn = CURL_HTTP_VERSION_2;
        }
        else
#endif
        if(len == ALPN_HTTP_1_1_LENGTH &&
           !memcmp(ALPN_HTTP_1_1, neg_protocol, ALPN_HTTP_1_1_LENGTH)) {
          conn->negnpn = CURL_HTTP_VERSION_1_1;
        }
      }
      else
        infof(data, "ALPN, server did not agree to a protocol\n");
    }
#endif

    return CURLE_OK;
  }
}