    net->c = c;
    net->in_ctx = NULL;
    net->out_ctx = NULL;
    net->client_socket = csd;

    ap_set_module_config(net->c->conn_config, &core_module, csd);
    ap_add_input_filter("CORE_IN", net, NULL, net->c);
    ap_add_output_filter("CORE", net, NULL, net->c);
    return DONE;
}

static void register_hooks(apr_pool_t *p)
{
    /* create_connection and install_transport_filters are
