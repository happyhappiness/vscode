void
Ssl::chainCertificatesToSSLContext(SSL_CTX *sslContext, AnyP::PortCfg &port)
{
    assert(sslContext != NULL);
    // Add signing certificate to the certificates chain
    X509 *signingCert = port.signingCert.get();
    if (SSL_CTX_add_extra_chain_cert(sslContext, signingCert)) {
        // increase the certificate lock
        CRYPTO_add(&(signingCert->references),1,CRYPTO_LOCK_X509);
    } else {
        const int ssl_error = ERR_get_error();
        debugs(33, DBG_IMPORTANT, "WARNING: can not add signing certificate to SSL context chain: " << ERR_error_string(ssl_error, NULL));
    }
    Ssl::addChainToSslContext(sslContext, port.certsToChain.get());
}