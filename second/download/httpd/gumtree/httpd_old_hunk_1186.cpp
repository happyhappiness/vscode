
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "total of %" APR_OFF_T_FMT " bytes in buffer, eos=%d",
                      total, eos);

        /* Fail if this exceeds the maximum buffer size. */
        if (total > SSL_MAX_IO_BUFFER) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request body exceeds maximum size for SSL buffer");
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }

    } while (!eos);

    apr_brigade_destroy(tempb);
