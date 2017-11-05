ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "Request header value is malformed: "
                                  "%.*s", (int)LOG_NAME_MAX_LEN, value);