static int uldap_connection_init(request_rec *r,
                                 util_ldap_connection_t *ldc)
{
    int rc = 0, ldap_option = 0;
    int version  = LDAP_VERSION3;
    apr_ldap_err_t *result = NULL;
#ifdef LDAP_OPT_NETWORK_TIMEOUT
    struct timeval connectionTimeout = {10,0};    /* 10 second connection timeout */
#endif
    util_ldap_state_t *st =
        (util_ldap_state_t *)ap_get_module_config(r->server->module_config,
        &ldap_module);

    /* Since the host will include a port if the default port is not used,
     * always specify the default ports for the port parameter.  This will
     * allow a host string that contains multiple hosts the ability to mix
     * some hosts with ports and some without. All hosts which do not
     * specify a port will use the default port.
     */
    apr_ldap_init(r->pool, &(ldc->ldap),
                  ldc->host,
                  APR_LDAP_SSL == ldc->secure ? LDAPS_PORT : LDAP_PORT,
                  APR_LDAP_NONE,
                  &(result));

    if (NULL == result) {
        /* something really bad happened */
        ldc->bound = 0;
        if (NULL == ldc->reason) {
            ldc->reason = "LDAP: ldap initialization failed";
        }
        return(APR_EGENERAL);
    }

    if (result->rc) {
        ldc->reason = result->reason;
        ldc->bound = 0;
        return result->rc;
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

    /* Now that we have an ldap struct, add it to the referral list for rebinds. */
    rc = apr_ldap_rebind_add(ldc->pool, ldc->ldap, ldc->binddn, ldc->bindpw);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "LDAP: Unable to add rebind cross reference entry. Out of memory?");
        uldap_connection_unbind(ldc);
        ldc->reason = "LDAP: Unable to add rebind cross reference entry.";
        return(rc);
    }

    /* always default to LDAP V3 */
    ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION, &version);

    /* set client certificates */
    if (!apr_is_empty_array(ldc->client_certs)) {
        apr_ldap_set_option(r->pool, ldc->ldap, APR_LDAP_OPT_TLS_CERT,
                            ldc->client_certs, &(result));
        if (LDAP_SUCCESS != result->rc) {
            uldap_connection_unbind( ldc );
            ldc->reason = result->reason;
            return(result->rc);
        }
    }

    /* switch on SSL/TLS */
    if (APR_LDAP_NONE != ldc->secure) {
        apr_ldap_set_option(r->pool, ldc->ldap,
                            APR_LDAP_OPT_TLS, &ldc->secure, &(result));
        if (LDAP_SUCCESS != result->rc) {
            uldap_connection_unbind( ldc );
            ldc->reason = result->reason;
            return(result->rc);
        }
    }

    /* Set the alias dereferencing option */
    ldap_option = ldc->deref;
    ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &ldap_option);

    /* Set options for rebind and referrals. */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "LDAP: Setting referrals to %s.",
                 ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"));
    apr_ldap_set_option(r->pool, ldc->ldap,
                        APR_LDAP_OPT_REFERRALS,
                        (void *)((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ?
                                 LDAP_OPT_ON : LDAP_OPT_OFF),
                        &(result));
    if (result->rc != LDAP_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Unable to set LDAP_OPT_REFERRALS option to %s: %d.",
                     ((ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) ? "On" : "Off"),
                     result->rc);
        result->reason = "Unable to set LDAP_OPT_REFERRALS.";
        ldc->reason = result->reason;
        uldap_connection_unbind(ldc);
        return(result->rc);
    }

    if ((ldc->ReferralHopLimit != AP_LDAP_HOPLIMIT_UNSET) && ldc->ChaseReferrals == AP_LDAP_CHASEREFERRALS_ON) {
        /* Referral hop limit - only if referrals are enabled and a hop limit is explicitly requested */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Setting referral hop limit to %d.",
                     ldc->ReferralHopLimit);
        apr_ldap_set_option(r->pool, ldc->ldap,
                            APR_LDAP_OPT_REFHOPLIMIT,
                            (void *)&ldc->ReferralHopLimit,
                            &(result));
        if (result->rc != LDAP_SUCCESS) {
          ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                       "Unable to set LDAP_OPT_REFHOPLIMIT option to %d: %d.",
                       ldc->ReferralHopLimit,
                       result->rc);
          result->reason = "Unable to set LDAP_OPT_REFHOPLIMIT.";
          ldc->reason = result->reason;
          uldap_connection_unbind(ldc);
          return(result->rc);
        }
    }

/*XXX All of the #ifdef's need to be removed once apr-util 1.2 is released */
#ifdef APR_LDAP_OPT_VERIFY_CERT
    apr_ldap_set_option(r->pool, ldc->ldap, APR_LDAP_OPT_VERIFY_CERT,
                        &(st->verify_svr_cert), &(result));
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
        connectionTimeout.tv_sec = st->connectionTimeout;
    }

    if (st->connectionTimeout >= 0) {
        rc = apr_ldap_set_option(r->pool, ldc->ldap, LDAP_OPT_NETWORK_TIMEOUT,
                                 (void *)&connectionTimeout, &(result));
        if (APR_SUCCESS != rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "LDAP: Could not set the connection timeout");
        }
    }
#endif

#ifdef LDAP_OPT_TIMEOUT
    /*
     * LDAP_OPT_TIMEOUT is not portable, but it influences all synchronous ldap
     * function calls and not just ldap_search_ext_s(), which accepts a timeout
     * parameter.
     * XXX: It would be possible to simulate LDAP_OPT_TIMEOUT by replacing all
     * XXX: synchronous ldap function calls with asynchronous calls and using
     * XXX: ldap_result() with a timeout.
     */
    if (st->opTimeout) {
        rc = apr_ldap_set_option(r->pool, ldc->ldap, LDAP_OPT_TIMEOUT,
                                 st->opTimeout, &(result));
        if (APR_SUCCESS != rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "LDAP: Could not set LDAP_OPT_TIMEOUT");
        }
    }
#endif

    return(rc);
}