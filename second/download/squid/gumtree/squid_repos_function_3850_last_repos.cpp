void
Ssl::chainCertificatesToSSLContext(Security::ContextPointer &ctx, AnyP::PortCfg &port)
{
    assert(ctx);
    // Add signing certificate to the certificates chain
    X509 *signingCert = port.signingCert.get();
    if (SSL_CTX_add_extra_chain_cert(ctx.get(), signingCert)) {
        // increase the certificate lock
        X509_up_ref(signingCert);
    } else {
        const int ssl_error = ERR_get_error();
        debugs(33, DBG_IMPORTANT, "WARNING: can not add signing certificate to SSL context chain: " << Security::ErrorString(ssl_error));
    }
    Ssl::addChainToSslContext(ctx, port.certsToChain.get());
}