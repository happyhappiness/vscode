{
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