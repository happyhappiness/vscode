void
Security::PeerOptions::updateSessionOptions(Security::SessionPointer &s)
{
#if USE_OPENSSL
    // 'options=' value being set to session is a GnuTLS specific thing.
#elif USE_GNUTLS
    int x;
    SBuf errMsg;
    if (!parsedOptions) {
        debugs(83, 5, "set GnuTLS default priority/options for session=" << s);
        x = gnutls_set_default_priority(s.get());
        static const SBuf defaults("default");
        errMsg = defaults;
    } else {
        debugs(83, 5, "set GnuTLS options '" << sslOptions << "' for session=" << s);
        x = gnutls_priority_set(s.get(), parsedOptions.get());
        errMsg = sslOptions;
    }

    if (x != GNUTLS_E_SUCCESS) {
        debugs(83, DBG_IMPORTANT, "ERROR: Failed to set TLS options (" << errMsg << "). error: " << Security::ErrorString(x));
    }
#endif
}