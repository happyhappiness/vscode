ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01080)
                      "ajp_msg_check_header() got bad signature %02x%02x",
                      head[0], head[1]);