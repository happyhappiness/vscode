static apr_status_t init_ext_filter_process(ap_filter_t *f)
{
    ef_ctx_t *ctx = f->ctx;
    apr_status_t rc;
    ef_dir_t *dc = ctx->dc;
    const char * const *env;

    ctx->proc = apr_pcalloc(ctx->p, sizeof(*ctx->proc));

    rc = apr_procattr_create(&ctx->procattr, ctx->p);
    ap_assert(rc == APR_SUCCESS);

    rc = apr_procattr_io_set(ctx->procattr,
                            APR_CHILD_BLOCK,
                            APR_CHILD_BLOCK,
                            APR_CHILD_BLOCK);
    ap_assert(rc == APR_SUCCESS);

    rc = set_resource_limits(f->r, ctx->procattr);
    ap_assert(rc == APR_SUCCESS);

    if (dc->log_stderr > 0) {
        rc = apr_procattr_child_err_set(ctx->procattr,
                                      f->r->server->error_log, /* stderr in child */
                                      NULL);
        ap_assert(rc == APR_SUCCESS);
    }

    rc = apr_procattr_child_errfn_set(ctx->procattr, child_errfn);
    ap_assert(rc == APR_SUCCESS);
    apr_pool_userdata_set(f->r, ERRFN_USERDATA_KEY, apr_pool_cleanup_null, ctx->p);

    rc = apr_procattr_error_check_set(ctx->procattr, 1);
    if (rc != APR_SUCCESS) {
        return rc;
    }

    /* add standard CGI variables as well as DOCUMENT_URI, DOCUMENT_PATH_INFO,
     * and QUERY_STRING_UNESCAPED
     */
    ap_add_cgi_vars(f->r);
    ap_add_common_vars(f->r);
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
        return rc;
    }

    apr_pool_note_subprocess(ctx->p, ctx->proc, APR_KILL_AFTER_TIMEOUT);

    /* We don't want the handle to the child's stdin inherited by any
     * other processes created by httpd.  Otherwise, when we close our
     * handle, the child won't see EOF because another handle will still
     * be open.
     */

    apr_pool_cleanup_register(ctx->p, ctx->proc->in,
                         apr_pool_cleanup_null, /* other mechanism */
                         ef_close_file);

#if APR_FILES_AS_SOCKETS
    {
        apr_pollfd_t pfd = { 0 };

        rc = apr_pollset_create(&ctx->pollset, 2, ctx->p, 0);
        ap_assert(rc == APR_SUCCESS);

        pfd.p         = ctx->p;
        pfd.desc_type = APR_POLL_FILE;
        pfd.reqevents = APR_POLLOUT;
        pfd.desc.f    = ctx->proc->in;
        rc = apr_pollset_add(ctx->pollset, &pfd);
        ap_assert(rc == APR_SUCCESS);

        pfd.reqevents = APR_POLLIN;
        pfd.desc.f    = ctx->proc->out;
        rc = apr_pollset_add(ctx->pollset, &pfd);
        ap_assert(rc == APR_SUCCESS);
    }
#endif

    return APR_SUCCESS;
}