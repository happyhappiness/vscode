ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, 
                  APLOGNO(03385) "h2_task(%s): destroy "
                  "output beam empty=%d, holds proxies=%d", 
                  task->id,
                  h2_beam_empty(task->output.beam),
                  h2_beam_holds_proxies(task->output.beam));