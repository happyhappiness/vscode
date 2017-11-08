static int ap_process_http_sync_connection(conn_rec *c)
{
    request_rec *r;
    conn_state_t *cs = c->cs;
    apr_socket_t *csd = NULL;
    int mpm_state = 0;

    /*
     * Read and process each request found on our connection
     * until no requests are left or we decide to close.
     */

    ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_READ, c);
    while ((r = ap_read_request(c)) != NULL) {
        apr_interval_time_t keep_alive_timeout = r->server->keep_alive_timeout;

        /* To preserve legacy behaviour, use the keepalive timeout from the
         * base server (first on this IP:port) when none is explicitly
         * configured on this server.
         */
        if (!r->server->keep_alive_timeout_set) {
            keep_alive_timeout = c->base_server->keep_alive_timeout;
        }

        c->keepalive = AP_CONN_UNKNOWN;
        /* process the request if it was read without error */

        ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, r);
        if (r->status == HTTP_OK) {
            if (cs)
                cs->state = CONN_STATE_HANDLER;
            ap_process_request(r);
            /* After the call to ap_process_request, the
             * request pool will have been deleted.  We set
             * r=NULL here to ensure that any dereference
             * of r that might be added later in this function
             * will result in a segfault immediately instead
             * of nondeterministic failures later.
             */
            r = NULL;
        }

        if (c->keepalive != AP_CONN_KEEPALIVE || c->aborted)
            break;

        ap_update_child_status(c->sbh, SERVER_BUSY_KEEPALIVE, NULL);

        if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            break;
        }

        if (mpm_state == AP_MPMQ_STOPPING) {
          break;
        }

        if (!csd) {
            csd = ap_get_conn_socket(c);
        }
        apr_socket_opt_set(csd, APR_INCOMPLETE_READ, 1);
        apr_socket_timeout_set(csd, keep_alive_timeout);
        /* Go straight to select() to wait for the next request */
    }

    return OK;
}