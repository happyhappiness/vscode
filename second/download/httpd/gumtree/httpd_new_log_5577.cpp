ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, output->task->c,
                      "h2_task(%s): could not write all, saving brigade", 
                      output->task->id);