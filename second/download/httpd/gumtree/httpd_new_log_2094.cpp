ap_log_error(file, line, APLOG_MODULE_INDEX, level, 0, s,
                     "SSL Library Error: %s%s%s%s%s%s",
                     /* %s */
                     err, 
                     /* %s%s%s */
                     data ? " (" : "", data ? data : "", data ? ")" : "", 
                     /* %s%s */
                     annotation ? " -- " : "",
                     annotation ? annotation : "");