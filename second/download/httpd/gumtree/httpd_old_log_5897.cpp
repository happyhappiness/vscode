ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, &env->c,
                          "h2_task_input(%s): serialize request %s %s", 
                          env->id, env->method, env->path);