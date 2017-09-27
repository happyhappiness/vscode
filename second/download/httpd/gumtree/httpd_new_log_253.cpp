ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Faking HTTP Basic Auth header: \"Authorization: %s\"",
                 auth_line);