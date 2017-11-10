static void option_set_cert(apr_pool_t *pool, LDAP *ldap,
                           const void *invalue, apr_ldap_err_t *result)
{
#if APR_HAS_LDAP_SSL
#if APR_HAS_LDAPSSL_CLIENT_INIT || APR_HAS_OPENLDAP_LDAPSDK
    apr_array_header_t *certs = (apr_array_header_t *)invalue;
    struct apr_ldap_opt_tls_cert_t *ents = (struct apr_ldap_opt_tls_cert_t *)certs->elts;
    int i = 0;
#endif

    /* Netscape/Mozilla/Solaris SDK */
#if APR_HAS_NETSCAPE_LDAPSDK || APR_HAS_SOLARIS_LDAPSDK || APR_HAS_MOZILLA_LDAPSDK
#if APR_HAS_LDAPSSL_CLIENT_INIT
    const char *nickname = NULL;
    const char *secmod = NULL;
    const char *key3db = NULL;
    const char *cert7db = NULL;
    const char *password = NULL;

    /* set up cert7.db, key3.db and secmod parameters */
    for (i = 0; i < certs->nelts; i++) {
        switch (ents[i].type) {
        case APR_LDAP_CA_TYPE_CERT7_DB:
            cert7db = ents[i].path;
            break;
        case APR_LDAP_CA_TYPE_SECMOD:
            secmod = ents[i].path;
            break;
        case APR_LDAP_CERT_TYPE_KEY3_DB:
            key3db = ents[i].path;
            break;
        case APR_LDAP_CERT_TYPE_NICKNAME:
            nickname = ents[i].path;
            password = ents[i].password;
            break;
        default:
            result->rc = -1;
            result->reason = "LDAP: The Netscape/Mozilla LDAP SDK only "
                "understands the CERT7, KEY3 and SECMOD "
                "file types.";
            break;
        }
        if (result->rc != LDAP_SUCCESS) {
            break;
        }
    }

    /* actually set the certificate parameters */
    if (result->rc == LDAP_SUCCESS) {
        if (nickname) {
            result->rc = ldapssl_enable_clientauth(ldap, "",
                                                   (char *)password,
                                                   (char *)nickname);
            if (result->rc != LDAP_SUCCESS) {
                result->reason = "LDAP: could not set client certificate: "
                                 "ldapssl_enable_clientauth() failed.";
                result->msg = ldap_err2string(result->rc);
            }
        }
        else if (secmod) {
            result->rc = ldapssl_advclientauth_init(cert7db, NULL,
                                                    key3db ? 1 : 0, key3db, NULL,
                                                    1, secmod, LDAPSSL_AUTH_CNCHECK);
            if (result->rc != LDAP_SUCCESS) {
                result->reason = "LDAP: ldapssl_advclientauth_init() failed.";
                result->msg = ldap_err2string(result->rc);
            }
        }
        else if (key3db) {
            result->rc = ldapssl_clientauth_init(cert7db, NULL,
                                                    1, key3db, NULL);
            if (result->rc != LDAP_SUCCESS) {
                result->reason = "LDAP: ldapssl_clientauth_init() failed.";
                result->msg = ldap_err2string(result->rc);
            }
        }
        else {
            result->rc = ldapssl_client_init(cert7db, NULL);
            if (result->rc != LDAP_SUCCESS) {
                result->reason = "LDAP: ldapssl_client_init() failed.";
                result->msg = ldap_err2string(result->rc);
            }
        }
    }
#else
    result->reason = "LDAP: SSL/TLS ldapssl_client_init() function not "
                     "supported by this Netscape/Mozilla/Solaris SDK. "
                     "Certificate authority file not set";
    result->rc = -1;
#endif
#endif

    /* Novell SDK */
#if APR_HAS_NOVELL_LDAPSDK
#if APR_HAS_LDAPSSL_CLIENT_INIT && APR_HAS_LDAPSSL_ADD_TRUSTED_CERT && APR_HAS_LDAPSSL_CLIENT_DEINIT
    /* The Novell library cannot support per connection certificates. Error
     * out if the ldap handle is provided.
     */
    if (ldap) {
        result->rc = -1;
        result->reason = "LDAP: The Novell LDAP SDK cannot support the setting "
                         "of certificates or keys on a per connection basis.";
    }
    /* Novell's library needs to be initialised first */
    else {
        result->rc = ldapssl_client_init(NULL, NULL);
        if (result->rc != LDAP_SUCCESS) {
            result->msg = ldap_err2string(result-> rc);
            result->reason = apr_pstrdup(pool, "LDAP: Could not "
                                         "initialize SSL");
        }
    }
    /* set one or more certificates */
    for (i = 0; LDAP_SUCCESS == result->rc && i < certs->nelts; i++) {
        /* Novell SDK supports DER or BASE64 files. */
        switch (ents[i].type) {
        case APR_LDAP_CA_TYPE_DER:
            result->rc = ldapssl_add_trusted_cert((void *)ents[i].path,
                                                  LDAPSSL_CERT_FILETYPE_DER);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_CA_TYPE_BASE64:
            result->rc = ldapssl_add_trusted_cert((void *)ents[i].path,
                                                  LDAPSSL_CERT_FILETYPE_B64);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_CERT_TYPE_DER:
            result->rc = ldapssl_set_client_cert((void *)ents[i].path,
                                                 LDAPSSL_CERT_FILETYPE_DER,
                                                 (void*)ents[i].password);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_CERT_TYPE_BASE64: 
            result->rc = ldapssl_set_client_cert((void *)ents[i].path,
                                                 LDAPSSL_CERT_FILETYPE_B64,
                                                 (void*)ents[i].password);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_CERT_TYPE_PFX: 
            result->rc = ldapssl_set_client_cert((void *)ents[i].path,
                                                 LDAPSSL_FILETYPE_P12,
                                                 (void*)ents[i].password);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_KEY_TYPE_DER:
            result->rc = ldapssl_set_client_private_key((void *)ents[i].path,
                                                        LDAPSSL_CERT_FILETYPE_DER,
                                                        (void*)ents[i].password);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_KEY_TYPE_BASE64:
            result->rc = ldapssl_set_client_private_key((void *)ents[i].path,
                                                        LDAPSSL_CERT_FILETYPE_B64,
                                                        (void*)ents[i].password);
            result->msg = ldap_err2string(result->rc);
            break;
        case APR_LDAP_KEY_TYPE_PFX:
            result->rc = ldapssl_set_client_private_key((void *)ents[i].path,
                                                        LDAPSSL_FILETYPE_P12,
                                                        (void*)ents[i].password);
            result->msg = ldap_err2string(result->rc);
            break;
        default:
            result->rc = -1;
            result->reason = "LDAP: The Novell LDAP SDK only understands the "
                "DER and PEM (BASE64) file types.";
            break;
        }
        if (result->rc != LDAP_SUCCESS) {
            break;
        }
    }
#else
    result->reason = "LDAP: ldapssl_client_init(), "
                     "ldapssl_add_trusted_cert() or "
                     "ldapssl_client_deinit() functions not supported "
                     "by this Novell SDK. Certificate authority file "
                     "not set";
    result->rc = -1;
#endif
#endif

    /* OpenLDAP SDK */
#if APR_HAS_OPENLDAP_LDAPSDK
#ifdef LDAP_OPT_X_TLS_CACERTFILE
    /* set one or more certificates */
    /* FIXME: make it support setting directories as well as files */
    for (i = 0; i < certs->nelts; i++) {
        /* OpenLDAP SDK supports BASE64 files. */
        switch (ents[i].type) {
        case APR_LDAP_CA_TYPE_BASE64:
            result->rc = ldap_set_option(ldap, LDAP_OPT_X_TLS_CACERTFILE,
             