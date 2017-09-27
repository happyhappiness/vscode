                           conn_rec *origin,
                           proxy_dir_conf *conf,
                           apr_uri_t *uri,
                           char *url, char *server_portstr)
{
    /* Request IDs are arbitrary numbers that we assign to a
     * single request. This would allow multiplex/pipelinig of 
     * multiple requests to the same FastCGI connection, but 
     * we don't support that, and always use a value of '1' to
     * keep things simple. */
    int request_id = 1; 
    apr_status_t rv;
   
    /* Step 1: Send FCGI_BEGIN_REQUEST */
    rv = send_begin_request(conn, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: FCGI: Failed Writing Request to %s:",
                     server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }
    
    /* Step 2: Send Environment via FCGI_PARAMS */
    rv = send_environment(conn, r, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: FCGI: Failed writing Environment to %s:",
                     server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }

    /* Step 3: Read records from the back end server and handle them. */
    rv = dispatch(conn, r, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                     "proxy: FCGI: Error dispatching request to %s:",
                     server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }

    return OK;
}
