     */
    rv = apr_socket_opt_set(csd, APR_TCP_NODELAY, 1);
    if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
        /* expected cause is that the client disconnected already,
         * hence the debug level
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
                      "apr_socket_opt_set(APR_TCP_NODELAY)");
    }

    /* The core filter requires the timeout mode to be set, which
     * incidentally sets the socket to be nonblocking.  If this
     * is not initialized correctly, Linux - for example - will
     * be initially blocking, while Solaris will be non blocking
     * and any initial read will fail.
     */
    rv = apr_socket_timeout_set(csd, c->base_server->timeout);
    if (rv != APR_SUCCESS) {
        /* expected cause is that the client disconnected already */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rv, c,
                      "apr_socket_timeout_set");
    }

    net->c = c;
    net->in_ctx = NULL;
    net->out_ctx = NULL;
    net->client_socket = csd;

    ap_set_module_config(net->c->conn_config, &core_module, csd);
    ap_add_input_filter_handle(ap_core_input_filter_handle, net, NULL, net->c);
    ap_add_output_filter_handle(ap_core_output_filter_handle, net, NULL, net->c);
    return DONE;
}

static void register_hooks(apr_pool_t *p)
{
    /* create_connection and pre_connection should always be hooked
     * APR_HOOK_REALLY_LAST by core to give other modules the opportunity
     * to install alternate network transports and stop other functions 
     * from being run.
     */
    ap_hook_create_connection(core_create_conn, NULL, NULL,
                              APR_HOOK_REALLY_LAST);
    ap_hook_pre_connection(core_pre_connection, NULL, NULL,
                           APR_HOOK_REALLY_LAST);

    ap_hook_pre_config(core_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_post_config(core_post_config,NULL,NULL,APR_HOOK_REALLY_FIRST);
    ap_hook_translate_name(ap_core_translate,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_map_to_storage(core_map_to_storage,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_open_logs(ap_open_logs,NULL,NULL,APR_HOOK_REALLY_FIRST);
    ap_hook_child_init(ap_logs_child_init,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_handler(default_handler,NULL,NULL,APR_HOOK_REALLY_LAST);
    /* FIXME: I suspect we can eliminate the need for these do_nothings - Ben */
    ap_hook_type_checker(do_nothing,NULL,NULL,APR_HOOK_REALLY_LAST);
    ap_hook_fixups(core_override_type,NULL,NULL,APR_HOOK_REALLY_FIRST);
    ap_hook_create_request(core_create_req, NULL, NULL, APR_HOOK_MIDDLE);
    APR_OPTIONAL_HOOK(proxy, create_req, core_create_proxy_req, NULL, NULL,
                      APR_HOOK_MIDDLE);
    ap_hook_pre_mpm(ap_create_scoreboard, NULL, NULL, APR_HOOK_MIDDLE);

    /* register the core's insert_filter hook and register core-provided
     * filters
     */
    ap_hook_insert_filter(core_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);

