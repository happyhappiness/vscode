ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_send_header: ajp_marshal_into_msgb failed");