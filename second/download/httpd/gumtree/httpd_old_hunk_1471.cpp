            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                          "Failed to enable the '%s' Accept Filter",
                          accf);
        }
#else
#ifdef APR_TCP_DEFER_ACCEPT
        rv = apr_socket_opt_set(s, APR_TCP_DEFER_ACCEPT, 1);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                              "Failed to enable APR_TCP_DEFER_ACCEPT");
        }
#endif
#endif
