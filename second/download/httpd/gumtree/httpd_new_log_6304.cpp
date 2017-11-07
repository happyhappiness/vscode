ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_task(%s): serialize request %s %s", 
                      task->id, task->request->method, task->request->path);