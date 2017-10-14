ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                          "h2_task(%s): getline: %s",
                          task->id, buffer);