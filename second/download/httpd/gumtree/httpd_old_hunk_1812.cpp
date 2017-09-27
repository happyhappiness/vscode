        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                          "Failed to enable the '%s' Accept Filter",
                          accf);
        }
#else
#ifdef APR_TCP_DEFER_ACCEPT
        rv = apr_socket_opt_set(s, APR_TCP_DEFER_ACCEPT, 30);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p,
                              "Failed to enable APR_TCP_DEFER_ACCEPT");
        }
#endif
#endif
    }
}

static apr_status_t close_listeners_on_exec(void *v)
{
    ap_close_listeners();
    return APR_SUCCESS;
}

static const char *alloc_listener(process_rec *process, char *addr,
                                  apr_port_t port, const char* proto)
{
    ap_listen_rec **walk, *last;
    apr_status_t status;
    apr_sockaddr_t *sa;
    int found_listener = 0;

