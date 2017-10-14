ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, output->task->c, APLOGNO(03204)
                          "h2_task_output(%s): write without response by %s "
                          "for %s %s %s",
                          output->task->id, caller, 
                          output->task->request->method, 
                          output->task->request->authority, 
                          output->task->request->path);