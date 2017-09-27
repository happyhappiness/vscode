ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: HTTPS: declining URL %s"
                         " (mod_ssl not configured?)", url);