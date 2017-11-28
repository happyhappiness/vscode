LDAP *
tool_ldap_open(struct main_args * margs, char *host, int port, char *ssl)
{
    LDAP *ld;
#ifdef HAVE_OPENLDAP
    LDAPURLDesc *url = NULL;
    char *ldapuri = NULL;
#endif
    int rc = 0;

    /*
     * Use ldap open here to check if TCP connection is possible. If possible use it.
     * (Not sure if this is the best way)
     */
#ifdef HAVE_OPENLDAP
    url = (LDAPURLDesc *) xmalloc(sizeof(*url));
    memset(url, 0, sizeof(*url));
#ifdef HAVE_LDAP_URL_LUD_SCHEME
    if (ssl)
        url->lud_scheme = xstrdup("ldaps");
    else
        url->lud_scheme = xstrdup("ldap");
#endif
    url->lud_host = xstrdup(host);
    url->lud_port = port;
#ifdef HAVE_LDAP_SCOPE_DEFAULT
    url->lud_scope = LDAP_SCOPE_DEFAULT;
#else
    url->lud_scope = LDAP_SCOPE_SUBTREE;
#endif
#ifdef HAVE_LDAP_URL_DESC2STR
    ldapuri = ldap_url_desc2str(url);
#elif defined(HAVE_LDAP_URL_PARSE)
    rc = ldap_url_parse(ldapuri, &url);
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error while parsing url: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        xfree(ldapuri);
        xfree(url);
        return NULL;
    }
#else
#error "No URL parsing function"
#endif
    safe_free(url);
    rc = ldap_initialize(&ld, ldapuri);
    xfree(ldapuri);
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error while initialising connection to ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        ldap_unbind(ld);
        ld = NULL;
        return NULL;
    }
#else
    ld = ldap_init(host, port);
#endif
    rc = ldap_set_defaults(margs, ld);
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error while setting default options for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        ldap_unbind(ld);
        ld = NULL;
        return NULL;
    }
    if (ssl) {
        /*
         * Try Start TLS first
         */
        debug((char *) "%s| %s: DEBUG: Set SSL defaults\n", LogTime(), PROGRAM);
        rc = ldap_set_ssl_defaults(margs);
        if (rc != LDAP_SUCCESS) {
            error((char *) "%s| %s: ERROR: Error while setting SSL default options for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
            ldap_unbind(ld);
            ld = NULL;
            return NULL;
        }
#ifdef HAVE_OPENLDAP
        /*
         *  Use tls if possible
         */
        rc = ldap_start_tls_s(ld, NULL, NULL);
        if (rc != LDAP_SUCCESS) {
            error((char *) "%s| %s: ERROR: Error while setting start_tls for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
            ldap_unbind(ld);
            ld = NULL;
            url = (LDAPURLDesc *) xmalloc(sizeof(*url));
            memset(url, 0, sizeof(*url));
#ifdef HAVE_LDAP_URL_LUD_SCHEME
            url->lud_scheme = xstrdup("ldaps");
#endif
            url->lud_host = xstrdup(host);
            url->lud_port = port;
#ifdef HAVE_LDAP_SCOPE_DEFAULT
            url->lud_scope = LDAP_SCOPE_DEFAULT;
#else
            url->lud_scope = LDAP_SCOPE_SUBTREE;
#endif
#ifdef HAVE_LDAP_URL_DESC2STR
            ldapuri = ldap_url_desc2str(url);
#elif defined(HAVE_LDAP_URL_PARSE)
            rc = ldap_url_parse(ldapuri, &url);
            if (rc != LDAP_SUCCESS) {
                error((char *) "%s| %s: ERROR: Error while parsing url: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
                xfree(ldapuri);
                xfree(url);
                return NULL;
            }
#else
#error "No URL parsing function"
#endif
            safe_free(url);
            rc = ldap_initialize(&ld, ldapuri);
            xfree(ldapuri);
            if (rc != LDAP_SUCCESS) {
                error((char *) "%s| %s: ERROR: Error while initialising connection to ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
                ldap_unbind(ld);
                ld = NULL;
                return NULL;
            }
            rc = ldap_set_defaults(margs, ld);
            if (rc != LDAP_SUCCESS) {
                error((char *) "%s| %s: ERROR: Error while setting default options for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
                ldap_unbind(ld);
                ld = NULL;
                return NULL;
            }
        }
#elif defined(HAVE_LDAPSSL_CLIENT_INIT)
        ld = ldapssl_init(host, port, 1);
        if (!ld) {
            error((char *) "%s| %s: ERROR: Error while setting SSL for ldap server: %s\n", LogTime(), PROGRAM, ldapssl_err2string(rc));
            ldap_unbind(ld);
            ld = NULL;
            return NULL;
        }
        rc = ldap_set_defaults(margs, ld);
        if (rc != LDAP_SUCCESS) {
            error((char *) "%s| %s: ERROR: Error while setting default options for ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
            ldap_unbind(ld);
            ld = NULL;
            return NULL;
        }
#else
        error((char *) "%s| %s: ERROR: SSL not supported by ldap library\n", LogTime(), PROGRAM);
#endif
    }
    return ld;
}