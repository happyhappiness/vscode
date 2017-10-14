ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%s): %s %s %s"
                      "[orph=%d/started=%d/done=%d/frozen=%d]", 
                      task->id, task->request->method, 
                      task->request->authority, task->request->path,
                      (stream? 0 : 1), task->worker_started, 
                      task->worker_done, task->frozen);