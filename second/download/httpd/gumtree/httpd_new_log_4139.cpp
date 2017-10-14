ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00998)
               "ajp_parse_data: Wrong chunk length. Length of chunk is %i,"
               " expected length is %i.", *len, expected_len);