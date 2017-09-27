ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00560) "Request "
                  "header exceeds LimitRequestFieldSize after merging: %.*s",
                  field_name_len(key), key);