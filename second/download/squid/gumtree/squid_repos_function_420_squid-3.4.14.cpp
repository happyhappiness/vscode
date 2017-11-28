static LDAP *
open_ldap_connection(const char *ldapServer, int port)
{
    LDAP *ld = NULL;
#if HAS_URI_SUPPORT
    if (strstr(ldapServer, "://") != NULL) {
        int rc = ldap_initialize(&ld, ldapServer);
        if (rc != LDAP_SUCCESS) {
            fprintf(stderr, "\nUnable to connect to LDAPURI:%s\n", ldapServer);
            exit(1);
        }
    } else
#endif
#if NETSCAPE_SSL
        if (sslpath) {
            if (!sslinit && (ldapssl_client_init(sslpath, NULL) != LDAP_SUCCESS)) {
                fprintf(stderr, "\nUnable to initialise SSL with cert path %s\n",
                        sslpath);
                exit(1);
            } else {
                ++sslinit;
            }
            if ((ld = ldapssl_init(ldapServer, port, 1)) == NULL) {
                fprintf(stderr, "\nUnable to connect to SSL LDAP server: %s port:%d\n",
                        ldapServer, port);
                exit(1);
            }
        } else
#endif
            if ((ld = ldap_init(ldapServer, port)) == NULL) {
                fprintf(stderr, "\nUnable to connect to LDAP server:%s port:%d\n",
                        ldapServer, port);
                exit(1);
            }
    if (connect_timeout)
        squid_ldap_set_connect_timeout(ld, connect_timeout);

#ifdef LDAP_VERSION3
    if (version == -1) {
        version = LDAP_VERSION3;
    }
    if (ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version) != LDAP_SUCCESS) {
        fprintf(stderr, "Could not set LDAP_OPT_PROTOCOL_VERSION %d\n",
                version);
        exit(1);
    }
    if (use_tls) {
#ifdef LDAP_OPT_X_TLS
        if (version != LDAP_VERSION3) {
            fprintf(stderr, "TLS requires LDAP version 3\n");
            exit(1);
        } else if (ldap_start_tls_s(ld, NULL, NULL) != LDAP_SUCCESS) {
            fprintf(stderr, "Could not Activate TLS connection\n");
            exit(1);
        }
#else
        fprintf(stderr, "TLS not supported with your LDAP library\n");
        exit(1);
#endif
    }
#endif
    squid_ldap_set_timelimit(ld, timelimit);
    squid_ldap_set_referrals(ld, !noreferrals);
    squid_ldap_set_aliasderef(ld, aliasderef);
    return ld;
}