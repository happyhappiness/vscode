
        /* read the response */
        status = ajp_read_header(conn->sock, r, maxsize,
                                 (ajp_msg_t **)&(conn->data));
        if (status != APR_SUCCESS) {
            backend_failed = 1;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00889)
                          "ajp_read_header failed");
            break;
        }
        result = ajp_parse_type(r, conn->data);
    }
    apr_brigade_destroy(input_brigade);

