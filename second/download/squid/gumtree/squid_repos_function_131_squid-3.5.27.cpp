static int
verifyTlsCertificate(gnutls_session_t session)
{
    // XXX: 1) try to verify using DANE -> Secure Authenticated Connection

    // 2) try to verify using CA
    if (verifyByCA(session) == GNUTLS_E_SUCCESS) {
        std::cerr << "SUCCESS: CA verified Encrypted Connection" << std::endl;
        return GNUTLS_E_SUCCESS;
    }

    // 3) fails both is insecure, but show the results anyway.
    std::cerr << "WARNING: Insecure Connection" << std::endl;
    return GNUTLS_E_SUCCESS;
}