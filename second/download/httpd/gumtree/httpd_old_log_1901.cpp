ap_log_rerror(APLOG_MARK, APLOG_INFO, rv, f->r,
                                      "Error reading/parsing chunk %s ",
                                      (APR_ENOSPC == rv) ? "(overflow)" : "");