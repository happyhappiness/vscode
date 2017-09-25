ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no-cache or authorization forbids caching "
                         "of %s", url);