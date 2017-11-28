void
Ssl::useSquidUntrusted(SSL_CTX *sslContext)
{
    SSL_CTX_set_cert_verify_callback(sslContext, untrustedToStoreCtx_cb, NULL);
}