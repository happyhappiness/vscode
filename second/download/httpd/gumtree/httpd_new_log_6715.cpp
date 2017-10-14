ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03444)
                          "HTTP Request Line; Invalid method token: '%.*s'"
                          " (only GET is allowed for HTTP/0.9 requests)",
                          field_name_len(r->method), r->method);