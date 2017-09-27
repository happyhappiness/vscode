ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, rv, s,
                         APLOGNO(02297)
                         "Cannot access directory '%s' for log file '%s' "
                         "defined at %s:%d", dir, cls->fname,
                         directive->filename, directive->line_num);