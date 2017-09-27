    }

    /* Set the alias dereferencing option */
    ldap_option = ldc->deref;
    ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &ldap_option);

/*XXX All of the #ifdef's need to be removed once apr-util 1.2 is released */
#ifdef APR_LDAP_OPT_VERIFY_CERT
    apr_ldap_set_option(r->pool, ldc->ldap,
                        APR_LDAP_OPT_VERIFY_CERT, &(st->verify_svr_cert), &(result));
#else
#if defined(LDAPSSL_VERIFY_SERVER)
    if (st->verify_svr_cert) {
        result->rc = ldapssl_set_verify_mode(LDAPSSL_VERIFY_SERVER);
    }
    else {
