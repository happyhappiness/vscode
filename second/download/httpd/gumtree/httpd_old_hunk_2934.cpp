    apr_uint16_t  num_headers;
    int i;

    rc = ajp_msg_get_uint16(msg, &status);

    if (rc != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                "ajp_unmarshal_response: Null status");
        return rc;
    }
    r->status = status;

    rc = ajp_msg_get_string(msg, &ptr);
