        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            c->aborted = 1;
            return rv;
        }
        APR_BRIGADE_CONCAT(bb, ctx->tmp_flush_bb);
    }

