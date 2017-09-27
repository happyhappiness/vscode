
    if (accf) {
#if APR_HAS_SO_ACCEPTFILTER
        rv = apr_socket_accept_filter(s, apr_pstrdup(p, accf),
                                      apr_pstrdup(p,""));
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                          "Failed to enable the '%s' Accept Filter",
                          accf);
        }
#else
        rv = apr_socket_opt_set(s, APR_TCP_DEFER_ACCEPT, 30);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                              "Failed to enable APR_TCP_DEFER_ACCEPT");
        }
#endif
    }
}

