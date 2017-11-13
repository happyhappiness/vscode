ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03348)
                  "h2_task(%s): open output to %s %s %s",
                  task->id, task->request->method, 
                  task->request->authority, 
                  task->request->path);