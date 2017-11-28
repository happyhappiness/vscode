static bool
doTlsHandshake(const char *type)
{
    // setup the connection for TLS
    gnutls_transport_set_int(Transport::Config.session, conn);
    gnutls_handshake_set_timeout(Transport::Config.session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

    debugVerbose(2, type << " TLS handshake ... ");

    int ret = 0;
    do {
        ret = gnutls_handshake(Transport::Config.session);
    } while (ret < 0 && gnutls_error_is_fatal(ret) == 0);

    if (ret < 0) {
        std::cerr << "ERROR: " << type << " TLS Handshake failed (" << ret << ") "
                  << gnutls_alert_get_name(gnutls_alert_get(Transport::Config.session))
                  << std::endl;
        gnutls_perror(ret);
        gnutls_deinit(Transport::Config.session);
        return false;
    }

    char *desc = gnutls_session_get_desc(Transport::Config.session);
    debugVerbose(3, "TLS Session info: " << std::endl << desc << std::endl);
    gnutls_free(desc);
    return true;
}