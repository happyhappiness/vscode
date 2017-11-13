ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                         "%s on line %d of %s: %s",
                         what, cfg->line_number, cfg->name, ptr);