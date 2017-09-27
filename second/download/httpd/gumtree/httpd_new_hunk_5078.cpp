{
    /* Request IDs are arbitrary numbers that we assign to a
     * single request. This would allow multiplex/pipelinig of
     * multiple requests to the same FastCGI connection, but
     * we don't support that, and always use a value of '1' to
     * keep things simple. */
    apr_uint16_t request_id = 1;
    apr_status_t rv;
    apr_pool_t *temp_pool;

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
    rv = dispatch(conn, conf, r, temp_pool, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01075)
                      "Error dispatching request to %s:", server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }
