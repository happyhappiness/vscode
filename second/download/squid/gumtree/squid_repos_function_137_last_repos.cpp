static bool
tryTlsCertificate(const char *hostname)
{
    gnutls_session_set_ptr(Transport::Config.session, (void *) hostname);
    gnutls_server_name_set(Transport::Config.session, GNUTLS_NAME_DNS, hostname, strlen(hostname));

    if (!loadTlsParameters())
        return false;

    // put the X.509 credentials to the current session
    gnutls_credentials_set(Transport::Config.session, GNUTLS_CRD_CERTIFICATE, Transport::Config.certCredentials);

    // setup the connection for TLS
    gnutls_transport_set_int(Transport::Config.session, conn);
    gnutls_handshake_set_timeout(Transport::Config.session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

    return doTlsHandshake("X.509");
}