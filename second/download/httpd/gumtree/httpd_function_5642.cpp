static int fcgi_do_request(apr_pool_t *p, request_rec *r,
                           proxy_conn_rec *conn,
                           conn_rec *origin,
                           proxy_dir_conf *conf,
                           apr_uri_t *uri,
                           char *url, char *server_portstr)
{
    /* Request IDs are arbitrary numbers that we assign to a
     * single request. This would allow multiplex/pipelining of
     * multiple requests to the same FastCGI connection, but
     * we don't support that, and always use a value of '1' to
     * keep things simple. */
    apr_uint16_t request_id = 1;
    apr_status_t rv;
    apr_pool_t *temp_pool;
    const char *err;
    int bad_request = 0,
        has_responded = 0;

    /* Step 1: Send AP_FCGI_BEGIN_REQUEST */
    rv = send_begin_request(conn, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01073)
                      "Failed Writing Request to %s:", server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }

    apr_pool_create(&temp_pool, r->pool);

    /* Step 2: Send Environment via FCGI_PARAMS */
    rv = send_environment(conn, r, temp_pool, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01074)
                      "Failed writing Environment to %s:", server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }

    /* Step 3: Read records from the back end server and handle them. */
    rv = dispatch(conn, conf, r, temp_pool, request_id,
                  &err, &bad_request, &has_responded);
    if (rv != APR_SUCCESS) {
        /* If the client aborted the connection during retrieval or (partially)
         * sending the response, don't return a HTTP_SERVICE_UNAVAILABLE, since
         * this is not a backend problem. */
        if (r->connection->aborted) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, rv, r, 
                          "The client aborted the connection.");
            conn->close = 1;
            return OK;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01075)
                      "Error dispatching request to %s: %s%s%s",
                      server_portstr,
                      err ? "(" : "",
                      err ? err : "",
                      err ? ")" : "");
        conn->close = 1;
        if (has_responded) {
            return AP_FILTER_ERROR;
        }
        if (bad_request) {
            return ap_map_http_request_error(rv, HTTP_BAD_REQUEST);
        }
        return HTTP_SERVICE_UNAVAILABLE;
    }

    return OK;
}