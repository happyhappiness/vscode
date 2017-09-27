ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_headers: wrong type 0x%02x expecting 0x%02x",
               result, CMD_AJP13_SEND_HEADERS);