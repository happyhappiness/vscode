ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, cid->r, APLOGNO(02111)
                "Could not determine HTTP response code; using %d",
                cid->r->status);