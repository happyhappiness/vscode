ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Unlock failed (%s):  "
                      "No Lock-Token specified in header", r->filename);