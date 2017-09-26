                       ap_escape_shell_cmd(f->r->pool, arg_copy));
    }

    env = (const char * const *) ap_create_environment(ctx->p,
                                                       f->r->subprocess_env);

    rc = apr_proc_create(ctx->proc, 
                            ctx->filter->command, 
                            (const char * const *)ctx->filter->args, 
                            env, /* environment */
                            ctx->procattr, 
                            ctx->p);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, f->r,
                      "couldn't create child process to run `%s'",
                      ctx->filter->command);
        return rc;
