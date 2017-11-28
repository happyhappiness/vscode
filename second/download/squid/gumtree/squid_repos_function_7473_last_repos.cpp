void
Security::PeerOptions::updateContextCa(Security::ContextPointer &ctx)
{
    debugs(83, 8, "Setting CA certificate locations.");
#if USE_OPENSSL
    const char *path = caDir.isEmpty() ? nullptr : caDir.c_str();
#endif
    for (auto i : caFiles) {
#if USE_OPENSSL
        if (!SSL_CTX_load_verify_locations(ctx.get(), i.c_str(), path)) {
            const auto x = ERR_get_error();
            debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate location " <<
                   i << ": " << Security::ErrorString(x));
        }
#elif USE_GNUTLS
        const auto x = gnutls_certificate_set_x509_trust_file(ctx.get(), i.c_str(), GNUTLS_X509_FMT_PEM);
        if (x < 0) {
            debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting CA certificate location " <<
                   i << ": " << Security::ErrorString(x));
        }
#endif
    }

    if (!flags.tlsDefaultCa)
        return;

    if (const char *err = loadSystemTrustedCa(ctx)) {
        debugs(83, DBG_IMPORTANT, "WARNING: Ignoring error setting default trusted CA : " << err);
    }
}