                             cache->type);
                return rv;
            }
            return OK;
        }
        else {
            /* stale data available */
            if (lookup) {
                return DECLINED;
            }

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
