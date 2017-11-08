static int process_echo_connection(conn_rec *c)
{
    apr_bucket_brigade *bb;
    apr_bucket *b;
    apr_status_t rv;
    EchoConfig *pConfig = ap_get_module_config(c->base_server->module_config,
                                               &echo_module);

    if (!pConfig->bEnabled) {
        return DECLINED;
    }
    
    bb = apr_brigade_create(c->pool, c->bucket_alloc);

    for ( ; ; ) {
        /* Get a single line of input from the client */
        if ((rv = ap_get_brigade(c->input_filters, bb, AP_MODE_GETLINE,
                                 APR_BLOCK_READ, 0) != APR_SUCCESS || 
             APR_BRIGADE_EMPTY(bb))) {
            apr_brigade_destroy(bb);
            break;
        }

        /* Make sure the data is flushed to the client */
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        ap_pass_brigade(c->output_filters, bb);    
    }
    return OK;
}