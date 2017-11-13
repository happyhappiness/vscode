ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, output->task->c, APLOGNO(03348)
                  "h2_task(%s): open response to %s %s %s",
                  output->task->id, output->task->request->method, 
                  output->task->request->authority, 
                  output->task->request->path);