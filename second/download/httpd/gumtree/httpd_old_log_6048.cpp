ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, &env->c,
                          "h2_task_input(%s): request is: %s", 
                          env->id, buffer);