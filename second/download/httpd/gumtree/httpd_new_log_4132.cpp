ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
               "ajp_read_header: ajp_ilink_received %s (0x%02x)",
               ajp_type_str(result), result);