                             cache->type);
                return rv;
            }
            return OK;
        }
        else {
            if (!r->err_headers_out) {
                r->err_headers_out = apr_table_make(r->pool, 3);
            }
            /* stale data available */
            if (lookup) {
                return DECLINED;
            }

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
