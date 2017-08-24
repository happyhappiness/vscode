{
    int cur = 0;
    unsigned char protocols[128];

#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2) {
      protocols[cur++] = NGHTTP2_PROTO_VERSION_ID_LEN;
      memcpy(&protocols[cur], NGHTTP2_PROTO_VERSION_ID,
          NGHTTP2_PROTO_VERSION_ID_LEN);
      cur += NGHTTP2_PROTO_VERSION_ID_LEN;
    }
#endif
    protocols[cur++] = ALPN_HTTP_1_1_LENGTH;
    memcpy(&protocols[cur], ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH);
    cur += ALPN_HTTP_1_1_LENGTH;

    if(SSL_SetNextProtoNego(connssl->handle, protocols, cur) != SECSuccess)
      goto error;
  }