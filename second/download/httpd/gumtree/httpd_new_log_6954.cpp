ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      H2_STRM_MSG(stream, "->03198: %s %s %s"
                      "[started=%d/done=%d/frozen=%d]"), 
                      task->request->method, task->request->authority, 
                      task->request->path, task->worker_started, 
                      task->worker_done, task->frozen);