static int
verifyByCA(gnutls_session_t session)
{
    /* read hostname */
    const char *hostname = static_cast<const char*>(gnutls_session_get_ptr(session));

    /* This verification function uses the trusted CAs in the credentials
     * structure. So you must have installed one or more CA certificates.
     */
    unsigned int status;
    if (gnutls_certificate_verify_peers3(session, hostname, &status) < 0) {
        std::cerr << "VERIFY peers failure";
        return GNUTLS_E_CERTIFICATE_ERROR;
    }

    gnutls_certificate_type_t type = gnutls_certificate_type_get(session);
    gnutls_datum_t out;
    if (gnutls_certificate_verification_status_print(status, type, &out, 0) < 0) {
        std::cerr << "VERIFY status failure";
        return GNUTLS_E_CERTIFICATE_ERROR;
    }

    std::cerr << "VERIFY DATUM: " << out.data << std::endl;
    gnutls_free(out.data);

    if (status != 0)        /* Certificate is not trusted */
        return GNUTLS_E_CERTIFICATE_ERROR;

    /* notify gnutls to continue handshake normally */
    return GNUTLS_E_SUCCESS;
}