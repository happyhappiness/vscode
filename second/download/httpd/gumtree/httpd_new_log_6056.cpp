ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                              "h2_task_input(%s): getline: %s",
                              input->task->id, buffer);