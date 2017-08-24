{
    const char *next_protocol = ssl_get_alpn_protocol(&connssl->ssl);

    if(next_protocol != NULL) {
      infof(data, "ALPN, server accepted to use %s\n", next_protocol);

#ifdef USE_NGHTTP2
      if(!strncmp(next_protocol, NGHTTP2_PROTO_VERSION_ID,
                  NGHTTP2_PROTO_VERSION_ID_LEN)) {
        conn->negnpn = CURL_HTTP_VERSION_2;
      }
      else
#endif
        if(!strncmp(next_protocol, ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH)) {
          conn->negnpn = CURL_HTTP_VERSION_1_1;
        }
    }
    else
      infof(data, "ALPN, server did not agree to a protocol\n");
  }