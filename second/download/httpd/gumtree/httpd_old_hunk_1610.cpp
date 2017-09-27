    }
#endif
#endif

#ifdef LDAP_OPT_NETWORK_TIMEOUT
    if (st->connectionTimeout > 0) {
        timeOut.tv_sec = st->connectionTimeout;
    }

    if (st->connectionTimeout >= 0) {
        rc = apr_ldap_set_option(r->pool, ldc->ldap, LDAP_OPT_NETWORK_TIMEOUT,
                                 (void *)&timeOut, &(result));
        if (APR_SUCCESS != rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "LDAP: Could not set the connection timeout");
        }
    }
#endif

    return(rc);
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

    /* sanity check for NULL */
    if (!ldc) {
        return -1;
    }

