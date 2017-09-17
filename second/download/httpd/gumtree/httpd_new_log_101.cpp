ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
            "Chunked request body is larger than the configured limit of %lu",
            max_body);