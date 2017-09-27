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
