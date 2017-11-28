void
Transport::ShutdownTls()
{
#if USE_GNUTLS
    if (!Config.tlsEnabled)
        return;

    debugVerbose(3, "Shutting down TLS library...");

    // release any existing session and credentials
    gnutls_deinit(Config.session);
    gnutls_anon_free_client_credentials(Config.anonCredentials);
    gnutls_certificate_free_credentials(Config.certCredentials);

    // NP: gnutls init is re-entrant and lock-counted with deinit but not thread safe.
    gnutls_global_deinit();
    Config.tlsEnabled = false;
#endif
}