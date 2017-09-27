    r->output_filters = c->output_filters;
    r->proto_output_filters = c->output_filters;
    r->input_filters = c->input_filters;
    r->proto_input_filters = c->input_filters;
/*    r->sent_bodyct = 1;*/

    do { /* Loop until done (one side closes the connection, or an error) */
        rv = apr_pollset_poll(pollset, -1, &pollcnt, &signalled);
        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rv)) {
                continue;
            }
            apr_socket_close(sock);
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01023) "error apr_poll()");
            return HTTP_INTERNAL_SERVER_ERROR;
