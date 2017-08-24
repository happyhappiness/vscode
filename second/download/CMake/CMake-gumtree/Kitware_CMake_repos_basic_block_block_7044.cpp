{
      memcpy(&alpn_buffer[cur], NGHTTP2_PROTO_ALPN, NGHTTP2_PROTO_ALPN_LEN);
      cur += NGHTTP2_PROTO_ALPN_LEN;
      infof(data, "schannel: ALPN, offering %s\n", NGHTTP2_PROTO_VERSION_ID);
    }