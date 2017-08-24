{

      infof(data, "schannel: ALPN, server accepted to use %.*s\n",
        alpn_result.ProtocolIdSize, alpn_result.ProtocolId);

#ifdef USE_NGHTTP2
      if(alpn_result.ProtocolIdSize == NGHTTP2_PROTO_VERSION_ID_LEN &&
         !memcmp(NGHTTP2_PROTO_VERSION_ID, alpn_result.ProtocolId,
          NGHTTP2_PROTO_VERSION_ID_LEN)) {
        conn->negnpn = CURL_HTTP_VERSION_2;
      }
      else
#endif
      if(alpn_result.ProtocolIdSize == ALPN_HTTP_1_1_LENGTH &&
         !memcmp(ALPN_HTTP_1_1, alpn_result.ProtocolId,
           ALPN_HTTP_1_1_LENGTH)) {
        conn->negnpn = CURL_HTTP_VERSION_1_1;
      }
    }