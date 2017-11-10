static int ap_process_http_async_connection(conn_rec *c)
{
    request_rec *r;
    conn_state_t *cs = c->cs;

    AP_DEBUG_ASSERT(cs->state == CONN_STATE_READ_REQUEST_LINE);

    while (cs->state == CONN_STATE_READ_REQUEST_LINE) {
        ap_update_child_status(c->sbh, SERVER_BUSY_READ, NULL);

        if ((r = ap_read_request(c))) {

            c->keepalive = AP_CONN_UNKNOWN;
            /* process the request if it was read without error */

            ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, r);
            if (r->status == HTTP_OK)
                ap_process_request(r);

            if (ap_extended_status)
                ap_increment_counts(c->sbh, r);

            if (c->keepalive != AP_CONN_KEEPALIVE || c->aborted
                    || ap_graceful_stop_signalled()) {
                cs->state = CONN_STATE_LINGER;
            }
            else if (!c->data_in_input_filters) {
                cs->state = CONN_STATE_CHECK_REQUEST_LINE_READABLE;
            }

            /* else we are pipelining.  Stay in READ_REQUEST_LINE state
             *  and stay in the loop
             */

            apr_pool_destroy(r->pool);
        }
        else {   /* ap_read_request failed - client may have closed */
            cs->state = CONN_STATE_LINGER;
        }
    }

    return OK;
}