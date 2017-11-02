static void HandshakeCallback(PRFileDesc *sock, void *arg)
{
#ifdef USE_NGHTTP2
  struct connectdata *conn = (struct connectdata*) arg;
  unsigned int buflenmax = 50;
  unsigned char buf[50];
  unsigned int buflen;
  SSLNextProtoState state;

  struct ssl_connect_data *connssl = &conn->ssl[FIRSTSOCKET];

  if(!conn->data->set.ssl_enable_npn && !conn->data->set.ssl_enable_alpn) {
    return;
  }

  if(SSL_GetNextProto(sock, &state, buf, &buflen, buflenmax) == SECSuccess) {

    switch(state) {
    case SSL_NEXT_PROTO_NO_SUPPORT:
    case SSL_NEXT_PROTO_NO_OVERLAP:
      if(connssl->asked_for_h2)
        infof(conn->data, "TLS, neither ALPN nor NPN succeeded\n");
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

    if(buflen == NGHTTP2_PROTO_VERSION_ID_LEN &&
       !memcmp(NGHTTP2_PROTO_VERSION_ID, buf, NGHTTP2_PROTO_VERSION_ID_LEN)) {
      conn->negnpn = NPN_HTTP2;
    }
    else if(buflen == ALPN_HTTP_1_1_LENGTH &&
            !memcmp(ALPN_HTTP_1_1, buf, ALPN_HTTP_1_1_LENGTH)) {
      conn->negnpn = NPN_HTTP1_1;
    }
  }
#else
  (void)sock;
  (void)arg;
#endif
}