ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_marshal_into_msgb - Sending unknown method %s as request attribute",
               r->method);