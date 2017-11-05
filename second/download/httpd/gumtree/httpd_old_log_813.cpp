ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Syntax error on line %d of %s:",
                     parms.err_directive->line_num,
                     parms.err_directive->filename);