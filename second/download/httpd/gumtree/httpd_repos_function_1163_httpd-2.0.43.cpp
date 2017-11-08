static int include_cmd(include_ctx_t *ctx, apr_bucket_brigade **bb, char *command,
                       request_rec *r, ap_filter_t *f)
{
    char **env; 
    const char *location; 
    int sd;
    apr_status_t rc = APR_SUCCESS; 
    int retval;
    apr_bucket_brigade *bcgi;
    apr_bucket *b;
    apr_file_t *tempsock = NULL;
    cgid_server_conf *conf = ap_get_module_config(r->server->module_config,
                                                  &cgid_module); 

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

    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.
     * Note that this does not register a cleanup for the socket.  We did
     * that explicitly right after we created the socket.
     */
    apr_os_file_put(&tempsock, &sd, 0, r->pool);

    if ((retval = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR))) 
        return retval; 
    
    location = apr_table_get(r->headers_out, "Location"); 

    if (location && location[0] == '/' && r->status == 200) { 
        char argsbuffer[HUGE_STRING_LEN]; 

        /* Soak up all the script output */ 
        while (apr_file_gets(argsbuffer, HUGE_STRING_LEN, 
                             tempsock) == APR_SUCCESS) { 
            continue; 
        } 
        /* This redirect needs to be a GET no matter what the original 
         * method was. 
         */ 
        r->method = apr_pstrdup(r->pool, "GET"); 
        r->method_number = M_GET; 

        /* We already read the message body (if any), so don't allow 
         * the redirected request to think it has one. We can ignore 
         * Transfer-Encoding, since we used REQUEST_CHUNKED_ERROR. 
         */ 
        apr_table_unset(r->headers_in, "Content-Length"); 

        ap_internal_redirect_handler(location, r); 
        return OK; 
    } 
    else if (location && r->status == 200) { 
        /* XX Note that if a script wants to produce its own Redirect 
         * body, it now has to explicitly *say* "Status: 302" 
         */ 
        return HTTP_MOVED_TEMPORARILY; 
    } 

    if (!r->header_only) { 
        /* Passing our socket down the filter chain in a pipe bucket
         * gives up the responsibility of closing the socket, so
         * get rid of the cleanup.
         */
        apr_pool_cleanup_kill(r->pool, (void *)sd, close_unix_socket);

        bcgi = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        b    = apr_bucket_pipe_create(tempsock, r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bcgi, b);
        ap_pass_brigade(f->next, bcgi);
    } 

    return 0;
}