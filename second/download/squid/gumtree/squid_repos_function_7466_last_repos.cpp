Security::ContextPointer
Security::PeerOptions::createClientContext(bool setOptions)
{
    updateTlsVersionLimits();

    Security::ContextPointer t(createBlankContext());
    if (t) {
#if USE_OPENSSL
        // NP: GnuTLS uses 'priorities' which are set per-session instead.
        SSL_CTX_set_options(t.get(), (setOptions ? parsedOptions : 0));

        // XXX: temporary performance regression. c_str() data copies and prevents this being a const method
        Ssl::InitClientContext(t, *this, parsedFlags);
#endif
        updateContextNpn(t);
        updateContextCa(t);
        updateContextCrl(t);
    }

    return t;
}