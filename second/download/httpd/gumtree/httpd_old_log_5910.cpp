ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                      "h2_task_output(%s): opened and passed brigade", 
                      output->env->id);