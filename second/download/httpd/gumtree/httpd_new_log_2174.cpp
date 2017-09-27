ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_DEBUG, 0, l->pool,
                      "Releasing mutex %s:%d", l->file, l->line);