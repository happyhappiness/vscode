int
ldap_set_defaults(LDAP * ld)
{
    int val, rc = 0;
#if LDAP_OPT_NETWORK_TIMEOUT
    struct timeval tv;
#endif
    val = LDAP_VERSION3;
    rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &val);
    if (rc != LDAP_SUCCESS) {
        debug((char *) "%s| %s: DEBUG: Error while setting protocol version: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        return rc;
    }
    rc = ldap_set_option(ld, LDAP_OPT_REFERRALS, LDAP_OPT_OFF);
    if (rc != LDAP_SUCCESS) {
        debug((char *) "%s| %s: DEBUG: Error while setting referrals off: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        return rc;
    }
#if LDAP_OPT_NETWORK_TIMEOUT
    tv.tv_sec = CONNECT_TIMEOUT;
    tv.tv_usec = 0;
    rc = ldap_set_option(ld, LDAP_OPT_NETWORK_TIMEOUT, &tv);
    if (rc != LDAP_SUCCESS) {
        debug((char *) "%s| %s: DEBUG: Error while setting network timeout: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        return rc;
    }
#endif /* LDAP_OPT_NETWORK_TIMEOUT */
    return LDAP_SUCCESS;
}