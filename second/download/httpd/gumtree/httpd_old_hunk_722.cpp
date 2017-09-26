                              apr_pool_cleanup_null);
    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.  APR will create
     * a cleanup for the apr_file_t which will close the socket, so we'll
     * get rid of the cleanup we registered when we created the socket.
     */
    
    apr_os_pipe_put_ex(&tempsock, &sd, 1, r->pool);
    apr_pool_cleanup_kill(r->pool, (void *)sd, close_unix_socket);

    if ((argv0 = strrchr(r->filename, '/')) != NULL) 
        argv0++; 
    else 
        argv0 = r->filename; 

    /* Transfer any put/post args, CERN style... 
     * Note that we already ignore SIGPIPE in the core server. 
     */ 
    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    seen_eos = 0;
    child_stopped_reading = 0;
    if (conf->logname) {
        dbuf = apr_palloc(r->pool, conf->bufbytes + 1);
        dbpos = 0;
    }
    do {
        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);
       
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Error reading request entity data");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
 
        APR_BRIGADE_FOREACH(bucket, bb) {
            const char *data;
            apr_size_t len;

            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
