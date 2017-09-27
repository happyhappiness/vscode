ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01000)
               "ajp_parse_reuse: wrong type %s (0x%02x) expecting %s (0x%02x)",
               ajp_type_str(result), result,
               ajp_type_str(CMD_AJP13_END_RESPONSE), CMD_AJP13_END_RESPONSE);