    apr_interval_time_t org;
    apr_byte_t result;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Into ajp_handle_cping_cpong");

    rc = ajp_msg_create(r->pool, AJP_PING_PONG_SZ, &msg);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_handle_cping_cpong: ajp_msg_create failed");
        return rc;
    }

