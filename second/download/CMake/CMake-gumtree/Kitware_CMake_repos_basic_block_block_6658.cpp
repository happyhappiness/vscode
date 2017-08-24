f(proto.size == ALPN_HTTP_1_1_LENGTH &&
         !memcmp(ALPN_HTTP_1_1, proto.data, ALPN_HTTP_1_1_LENGTH)) {
        conn->negnpn = CURL_HTTP_VERSION_1_1;
      }