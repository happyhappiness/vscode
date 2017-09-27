            }
            bytes_in_brigade += bucket->length;
            if (!APR_BUCKET_IS_FILE(bucket)) {
                non_file_bytes_in_brigade += bucket->length;
            }
        }
    }

    if (non_file_bytes_in_brigade >= THRESHOLD_MAX_BUFFER) {
        /* ### Writing the entire brigade may be excessive; we really just
         * ### need to send enough data to be under THRESHOLD_MAX_BUFFER.
         */
        rv = send_brigade_blocking(net->client_socket, bb,
                                   &(ctx->bytes_written), c);
        if (rv != APR_SUCCESS) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
        }
    }
    else if (bytes_in_brigade >= THRESHOLD_MIN_WRITE) {
        rv = send_brigade_nonblocking(net->client_socket, bb,
                                      &(ctx->bytes_written), c);
        if ((rv != APR_SUCCESS) && (!APR_STATUS_IS_EAGAIN(rv))) {
            /* The client has aborted the connection */
            c->aborted = 1;
            return rv;
