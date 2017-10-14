static int include_cmd(include_ctx_t *ctx, ap_filter_t *f,
                       apr_bucket_brigade *bb, char *command)
{
    char **env;
    int sd;
    int retval;
    apr_file_t *tempsock = NULL;
    request_rec *r = f->r;
    cgid_server_conf *conf = ap_get_module_config(r->server->module_config,
                                                  &cgid_module);
    cgid_dirconf *dc = ap_get_module_config(r->per_dir_config, &cgid_module);

    struct cleanup_script_info *info;
    apr_status_t rv;

    add_ssi_vars(r);
    env = ap_create_environment(r->pool, r->subprocess_env);

    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
    }

    send_req(sd, r, command, env, SSI_REQ);

    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
    info->conf = conf;
    info->r = r;
    rv = get_cgi_pid(r, conf, &(info->pid));
    if (APR_SUCCESS == rv) {             
        /* for this type of request, the script is invoked through an
         * intermediate shell process...  cleanup_script is only able
         * to knock out the shell process, not the actual script
         */
        apr_pool_cleanup_register(r->pool, info,
                                  cleanup_script,
                                  apr_pool_cleanup_null);
    }
    else { 
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, "error determining cgi PID (for SSI)");
    }

    apr_pool_cleanup_register(r->pool, info,
                              cleanup_script,
                              apr_pool_cleanup_null);

    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.  APR will create
     * a cleanup for the apr_file_t which will close the socket, so we'll
     * get rid of the cleanup we registered when we created the socket.
     */
    apr_os_pipe_put_ex(&tempsock, &sd, 1, r->pool);
    if (dc->timeout > 0) {
        apr_file_pipe_timeout_set(tempsock, dc->timeout);
    }
    else {
        apr_file_pipe_timeout_set(tempsock, r->server->timeout);
    }

    apr_pool_cleanup_kill(r->pool, (void *)((long)sd), close_unix_socket);

    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pipe_create(tempsock,
                            f->c->bucket_alloc));
    ctx->flush_now = 1;

    return APR_SUCCESS;
}