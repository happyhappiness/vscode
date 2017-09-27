ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING,
                                 0, NULL,
                                 "bad (negative) nesting on line %d of %s",
                                 config_file->line_number - line_number_start,
                                 where);