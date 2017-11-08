static int ap_process_http_connection(conn_rec *c)
{
    request_rec *r;
    int csd_set = 0;
    apr_socket_t *csd = NULL;

    /*
     * Read and process each request found on our connection
     * until no requests are left or we decide to close.
     */
 
    ap_update_child_status(c->sbh, SERVER_BUSY_READ, NULL);
    while ((r = ap_read_request(c)) != NULL) {

        c->keepalive = AP_CONN_UNKNOWN;
        /* process the request if it was read without error */
 
        ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, r);
        if (r->status == HTTP_OK)
            ap_process_request(r);
 
        if (ap_extended_status)
            ap_increment_counts(c->sbh, r);
 
        if (c->keepalive != AP_CONN_KEEPALIVE || c->aborted)
            break;
 
        ap_update_child_status(c->sbh, SERVER_BUSY_KEEPALIVE, r);
        apr_pool_destroy(r->pool);
 
        if (ap_graceful_stop_signalled())
            break;
        /* Go straight to select() to wait for the next request */
        if (!csd_set) {
            csd = ap_get_module_config(c->conn_config, &core_module);
            csd_set = 1;
        }
        apr_socket_opt_set(csd, APR_INCOMPLETE_READ, 1);
    }
 
    return OK;
}