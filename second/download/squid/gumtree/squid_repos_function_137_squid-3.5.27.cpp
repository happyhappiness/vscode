bool
Transport::MaybeStartTls(const char *hostname)
{
#if USE_GNUTLS
    if (Config.tlsEnabled) {

        // Initialize TLS session
        gnutls_init(&Transport::Config.session, GNUTLS_CLIENT);

        if (Transport::Config.tlsAnonymous && !tryTlsAnonymous()) {
            gnutls_deinit(Config.session);
            return false;
        }

        if (!tryTlsCertificate(hostname)) {
            gnutls_deinit(Config.session);
            return false;
        }
    }
#endif
    return true;
}