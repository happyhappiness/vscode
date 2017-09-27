
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
    }

    do {
        len = sizeof(buf);
        rv = apr_file_read(ctx->proc->out,
                      buf,
                      &len);
        if ((rv && !APR_STATUS_IS_EOF(rv) && !APR_STATUS_IS_EAGAIN(rv)) ||
            dc->debug >= DBGLVL_GORY) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "apr_file_read(child output), len %" APR_SIZE_T_FMT,
                          !rv ? len : -1);
        }
        if (APR_STATUS_IS_EAGAIN(rv)) {
            if (eos) {
                /* should not occur, because we have an APR timeout in place */
                AP_DEBUG_ASSERT(1 != 1);
            }
            return APR_SUCCESS;
