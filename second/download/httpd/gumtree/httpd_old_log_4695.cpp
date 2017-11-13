ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server,
                         "Init: (%s) You configured HTTPS(%d) "
                         "on the standard HTTP(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTPS_PORT, DEFAULT_HTTP_PORT);