    if (dc->log_stderr > 0) {
        rc = apr_procattr_child_err_set(ctx->procattr,
                                      f->r->server->error_log, /* stderr in child */
                                      NULL);
        ap_assert(rc == APR_SUCCESS);
    }

    /* add standard CGI variables as well as DOCUMENT_URI, DOCUMENT_PATH_INFO,
     * and QUERY_STRING_UNESCAPED
     */
    ap_add_cgi_vars(f->r);
    apr_table_setn(f->r->subprocess_env, "DOCUMENT_URI", f->r->uri);
    apr_table_setn(f->r->subprocess_env, "DOCUMENT_PATH_INFO", f->r->path_info);
    if (f->r->args) {
            /* QUERY_STRING is added by ap_add_cgi_vars */
        char *arg_copy = apr_pstrdup(f->r->pool, f->r->args);
        ap_unescape_url(arg_copy);
        apr_table_setn(f->r->subprocess_env, "QUERY_STRING_UNESCAPED",
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
