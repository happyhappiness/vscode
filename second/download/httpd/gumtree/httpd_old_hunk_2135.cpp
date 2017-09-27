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
