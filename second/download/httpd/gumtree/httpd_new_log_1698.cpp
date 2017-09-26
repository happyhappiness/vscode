ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, cid->r,
                "ISAPI: Could not determine HTTP response code; using %d",
                cid->r->status);