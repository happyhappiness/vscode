ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                          "mime type is %s; no translation selected",
                          mime_type);