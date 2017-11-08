static int include_cmd(include_ctx_t *ctx, apr_bucket_brigade **bb, char *command,
                       request_rec *r, ap_filter_t *f)
{
    char **env; 
    int sd;
    apr_status_t rc = APR_SUCCESS; 
    int retval;
    apr_bucket_brigade *bcgi;
    apr_bucket *b;
    apr_file_t *tempsock = NULL;
    cgid_server_conf *conf = ap_get_module_config(r->server->module_config,
                                                  &cgid_module); 
    struct cleanup_script_info *info;

    add_ssi_vars(r, f->next);
    env = ap_create_environment(r->pool, r->subprocess_env);

    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
    }

    SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, rc);
    if (rc != APR_SUCCESS) {
        return rc;
    }

    send_req(sd, r, command, env, SSI_REQ); 

    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
    info->r = r;
    info->conn_id = r->connection->id;
    info->conf = conf;
    /* for this type of request, the script is invoked through an
     * intermediate shell process...  cleanup_script is only able 
     * to knock out the shell process, not the actual script
     */
    apr_pool_cleanup_register(r->pool, info,
                              cleanup_script,
                              apr_pool_cleanup_null);
    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.  APR will create
     * a cleanup for the apr_file_t which will close the socket, so we'll
     * get rid of the cleanup we registered when we created the socket.
     */
    apr_os_pipe_put_ex(&tempsock, &sd, 1, r->pool);
    apr_pool_cleanup_kill(r->pool, (void *)sd, close_unix_socket);

    bcgi = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    b    = apr_bucket_pipe_create(tempsock, r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bcgi, b);
    ap_pass_brigade(f->next, bcgi);

    return 0;
}