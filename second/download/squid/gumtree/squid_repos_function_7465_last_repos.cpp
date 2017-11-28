Security::ContextPointer
Security::PeerOptions::createBlankContext() const
{
    Security::ContextPointer ctx;
#if USE_OPENSSL
    Ssl::Initialize();

#if HAVE_OPENSSL_TLS_CLIENT_METHOD
    SSL_CTX *t = SSL_CTX_new(TLS_client_method());
#else
    SSL_CTX *t = SSL_CTX_new(SSLv23_client_method());
#endif
    if (!t) {
        const auto x = ERR_get_error();
        fatalf("Failed to allocate TLS client context: %s\n", Security::ErrorString(x));
    }
    ctx = convertContextFromRawPtr(t);

#elif USE_GNUTLS
    // Initialize for X.509 certificate exchange
    gnutls_certificate_credentials_t t;
    if (const int x = gnutls_certificate_allocate_credentials(&t)) {
        fatalf("Failed to allocate TLS client context: %s\n", Security::ErrorString(x));
    }
    ctx = convertContextFromRawPtr(t);

#else
    debugs(83, 1, "WARNING: Failed to allocate TLS client context: No TLS library");

#endif

    return ctx;
}