ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                         base_server, APLOGNO(01916)
                         "Init: (%s) You configured HTTP(%d) "
                         "on the standard HTTPS(%d) port!",
                         ssl_util_vhostid(p, s),
                         DEFAULT_HTTP_PORT, DEFAULT_HTTPS_PORT);