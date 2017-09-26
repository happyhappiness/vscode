            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "apr_bucket_read()");
            return rv;
        }

        /* Good cast, we just tested len isn't negative */
        if (len > 0 &&
            (rv = pass_data_to_filter(f, data, (apr_size_t)len, bb_tmp))
                != APR_SUCCESS) {
            return rv;
        }
    }

    apr_brigade_cleanup(bb);
    APR_BRIGADE_CONCAT(bb, bb_tmp);
    apr_brigade_destroy(bb_tmp);

    if (eos) {
        /* close the child's stdin to signal that no more data is coming;
         * that will cause the child to finish generating output
         */
        if ((rv = apr_file_close(ctx->proc->in)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_file_close(child input)");
            return rv;
        }
        /* since we've seen eos and closed the child's stdin, set the proper pipe
         * timeout; we don't care if we don't return from apr_file_read() for a while...
         */
        rv = apr_file_pipe_timeout_set(ctx->proc->out,
                                       r->server->timeout);
        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_file_pipe_timeout_set(child output)");
            return rv;
        }
