ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, f->r,
                  "h2_task(%s): request filter, exp=%d", task->id, r->expecting_100);