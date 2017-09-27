ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, r,
               "ajp_parse_type: got %s (0x%02x)",
               ajp_type_str(result), result);