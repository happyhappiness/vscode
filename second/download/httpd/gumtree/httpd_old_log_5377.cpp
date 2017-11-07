ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "%s: %s", cid->r->filename,
                          (char*) buf_data);