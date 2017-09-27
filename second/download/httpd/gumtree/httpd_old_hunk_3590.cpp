        first = ap_getword_conf_nc(pool, &ptr);
        if (first) {
            /* detect nesting... */
            if (!strncmp(first, "</", 2)) {
                any_nesting--;
                if (any_nesting < 0) {
                    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING,
                                 0, NULL,
                                 "bad (negative) nesting on line %d of %s",
                                 config_file->line_number - line_number_start,
                                 where);
                }
            }
            else if (!strncmp(first, "<", 1)) {
