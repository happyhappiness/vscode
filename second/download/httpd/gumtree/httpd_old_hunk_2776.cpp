
        /*
         * If next != NULL then we left the while above because of
         * next->frec == ap_http_header_filter
         */
        if (next) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Custom error page caused AP_FILTER_ERROR");
            type = HTTP_INTERNAL_SERVER_ERROR;
        }
        else {
            return;
        }
