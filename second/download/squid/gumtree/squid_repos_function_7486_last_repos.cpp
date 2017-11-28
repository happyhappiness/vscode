Security::ContextPointer
Security::ServerOptions::createBlankContext() const
{
    Security::ContextPointer ctx;
#if USE_OPENSSL
    Ssl::Initialize();

#if HAVE_OPENSSL_SERVER_METHOD
    SSL_CTX *t = SSL_CTX_new(TLS_server_method());
#else
    SSL_CTX *t = SSL_CTX_new(SSLv23_server_method());
#endif
    if (!t) {
        const auto x = ERR_get_error();
        debugs(83, DBG_CRITICAL, "ERROR: Failed to allocate TLS server context: " << Security::ErrorString(x));
    }
    ctx = convertContextFromRawPtr(t);

#elif USE_GNUTLS
    // Initialize for X.509 certificate exchange
    gnutls_certificate_credentials_t t;
    if (const int x = gnutls_certificate_allocate_credentials(&t)) {
        debugs(83, DBG_CRITICAL, "ERROR: Failed to allocate TLS server context: " << Security::ErrorString(x));
    }
    ctx = convertContextFromRawPtr(t);

#else
    debugs(83, DBG_CRITICAL, "ERROR: Failed to allocate TLS server context: No TLS library");

#endif

    return ctx;
}