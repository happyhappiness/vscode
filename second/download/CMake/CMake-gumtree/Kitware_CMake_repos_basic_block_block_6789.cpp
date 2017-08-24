f(SSL_GetNextProto(sock, &state, buf, &buflen, buflenmax) == SECSuccess) {

    switch(state) {
#if NSSVERNUM >= 0x031a00 /* 3.26.0 */
    /* used by NSS internally to implement 0-RTT */
    case SSL_NEXT_PROTO_EARLY_VALUE:
      /* fall through! */
#endif
    case SSL_NEXT_PROTO_NO_SUPPORT:
    case SSL_NEXT_PROTO_NO_OVERLAP:
      infof(conn->data, "ALPN/NPN, server did not agree to a protocol\n");
      return;
#ifdef SSL_ENABLE_ALPN
    case SSL_NEXT_PROTO_SELECTED:
      infof(conn->data, "ALPN, server accepted to use %.*s\n", buflen, buf);
      break;
#endif
    case SSL_NEXT_PROTO_NEGOTIATED:
      infof(conn->data, "NPN, server accepted to use %.*s\n", buflen, buf);
      break;
    }

#ifdef USE_NGHTTP2
    if(buflen == NGHTTP2_PROTO_VERSION_ID_LEN &&
       !memcmp(NGHTTP2_PROTO_VERSION_ID, buf, NGHTTP2_PROTO_VERSION_ID_LEN)) {
      conn->negnpn = CURL_HTTP_VERSION_2;
    }
    else
#endif
    if(buflen == ALPN_HTTP_1_1_LENGTH &&
       !memcmp(ALPN_HTTP_1_1, buf, ALPN_HTTP_1_1_LENGTH)) {
      conn->negnpn = CURL_HTTP_VERSION_1_1;
    }
  }