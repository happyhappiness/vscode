        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            apr_brigade_cleanup(bb);
            c->aborted = 1;
            return rv;
        }
    }

    setaside_remaining_output(f, ctx, bb, c);
