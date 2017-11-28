static bool
tryTlsAnonymous()
{
    if (!loadTlsParameters())
        return false;

    // put the anonymous credentials to the current session
    int x;
    if ((x = gnutls_credentials_set(Transport::Config.session, GNUTLS_CRD_ANON, Transport::Config.anonCredentials)) != GNUTLS_E_SUCCESS) {
        std::cerr << "ERROR: Anonymous TLS credentials setup failed (" << x << ") " << std::endl;
        gnutls_perror(x);
        return false;
    }

    return doTlsHandshake("Anonymous");
}