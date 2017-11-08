static int
select_next_proto_cb(SSL *ssl,
                     unsigned char **out, unsigned char *outlen,
                     const unsigned char *in, unsigned int inlen,
                     void *arg)
{
  struct connectdata *conn = (struct connectdata*) arg;

  (void)ssl;

#ifdef USE_NGHTTP2
  if(conn->data->set.httpversion >= CURL_HTTP_VERSION_2 &&
     !select_next_protocol(out, outlen, in, inlen, NGHTTP2_PROTO_VERSION_ID,
                           NGHTTP2_PROTO_VERSION_ID_LEN)) {
    infof(conn->data, "NPN, negotiated HTTP2 (%s)\n",
          NGHTTP2_PROTO_VERSION_ID);
    conn->negnpn = CURL_HTTP_VERSION_2;
    return SSL_TLSEXT_ERR_OK;
  }
#endif

  if(!select_next_protocol(out, outlen, in, inlen, ALPN_HTTP_1_1,
                           ALPN_HTTP_1_1_LENGTH)) {
    infof(conn->data, "NPN, negotiated HTTP1.1\n");
    conn->negnpn = CURL_HTTP_VERSION_1_1;
    return SSL_TLSEXT_ERR_OK;
  }

  infof(conn->data, "NPN, no overlap, use HTTP1.1\n");
  *out = (unsigned char *)ALPN_HTTP_1_1;
  *outlen = ALPN_HTTP_1_1_LENGTH;
  conn->negnpn = CURL_HTTP_VERSION_1_1;

  return SSL_TLSEXT_ERR_OK;
}