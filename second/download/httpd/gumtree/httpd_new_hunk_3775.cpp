            /* ap_rgetline returns APR_ENOSPC if it fills up the
             * buffer before finding the end-of-line.  This is only going to
             * happen if it exceeds the configured limit for a request-line.
             */
            if (APR_STATUS_IS_ENOSPC(rv)) {
                r->status    = HTTP_REQUEST_URI_TOO_LARGE;
            }
            else if (APR_STATUS_IS_TIMEUP(rv)) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else if (APR_STATUS_IS_EINVAL(rv)) {
                r->status = HTTP_BAD_REQUEST;
            }
            r->proto_num = HTTP_VERSION(1,0);
            r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
            return 0;
        }
    } while ((len <= 0) && (++num_blank_lines < max_blank_lines));

    if (APLOGrtrace5(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
