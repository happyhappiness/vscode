     *     then save the rest in ctx->buffered_bb.
     */

    if (new_bb == NULL) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if (APR_STATUS_IS_EAGAIN(rv)) {
            rv = APR_SUCCESS;
        }
        else if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, rv, c,
                          "core_output_filter: writing data to the network");
            c->aborted = 1;
        }
        setaside_remaining_output(f, ctx, bb, c);
        return rv;
    }

    bytes_in_brigade = 0;
    non_file_bytes_in_brigade = 0;
    eor_buckets_in_brigade = 0;
    morphing_bucket_in_brigade = 0;
