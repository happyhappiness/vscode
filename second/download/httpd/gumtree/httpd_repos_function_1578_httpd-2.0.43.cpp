int util_ldap_connection_open(util_ldap_connection_t *ldc)
{
    int result = 0;
    int failures = 0;


start_over:
    if (failures++ > 10) {
	/* too many failures - leave */
        return result;
    }

    if (!ldc->ldap) {
        ldc->bound = 0;

	/* opening connection to LDAP server */
        if ((ldc->ldap = ldap_init(ldc->host, ldc->port)) == NULL) {
	    /* couldn't connect */
            ldc->reason = "ldap_init() failed";
            return -1;
        }

	/* add the cleanup to the pool */
        apr_pool_cleanup_register(ldc->pool, ldc,
                                  util_ldap_connection_destroy,
                                  apr_pool_cleanup_null);

        /* Set the alias dereferencing option */
#if LDAP_VERSION_MAX == 2
        ldc->ldap->ld_deref = ldc->deref;
#else
        result = ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &(ldc->deref));
        if (result != LDAP_SUCCESS) {
	    /* setting LDAP dereference option failed */
	    /* we ignore this error */
        }
#endif /* LDAP_VERSION_MAX */

#ifdef APU_HAS_LDAP_NETSCAPE_SSL
        if (ldc->netscapessl) {
            if (!ldc->certdb) {
		/* secure LDAP requested, but no CA cert defined */
                ldc->reason = "secure LDAP requested, but no CA cert defined";
                return -1;
            } else {
                result = ldapssl_install_routines(ldc->ldap);
                if (result != LDAP_SUCCESS) {
		    /* SSL initialisation failed */
                    ldc->reason = "ldapssl_install_routines() failed";
                    return result;
                }
                result = ldap_set_option(ldc->ldap, LDAP_OPT_SSL, LDAP_OPT_ON);
                if (result != LDAP_SUCCESS) {
		    /* SSL option failed */
                    ldc->reason = "ldap_set_option() failed trying to set LDAP_OPT_SSL";
                    return result;
                }
            }
        }
#endif /* APU_HAS_LDAP_NETSCAPE_SSL */

#ifdef APU_HAS_LDAP_STARTTLS
        if (ldc->starttls) {
            int version = LDAP_VERSION3;

            /* Also we have to set the connection to use protocol version 3,
             * since we're using TLS. */
            if ((result = ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION,
                                         &version)) != LDAP_SUCCESS) {
		/* setting LDAP version failed - ignore error */
            }

            /* 
             * In util_ldap_connection_find, we compare ldc->withtls to
             * sec->starttls to see if we have a cache match. On the off
             * chance that apache's config processing rotines set starttls to
             * some other true value besides 1, we set it to 1 here to ensure
             * that the comparison succeeds.
             */
            ldc->starttls = 1;

            result = ldap_start_tls_s(ldc->ldap, NULL, NULL);
            if (result != LDAP_SUCCESS) {
		/* start TLS failed */
		ldc->withtls = 0;
                ldc->reason = "ldap_start_tls_s() failed";
	        return result;
            }
            ldc->withtls = 1;
        } else {
            ldc->withtls = 0;
        }
#endif /* APU_HAS_LDAP_STARTTLS */
    }

    /* 
     * At this point the LDAP connection is guaranteed alive. If bound says
     * that we're bound already, we can just return.
     */
    if (ldc->bound) {
        ldc->reason = "LDAP connection open successful (already bound)";
        return LDAP_SUCCESS;
    }

    /* 
     * Now bind with the username/password provided by the
     * configuration. It will be an anonymous bind if no u/p was
     * provided. 
     */
    if ((result = ldap_simple_bind_s(ldc->ldap, ldc->binddn, ldc->bindpw))
        == LDAP_SERVER_DOWN) {
	/* couldn't connect - try again */
        ldc->reason = "ldap_simple_bind_s() failed with server down";
        goto start_over;
    }

    if (result != LDAP_SUCCESS) {
	/* LDAP fatal error occured */
        ldc->reason = "ldap_simple_bind_s() failed";
        return result;
    }

    /* note how we are bound */
    ldc->bound = 1;

    ldc->reason = "LDAP connection open successful";
    return LDAP_SUCCESS;
}