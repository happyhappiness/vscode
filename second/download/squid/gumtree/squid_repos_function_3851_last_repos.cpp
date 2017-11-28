void
Ssl::configureUnconfiguredSslContext(Security::ContextPointer &ctx, Ssl::CertSignAlgorithm signAlgorithm,AnyP::PortCfg &port)
{
    if (ctx && signAlgorithm == Ssl::algSignTrusted)
        Ssl::chainCertificatesToSSLContext(ctx, port);
}