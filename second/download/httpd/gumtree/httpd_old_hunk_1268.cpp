            APR_BRIGADE_CHECK_CONSISTENCY(bb);
            APR_BRIGADE_CHECK_CONSISTENCY(ctx->bb);
        }
    }
    else {
        /* Split a line into the passed-in brigade. */
        rv = apr_brigade_split_line(bb, ctx->bb, mode, bytes);

        if (rv) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, f->c,
                          "could not split line from buffered SSL brigade");
            ap_remove_input_filter(f);
            return rv;
