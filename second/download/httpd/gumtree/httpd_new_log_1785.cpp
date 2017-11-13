ap_log_rerror(APLOG_MARK, level, errscan->aprerr, r, "%s  [%d, #%d]",
                      errscan->desc, errscan->status, errscan->error_id);