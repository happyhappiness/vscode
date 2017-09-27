ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00995)
               "ajp_parse_headers: wrong type %s (0x%02x) expecting %s (0x%02x)",
               ajp_type_str(result), result,
               ajp_type_str(CMD_AJP13_SEND_HEADERS), CMD_AJP13_SEND_HEADERS);