     */
    rc = apr_ldap_ssl_init(p,
                      NULL,
                      0,
                      &(result_err));
    if (APR_SUCCESS == rc) {
        rc = apr_ldap_set_option(ptemp, NULL, APR_LDAP_OPT_TLS_CERT,
                                 (void *)st->global_certs, &(result_err));
    }

    if (APR_SUCCESS == rc) {
        st->ssl_supported = 1;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
