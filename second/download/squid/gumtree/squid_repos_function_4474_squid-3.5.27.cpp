void
Ssl::configureUnconfiguredSslContext(SSL_CTX *sslContext, Ssl::CertSignAlgorithm signAlgorithm,AnyP::PortCfg &port)
{
    if (sslContext && signAlgorithm == Ssl::algSignTrusted) {
        Ssl::chainCertificatesToSSLContext(sslContext, port);
    }
}