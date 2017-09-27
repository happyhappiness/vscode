ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "Request "
                  "header exceeds LimitRequestFieldSize after merging: %.*s",
                  field_name_len(key), key);