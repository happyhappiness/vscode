static void ap_apply_accept_filter(apr_pool_t *p, ap_listen_rec *lis,
                                           server_rec *server)
{
    apr_socket_t *s = lis->sd;
    const char *accf;
    apr_status_t rv;
    const char *proto;

    proto = lis->protocol;

    if (!proto) {
        proto = ap_get_server_protocol(server);
    }


    accf = find_accf_name(server, proto);

    if (accf) {
#if APR_HAS_SO_ACCEPTFILTER
        /* In APR 1.x, the 2nd and 3rd parameters are char * instead of 
         * const char *, so make a copy of those args here.
         */
        rv = apr_socket_accept_filter(s, apr_pstrdup(p, accf),
                                      apr_pstrdup(p, ""));
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p, APLOGNO(00075)
                          "Failed to enable the '%s' Accept Filter",
                          accf);
        }
#else
        rv = apr_socket_opt_set(s, APR_TCP_DEFER_ACCEPT, 30);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_ENOTIMPL(rv)) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, rv, p, APLOGNO(00076)
                              "Failed to enable APR_TCP_DEFER_ACCEPT");
        }
#endif
    }
}