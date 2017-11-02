static int
select_next_proto_cb(SSL *ssl,
                     unsigned char **out, unsigned char *outlen,
                     const unsigned char *in, unsigned int inlen,
                     void *arg)
{
  struct connectdata *conn = (struct connectdata*) arg;
  int retval = nghttp2_select_next_protocol(out, outlen, in, inlen);

  (void)ssl;

  if(retval == 1) {
    infof(conn->data, "NPN, negotiated HTTP2 (%s)\n",
          NGHTTP2_PROTO_VERSION_ID);
    conn->negnpn = NPN_HTTP2;
  }
  else if(retval == 0) {
    infof(conn->data, "NPN, negotiated HTTP1.1\n");
    conn->negnpn = NPN_HTTP1_1;
  }
  else {
    infof(conn->data, "NPN, no overlap, use HTTP1.1\n",
          NGHTTP2_PROTO_VERSION_ID);
    *out = (unsigned char*)"http/1.1";
    *outlen = sizeof("http/1.1") - 1;
    conn->negnpn = NPN_HTTP1_1;
  }

  return SSL_TLSEXT_ERR_OK;
}