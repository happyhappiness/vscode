                cache->remove_url_filter =
                    ap_add_output_filter_handle(cache_remove_url_filter_handle,
                            cache, r, r->connection);

            }
            else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv,
                             r->server, "Cache locked for url, not caching "
                             "response: %s", r->uri);
            }
        }
        else {
            /* error */
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "cache: error returned while checking for cached "
                         "file by %s cache", cache->provider_name);
        }
        return DECLINED;
    }

    rv = ap_meets_conditions(r);
    if (rv != OK) {
        return rv;
    }

    /* Serve up the content */
