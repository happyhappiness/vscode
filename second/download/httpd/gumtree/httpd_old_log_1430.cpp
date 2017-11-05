ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
                              "Request header exceeds LimitRequestFieldSize: "
                              "%.*s", field_name_len(field), field);