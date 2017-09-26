            }
        }
        else {
            /* error */
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "cache: error returned while checking for cached "
                         "file by '%s' cache", cache->provider_name);
        }
        return DECLINED;
    }

    /* if we are a lookup, we are exiting soon one way or another; Restore
     * the headers. */
