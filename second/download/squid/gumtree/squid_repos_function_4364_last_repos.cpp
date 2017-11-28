static bool ldap_search_ok(const int result)
{
    if (result == LDAP_SUCCESS)
        return true;
    if (noreferrals && result == LDAP_PARTIAL_RESULTS) {
        /* Everything is fine. This is expected when referrals
         * are disabled.
         */
        return true;
    }
    std::cerr << PROGRAM_NAME << ": WARNING: LDAP search error '" <<
              ldap_err2string(result) << "'" << std::endl;
#if defined(NETSCAPE_SSL)
    if (sslpath && ((result == LDAP_SERVER_DOWN) || (result == LDAP_CONNECT_ERROR))) {
        int sslerr = PORT_GetError();
        std::cerr << PROGRAM_NAME << ": WARNING: SSL error " << sslerr << " (" <<
                  ldapssl_err2string(sslerr) << ")" << std::endl;
    }
#endif
    return false;
}