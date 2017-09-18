ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, r,
                          "ISAPI %s: %s", cid->r->filename,
                          (char*) lpvBuffer);