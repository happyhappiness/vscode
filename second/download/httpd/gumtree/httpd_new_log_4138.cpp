ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00997)
               "ajp_parse_data: wrong type %s (0x%02x) expecting %s (0x%02x)",
               ajp_type_str(result), result,
               ajp_type_str(CMD_AJP13_SEND_BODY_CHUNK), CMD_AJP13_SEND_BODY_CHUNK);