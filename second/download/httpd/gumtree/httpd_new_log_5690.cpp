ap_log_error(APLOG_MARK, APLOG_WARNING,
                                 0, NULL, APLOGNO(02793)
                                 "bad (negative) nesting on line %d of %s",
                                 config_file->line_number - line_number_start,
                                 where);