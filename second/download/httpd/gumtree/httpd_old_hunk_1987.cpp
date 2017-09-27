
    }

    return APR_SUCCESS;
}


/*
 * Connect to the LDAP server and binds. Does not connect if already
 * connected (i.e. ldc->ldap is non-NULL.) Does not bind if already bound.
 *
 * Returns LDAP_SUCCESS on success; and an error code on failure
 */
static int uldap_connection_open(request_rec *r,
                                 util_ldap_connection_t *ldc)
{
    int rc = 0;
    int failures = 0;
    int version  = LDAP_VERSION3;
    apr_ldap_err_t *result = NULL;
    struct timeval timeOut = {10,0};    /* 10 second connection timeout */
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);

    /* sanity check for NULL */
    if (!ldc) {
        return -1;
    }

    /* If the connection is already bound, return
    */
    if (ldc->bound)
    {
        ldc->reason = "LDAP: connection open successful (already bound)";
        return LDAP_SUCCESS;
    }

    /* create the ldap session handle
    */
    if (NULL == ldc->ldap)
    {
        /* Since the host will include a port if the default port is not used,
         * always specify the default ports for the port parameter.  This will
         * allow a host string that contains multiple hosts the ability to mix
         * some hosts with ports and some without. All hosts which do not
         * specify a port will use the default port.
         */
        apr_ldap_init(ldc->pool, &(ldc->ldap),
                      ldc->host,
                      APR_LDAP_SSL == ldc->secure ? LDAPS_PORT : LDAP_PORT,
                      APR_LDAP_NONE,
                      &(result));


        if (result != NULL && result->rc) {
            ldc->reason = result->reason;
        }

        if (NULL == ldc->ldap)
        {
            ldc->bound = 0;
            if (NULL == ldc->reason) {
                ldc->reason = "LDAP: ldap initialization failed";
            }
            else {
                ldc->reason = result->reason;
            }
            return(result->rc);
        }

        /* always default to LDAP V3 */
        ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION, &version);

        /* set client certificates */
        if (!apr_is_empty_array(ldc->client_certs)) {
            apr_ldap_set_option(ldc->pool, ldc->ldap, APR_LDAP_OPT_TLS_CERT,
                                ldc->client_certs, &(result));
            if (LDAP_SUCCESS != result->rc) {
                ldap_unbind_s(ldc->ldap);
                ldc->ldap = NULL;
                ldc->bound = 0;
                ldc->reason = result->reason;
                return(result->rc);
            }
        }

        /* switch on SSL/TLS */
        if (APR_LDAP_NONE != ldc->secure) {
            apr_ldap_set_option(ldc->pool, ldc->ldap,
                                APR_LDAP_OPT_TLS, &ldc->secure, &(result));
            if (LDAP_SUCCESS != result->rc) {
                ldap_unbind_s(ldc->ldap);
                ldc->ldap = NULL;
                ldc->bound = 0;
                ldc->reason = result->reason;
                return(result->rc);
            }
        }

        /* Set the alias dereferencing option */
        ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &(ldc->deref));

/*XXX All of the #ifdef's need to be removed once apr-util 1.2 is released */
#ifdef APR_LDAP_OPT_VERIFY_CERT
        apr_ldap_set_option(ldc->pool, ldc->ldap,
                            APR_LDAP_OPT_VERIFY_CERT, &(st->verify_svr_cert), &(result));
#else
#if defined(LDAPSSL_VERIFY_SERVER)
        if (st->verify_svr_cert) {
            result->rc = ldapssl_set_verify_mode(LDAPSSL_VERIFY_SERVER);
        }
        else {
            result->rc = ldapssl_set_verify_mode(LDAPSSL_VERIFY_NONE);
        }
#elif defined(LDAP_OPT_X_TLS_REQUIRE_CERT)
                /* This is not a per-connection setting so just pass NULL for the
                   Ldap connection handle */
        if (st->verify_svr_cert) {
                        int i = LDAP_OPT_X_TLS_DEMAND;
                        result->rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &i);
        }
        else {
                        int i = LDAP_OPT_X_TLS_NEVER;
                        result->rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &i);
        }
#endif
#endif

#ifdef LDAP_OPT_NETWORK_TIMEOUT
        if (st->connectionTimeout > 0) {
            timeOut.tv_sec = st->connectionTimeout;
        }

        if (st->connectionTimeout >= 0) {
            rc = apr_ldap_set_option(ldc->pool, ldc->ldap, LDAP_OPT_NETWORK_TIMEOUT,
                                     (void *)&timeOut, &(result));
            if (APR_SUCCESS != rc) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                                 "LDAP: Could not set the connection timeout");
            }
        }
#endif


    }


    /* loop trying to bind up to 10 times if LDAP_SERVER_DOWN error is
     * returned.  Break out of the loop on Success or any other error.
     *
