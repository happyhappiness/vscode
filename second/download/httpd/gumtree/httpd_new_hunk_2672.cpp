                            ctx->filter->command,
                            (const char * const *)ctx->filter->args,
                            env, /* environment */
                            ctx->procattr,
                            ctx->p);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, f->r, APLOGNO(01458)
                      "couldn't create child process to run `%s'",
                      ctx->filter->command);
        return rc;
    }

    apr_pool_note_subprocess(ctx->p, ctx->proc, APR_KILL_AFTER_TIMEOUT);
