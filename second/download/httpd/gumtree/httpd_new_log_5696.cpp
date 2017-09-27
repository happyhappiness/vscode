ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(02800)
                         "macro '%s' (%s): argument '%s' (#%d) never used",
                         macro->name, macro->location, names[i], i + 1);