void
Transport::InitTls()
{
#if USE_GNUTLS
    debugVerbose(3, "Initializing TLS library...");
    // NP: gnutls init is re-entrant and lock-counted with deinit but not thread safe.
    if (gnutls_global_init() != GNUTLS_E_SUCCESS) {
        std::cerr << "FATAL ERROR: TLS Initialize failed: " << xstrerror() << std::endl;
        exit(1);
    }

    Config.tlsEnabled = true;

    // Initialize for anonymous TLS
    gnutls_anon_allocate_client_credentials(&Config.anonCredentials);

    // Initialize for X.509 certificate exchange
    gnutls_certificate_allocate_credentials(&Config.certCredentials);
    for (std::list<std::string>::const_iterator i = Config.caFiles.begin(); i != Config.caFiles.end(); ++i) {
        int x = gnutls_certificate_set_x509_trust_file(Config.certCredentials, (*i).c_str(), GNUTLS_X509_FMT_PEM);
        if (x < 0) {
            debugVerbose(3, "WARNING: Failed to load Certificate Authorities from " << *i);
        } else {
            debugVerbose(3, "Loaded " << x << " Certificate Authorities from " << *i);
        }
    }
    gnutls_certificate_set_verify_function(Config.certCredentials, verifyTlsCertificate);

    for (std::list<std::string>::const_iterator i = Config.certFiles.begin(); i != Config.certFiles.end(); ++i) {
        if (gnutls_certificate_set_x509_key_file(Transport::Config.certCredentials, (*i).c_str(), (*i).c_str(), GNUTLS_X509_FMT_PEM) != GNUTLS_E_SUCCESS) {
            debugVerbose(3, "WARNING: Failed to load Certificate from " << *i);
        } else {
            debugVerbose(3, "Loaded Certificate from " << *i);
        }
    }

#else
    std::cerr << "ERROR: TLS support not available." << std::endl;
#endif
}