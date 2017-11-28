void
Ssl::useSquidUntrusted(SSL_CTX *sslContext)
{
    if (SquidUntrustedCerts.size() > 0)
        SSL_CTX_set_cert_verify_callback(sslContext, untrustedToStoreCtx_cb, NULL);
    else
        SSL_CTX_set_cert_verify_callback(sslContext, NULL, NULL);
}