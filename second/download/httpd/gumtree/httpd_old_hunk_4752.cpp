        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                maxsize - AJP_HEADER_SZ);

        if (status != APR_SUCCESS) {
            /* We had a failure: Close connection to backend */
            conn->close++;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00871)
                          "ap_get_brigade failed");
            apr_brigade_destroy(input_brigade);
            return HTTP_BAD_REQUEST;
        }

