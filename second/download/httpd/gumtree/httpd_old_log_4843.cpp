ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, rv, l->pool,
                      "Mutex %s:%d acquired!", l->file, l->line);