

    accf = find_accf_name(server, proto);

    if (accf) {
#if APR_HAS_SO_ACCEPTFILTER
        rv = apr_socket_accept_filter(s, apr_pstrdup(p, accf),
                                      apr_pstrdup(p,""));
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p, APLOGNO(00075)
                          "Failed to enable the '%s' Accept Filter",
                          accf);
        }
#else
