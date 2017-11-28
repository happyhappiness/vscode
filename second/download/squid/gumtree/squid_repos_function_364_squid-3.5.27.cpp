int
ldap_set_ssl_defaults(struct main_args *margs)
{
#if HAVE_OPENLDAP || HAVE_LDAPSSL_CLIENT_INIT
    int rc = 0;
#endif
#if HAVE_OPENLDAP
    int val;
#elif HAVE_LDAPSSL_CLIENT_INIT
    char *ssl_certdbpath = NULL;
#endif

#if HAVE_OPENLDAP
    if (!margs->rc_allow) {
        char *ssl_cacertfile = NULL;
        int free_path;
        debug((char *) "%s| %s: DEBUG: Enable server certificate check for ldap server.\n", LogTime(), PROGRAM);
        val = LDAP_OPT_X_TLS_DEMAND;
        rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &val);
        if (rc != LDAP_SUCCESS) {
            error((char *) "%s| %s: ERROR: Error while setting LDAP_OPT_X_TLS_REQUIRE_CERT DEMAND for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
            return rc;
        }
        ssl_cacertfile = getenv("TLS_CACERTFILE");
        free_path = 0;
        if (!ssl_cacertfile) {
            ssl_cacertfile = xstrdup("/etc/ssl/certs/cert.pem");
            free_path = 1;
        }
        debug((char *) "%s| %s: DEBUG: Set certificate file for ldap server to %s.(Changeable through setting environment variable TLS_CACERTFILE)\n", LogTime(), PROGRAM, ssl_cacertfile);
        rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, ssl_cacertfile);
        if (ssl_cacertfile && free_path) {
            xfree(ssl_cacertfile);
        }
        if (rc != LDAP_OPT_SUCCESS) {
            error((char *) "%s| %s: ERROR: Error while setting LDAP_OPT_X_TLS_CACERTFILE for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
            return rc;
        }
    } else {
        debug((char *) "%s| %s: DEBUG: Disable server certificate check for ldap server.\n", LogTime(), PROGRAM);
        val = LDAP_OPT_X_TLS_ALLOW;
        rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &val);
        if (rc != LDAP_SUCCESS) {
            error((char *) "%s| %s: ERROR: Error while setting LDAP_OPT_X_TLS_REQUIRE_CERT ALLOW for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
            return rc;
        }
    }
#elif HAVE_LDAPSSL_CLIENT_INIT
    /*
     *  Solaris SSL ldap calls require path to certificate database
     */
    /*
     * rc = ldapssl_client_init( ssl_certdbpath, NULL );
     * rc = ldapssl_advclientauth_init( ssl_certdbpath, NULL , 0 , NULL, NULL, 0, NULL, 2);
     */
    ssl_certdbpath = getenv("SSL_CERTDBPATH");
    if (!ssl_certdbpath) {
        ssl_certdbpath = xstrdup("/etc/certs");
    }
    debug((char *) "%s| %s: DEBUG: Set certificate database path for ldap server to %s.(Changeable through setting environment variable SSL_CERTDBPATH)\n", LogTime(), PROGRAM, ssl_certdbpath);
    if (!margs->rc_allow) {
        rc = ldapssl_advclientauth_init(ssl_certdbpath, NULL, 0, NULL, NULL, 0, NULL, 2);
    } else {
        rc = ldapssl_advclientauth_init(ssl_certdbpath, NULL, 0, NULL, NULL, 0, NULL, 0);
        debug((char *) "%s| %s: DEBUG: Disable server certificate check for ldap server.\n", LogTime(), PROGRAM);
    }
    xfree(ssl_certdbpath);
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error while setting SSL for ldap server: %s\n", LogTime(), PROGRAM, ldapssl_err2string(rc));
        return rc;
    }
#else
    error((char *) "%s| %s: ERROR: SSL not supported by ldap library\n", LogTime(), PROGRAM);
#endif
    return LDAP_SUCCESS;
}