ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_ERR, rv, l->pool,
                      APLOGNO(02192) "Failed to destroy mutex for dynamic "
                      "lock %s:%d", l->file, l->line);