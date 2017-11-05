ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03204)
                      "h2_task(%s): write without response for %s %s %s",
                      task->id, 
                      task->request->method, 
                      task->request->authority, 
                      task->request->path);