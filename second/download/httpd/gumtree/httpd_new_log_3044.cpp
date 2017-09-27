ap_log_perror(file, line, APLOG_ERR, rv, l->pool, 
                      "Failed to destroy mutex for dynamic lock %s:%d", 
                      l->file, l->line);