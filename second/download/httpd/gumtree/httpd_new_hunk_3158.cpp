    }
    else {
        /* Split a line into the passed-in brigade. */
        rv = apr_brigade_split_line(bb, ctx->bb, block, bytes);

        if (rv) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, f->c, APLOGNO(02020)
                          "could not split line from buffered SSL brigade");
            ap_remove_input_filter(f);
            return rv;
        }
    }

