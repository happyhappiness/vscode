static apr_status_t simple_io_process(simple_conn_t * scon)
{
    apr_status_t rv;
    simple_core_t *sc;
    conn_rec *c;
    conn_state_t *cs;

    if (scon->c->clogging_input_filters && !scon->c->aborted) {
        /* Since we have an input filter which 'cloggs' the input stream,
         * like mod_ssl, lets just do the normal read from input filters,
         * like the Worker MPM does.
         */
        ap_run_process_connection(scon->c);
        if (scon->c->cs->state != CONN_STATE_SUSPENDED) {
            scon->c->cs->state = CONN_STATE_LINGER;
        }
    }

    sc = scon->sc;
    c = scon->c;
    cs = c->cs;

    while (!c->aborted) {

        if (cs->pfd.reqevents != 0) {
            rv = apr_pollcb_remove(sc->pollcb, &cs->pfd);
            if (rv) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                             "simple_io_process: apr_pollcb_remove failure");
                /*AP_DEBUG_ASSERT(rv == APR_SUCCESS);*/
            }
            cs->pfd.reqevents = 0;
        }

        if (cs->state == CONN_STATE_READ_REQUEST_LINE) {
            if (!c->aborted) {
                ap_run_process_connection(c);
                /* state will be updated upon return
                 * fall thru to either wait for readability/timeout or
                 * do lingering close
                 */
            }
            else {
                cs->state = CONN_STATE_LINGER;
            }
        }

        if (cs->state == CONN_STATE_WRITE_COMPLETION) {
            ap_filter_t *output_filter = c->output_filters;
            while (output_filter->next != NULL) {
                output_filter = output_filter->next;
            }

            rv = output_filter->frec->filter_func.out_func(output_filter,
                                                           NULL);

            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                             "network write failure in core output filter");
                cs->state = CONN_STATE_LINGER;
            }
            else if (c->data_in_output_filters) {
                /* Still in WRITE_COMPLETION_STATE:
                 * Set a write timeout for this connection, and let the
                 * event thread poll for writeability.
                 */

                simple_register_timer(scon->sc,
                                      simple_io_timeout_cb,
                                      scon,
                                      scon->c->base_server !=
                                      NULL ? scon->c->base_server->
                                      timeout : ap_server_conf->timeout,
                                      scon->pool);

                cs->pfd.reqevents = APR_POLLOUT | APR_POLLHUP | APR_POLLERR;

                rv = apr_pollcb_add(sc->pollcb, &cs->pfd);

                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                                 ap_server_conf,
                                 "apr_pollcb_add: failed in write completion");
                    AP_DEBUG_ASSERT(rv == APR_SUCCESS);
                }
                return APR_SUCCESS;
            }
            else if (c->keepalive != AP_CONN_KEEPALIVE || c->aborted) {
                c->cs->state = CONN_STATE_LINGER;
            }
            else if (c->data_in_input_filters) {
                cs->state = CONN_STATE_READ_REQUEST_LINE;
            }
            else {
                cs->state = CONN_STATE_CHECK_REQUEST_LINE_READABLE;
            }
        }

        if (cs->state == CONN_STATE_LINGER) {
            ap_lingering_close(c);
            apr_pool_destroy(scon->pool);
            return APR_SUCCESS;
        }

        if (cs->state == CONN_STATE_CHECK_REQUEST_LINE_READABLE) {
            simple_register_timer(scon->sc,
                                  simple_io_timeout_cb,
                                  scon,
                                  scon->c->base_server !=
                                  NULL ? scon->c->base_server->
                                  timeout : ap_server_conf->timeout,
                                  scon->pool);

            cs->pfd.reqevents = APR_POLLIN;

            rv = apr_pollcb_add(sc->pollcb, &cs->pfd);

            if (rv) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                             "process_socket: apr_pollcb_add failure in read request line");
                AP_DEBUG_ASSERT(rv == APR_SUCCESS);
            }

            return APR_SUCCESS;
        }
    }

    ap_lingering_close(c);
    apr_pool_destroy(scon->pool);
    return APR_SUCCESS;
}