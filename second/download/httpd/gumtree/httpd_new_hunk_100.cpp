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
