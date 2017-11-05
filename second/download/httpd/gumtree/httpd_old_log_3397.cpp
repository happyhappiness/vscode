ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r,
                  "Unknown Transfer-Encoding: %s; using Content-Length", tenc);