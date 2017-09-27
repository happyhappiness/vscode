
        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
        }
    }

    if (bytes_streamed != cl_val) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: client %s given Content-Length did not match"
