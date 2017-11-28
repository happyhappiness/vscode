Security::ContextPointer
Ssl::createSSLContext(Security::CertPointer & x509, Ssl::EVP_PKEY_Pointer & pkey, AnyP::PortCfg &port)
{
    Security::ContextPointer ctx(port.secure.createBlankContext());

    if (!SSL_CTX_use_certificate(ctx.get(), x509.get()))
        return Security::ContextPointer();

    if (!SSL_CTX_use_PrivateKey(ctx.get(), pkey.get()))
        return Security::ContextPointer();

    if (!configureSslContext(ctx, port))
        return Security::ContextPointer();

    return ctx;
}