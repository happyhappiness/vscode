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

