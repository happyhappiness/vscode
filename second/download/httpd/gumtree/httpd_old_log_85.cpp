ap_log_rerror(APLOG_MARK, level | APLOG_NOERRNO, 0, r,
                          "%s  [%d, #%d]",
                          errscan->desc, errscan->status, errscan->error_id);