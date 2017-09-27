ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, output->task->c,
                  "h2_task(%s): write response body (%ld bytes)", 
                  output->task->id, (long)written);