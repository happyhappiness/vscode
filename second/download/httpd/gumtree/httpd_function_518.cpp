static int core_pre_connection(conn_rec *c, void *csd)
{
    core_net_rec *net = apr_palloc(c->pool, sizeof(*net));

#ifdef AP_MPM_DISABLE_NAGLE_ACCEPTED_SOCK
    apr_status_t rv;

    /* BillS says perhaps this should be moved to the MPMs. Some OSes
     * allow listening socket attributes to be inherited by the
     * accept sockets which means this call only needs to be made
     * once on the listener
     */
    /* The Nagle algorithm says that we should delay sending partial
     * packets in hopes of getting more data.  We don't want to do
     * this; we are not telnet.  There are bad interactions between
     * persistent connections and Nagle's algorithm that have very severe
     * performance penalties.  (Failing to disable Nagle is not much of a
     * problem with simple HTTP.)
     */
    rv = apr_socket_opt_set(csd, APR_TCP_NODELAY, 1);
    if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
        /* expected cause is that the client disconnected already,
         * hence the debug level
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
                      "apr_socket_opt_set(APR_TCP_NODELAY)");
    }
#endif
    net->c = c;
    net->in_ctx = NULL;
    net->out_ctx = NULL;
    net->client_socket = csd;

    ap_set_module_config(net->c->conn_config, &core_module, csd);
    ap_add_input_filter_handle(ap_core_input_filter_handle, net, NULL, net->c);
    ap_add_output_filter_handle(ap_core_output_filter_handle, net, NULL, net->c);
    return DONE;
}