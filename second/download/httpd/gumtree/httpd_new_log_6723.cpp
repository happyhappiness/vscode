ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02423)
                      "HTTP Request Line; Unrecognized HTTP method: '%.*s' "
                      "(disallowed by RegisteredMethods)",
                      field_name_len(r->method), r->method);