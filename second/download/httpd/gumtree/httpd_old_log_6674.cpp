ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                  "h2_task(%s): write response body (%ld bytes)", 
                  task->id, (long)written);