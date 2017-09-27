     * get rid of the cleanup we registered when we created the socket.
     */

    apr_os_pipe_put_ex(&tempsock, &sd, 1, r->pool);
    apr_pool_cleanup_kill(r->pool, (void *)((long)sd), close_unix_socket);

    /* Transfer any put/post args, CERN style...
     * Note that we already ignore SIGPIPE in the core server.
     */
    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    seen_eos = 0;
    child_stopped_reading = 0;
    dbuf = NULL;
    dbpos = 0;
    if (conf->logname) {
        dbuf = apr_palloc(r->pool, conf->bufbytes + 1);
    }
    do {
        apr_bucket *bucket;

        rv = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, HUGE_STRING_LEN);

        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_TIMEUP(rv)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01269)
                              "Timeout during reading request entity data");
                return HTTP_REQUEST_TIME_OUT;
            }
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01270)
                          "Error reading request entity data");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        for (bucket = APR_BRIGADE_FIRST(bb);
             bucket != APR_BRIGADE_SENTINEL(bb);
