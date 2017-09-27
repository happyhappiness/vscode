ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading first chunk %s ", 
                              (ctx->remaining < 0) ? "(overflow)" : "");