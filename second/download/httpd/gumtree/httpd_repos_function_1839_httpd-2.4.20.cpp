static int ap_process_http_async_connection(conn_rec *c)
{
    request_rec *r;
    conn_state_t *cs = c->cs;

    AP_DEBUG_ASSERT(cs != NULL);
    AP_DEBUG_ASSERT(cs->state == CONN_STATE_READ_REQUEST_LINE);

    while (cs->state == CONN_STATE_READ_REQUEST_LINE) {
        ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_READ, c);

        if ((r = ap_read_request(c))) {

            c->keepalive = AP_CONN_UNKNOWN;
            /* process the request if it was read without error */

            ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, r);
            if (r->status == HTTP_OK) {
                cs->state = CONN_STATE_HANDLER;
                ap_process_async_request(r);
                /* After the call to ap_process_request, the
                 * request pool may have been deleted.  We set
                 * r=NULL here to ensure that any dereference
                 * of r that might be added later in this function
                 * will result in a segfault immediately instead
                 * of nondeterministic failures later.
                 */
                r = NULL;
            }

            if (cs->state != CONN_STATE_WRITE_COMPLETION &&
                cs->state != CONN_STATE_SUSPENDED) {
                /* Something went wrong; close the connection */
                cs->state = CONN_STATE_LINGER;
            }
        }
        else {   /* ap_read_request failed - client may have closed */
            cs->state = CONN_STATE_LINGER;
        }
    }

    return OK;
}