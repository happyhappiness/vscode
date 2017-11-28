static bool
loadTlsParameters()
{
    const char *err = NULL;
    int x;
    if ((x = gnutls_priority_set_direct(Transport::Config.session, Transport::Config.params, &err)) != GNUTLS_E_SUCCESS) {
        if (x == GNUTLS_E_INVALID_REQUEST)
            std::cerr << "ERROR: Syntax error at: " << err << std::endl;
        gnutls_perror(x);
        return false;
    }
    return true;
}