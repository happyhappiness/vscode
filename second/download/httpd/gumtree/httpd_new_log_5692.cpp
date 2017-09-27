ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(02796)
                         "macro '%s' (%s) "
                         "argument name '%s' (#%d) without expected prefix, "
                         "better prefix argument names with one of '%s'.",
                         macro->name, macro->location,
                         tab[i], i + 1, ARG_PREFIX);