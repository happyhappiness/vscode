    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01268)
                     "write to cgi daemon process");
    }

    info = apr_palloc(r->pool, sizeof(struct cleanup_script_info));
    info->r = r;
    info->conn_id = r->connection->id;
    info->conf = conf;
    apr_pool_cleanup_register(r->pool, info,
                              cleanup_script,
                              apr_pool_cleanup_null);
    /* We are putting the socket discriptor into an apr_file_t so that we can
     * use a pipe bucket to send the data to the client.  APR will create
     * a cleanup for the apr_file_t which will close the socket, so we'll
     * get rid of the cleanup we registered when we created the socket.
     */

