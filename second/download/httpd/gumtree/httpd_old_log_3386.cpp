ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "ISAPI: %s: %s", r->filename, cid->ecb->lpszLogData);