apr_status_t h2_conn_process(conn_rec *c, apr_socket_t *socket)
{
    AP_DEBUG_ASSERT(c);
    
    c->clogging_input_filters = 1;
    ap_process_connection(c, socket);
    
    return APR_SUCCESS;
}