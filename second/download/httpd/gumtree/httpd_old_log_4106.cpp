ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_marshal_into_msgb: "
                   "Error appending the remote user");