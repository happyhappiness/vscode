static int core_pre_connection(conn_rec *c, void *csd)
{
    core_net_rec *net = apr_palloc(c->pool, sizeof(*net));

#ifdef AP_MPM_DISABLE_NAGLE_ACCEPTED_SOCK
    /* BillS says perhaps this should be moved to the MPMs. Some OSes
     * allow listening socket attributes to be inherited by the
     * accept sockets which means this call only needs to be made
     * once on the listener
     */
    ap_sock_disable_nagle(csd);
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