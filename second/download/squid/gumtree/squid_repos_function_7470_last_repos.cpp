static int
ssl_next_proto_cb(SSL *s, unsigned char **out, unsigned char *outlen, const unsigned char *in, unsigned int inlen, void *arg)
{
    static const unsigned char supported_protos[] = {8, 'h','t','t', 'p', '/', '1', '.', '1'};
    (void)SSL_select_next_proto(out, outlen, in, inlen, supported_protos, sizeof(supported_protos));
    return SSL_TLSEXT_ERR_OK;
}