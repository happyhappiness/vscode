ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING,
                             0, NULL,
                             "macro '%s' (%s): "
                            "argument name prefix conflict (%s #%d and %s #%d),"
                             " be careful about your macro definition!",
                             macro->name, macro->location,
                             tab[i], i + 1, tab[j], j + 1);