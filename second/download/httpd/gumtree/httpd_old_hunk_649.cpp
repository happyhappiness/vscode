    if (dc->log_stderr > 0) {
        rc = apr_procattr_child_err_set(ctx->procattr,
                                      f->r->server->error_log, /* stderr in child */
                                      NULL);
        ap_assert(rc == APR_SUCCESS);
    }
                                  
    rc = apr_proc_create(ctx->proc, 
                            ctx->filter->command, 
                            (const char * const *)ctx->filter->args, 
                            NULL, /* environment */
                            ctx->procattr, 
                            ctx->p);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, f->r,
                      "couldn't create child process to run `%s'",
                      ctx->filter->command);
