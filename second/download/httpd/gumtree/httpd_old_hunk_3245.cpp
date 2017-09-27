         * let it set a note to allow it explicitly.
         * Otherwise, a return code that is neither reserved nor HTTP
         * is a bug, as in PR#31759.
         */
        ignore = apr_table_get(r->notes, "HTTP_IGNORE_RANGE");
        if (!ignore) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Handler for %s returned invalid result code %d",
                          r->handler, result);
            result = HTTP_INTERNAL_SERVER_ERROR;
        }
    }

