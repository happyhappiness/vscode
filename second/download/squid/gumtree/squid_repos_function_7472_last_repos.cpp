static const char *
loadSystemTrustedCa(Security::ContextPointer &ctx)
{
    debugs(83, 8, "Setting default system Trusted CA. ctx=" << (void*)ctx.get());
#if USE_OPENSSL
    if (SSL_CTX_set_default_verify_paths(ctx.get()) == 0)
        return Security::ErrorString(ERR_get_error());

#elif USE_GNUTLS
    auto x = gnutls_certificate_set_x509_system_trust(ctx.get());
    if (x < 0)
        return Security::ErrorString(x);

#endif
    return nullptr;
}