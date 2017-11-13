ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00561)
                              "Request header exceeds LimitRequestFieldSize%s"
                              "%.*s",
                              (field && *field) ? ": " : "",
                              (field) ? field_name_len(field) : 0,
                              (field) ? field : "");