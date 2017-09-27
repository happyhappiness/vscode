        ctx->tmp_flush_bb = apr_brigade_split_ex(bb, flush_upto,
                                                 ctx->tmp_flush_bb);
        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
        }
        APR_BRIGADE_CONCAT(bb, ctx->tmp_flush_bb);
    }

    if (bytes_in_brigade >= THRESHOLD_MIN_WRITE) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
        }
    }

    setaside_remaining_output(f, ctx, bb, c);
