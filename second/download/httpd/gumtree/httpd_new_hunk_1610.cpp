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

/*
 * Replacement function for ldap_simple_bind_s() with a timeout.
 * To do this in a portable way, we have to use ldap_simple_bind() and 
 * ldap_result().
 *
 * Returns LDAP_SUCCESS on success; and an error code on failure
 */
static int uldap_simple_bind(util_ldap_connection_t *ldc, char *binddn,
                             char* bindpw, struct timeval *timeout)
{
    LDAPMessage *result;
    int rc;
    int msgid = ldap_simple_bind(ldc->ldap, binddn, bindpw);
    if (msgid == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() failed";
        /* -1 is LDAP_SERVER_DOWN in openldap, use something else */
        return LDAP_OTHER;
    }
    rc = ldap_result(ldc->ldap, msgid, 0, timeout, &result);
    if (rc == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() result retrieval failed";
        /* -1 is LDAP_SERVER_DOWN in openldap, use something else */
        rc = LDAP_OTHER;
    }
    else if (rc == 0) {
        ldc->reason = "LDAP: ldap_simple_bind() timed out";
        rc = LDAP_TIMEOUT;
    } else if (ldap_parse_result(ldc->ldap, result, &rc, NULL, NULL, NULL,
                                 NULL, 1) == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() parse result failed";
    }
    return rc;
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
    int new_connection = 0;
    util_ldap_state_t *st;

    /* sanity check for NULL */
    if (!ldc) {
        return -1;
    }

