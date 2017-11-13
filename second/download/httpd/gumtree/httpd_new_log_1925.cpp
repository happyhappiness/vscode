ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_check_msg_header() got bad signature %02x%02x",
                      head[0], head[1]);