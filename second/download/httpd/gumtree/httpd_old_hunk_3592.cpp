        if (ltabi == 0) {
            return apr_psprintf(pool,
                                "macro '%s' (%s): empty argument #%d name",
                                macro->name, macro->location, i + 1);
        }
        else if (!looks_like_an_argument(tab[i])) {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                         "macro '%s' (%s) "
                         "argument name '%s' (#%d) without expected prefix, "
                         "better prefix argument names with one of '%s'.",
                         macro->name, macro->location,
                         tab[i], i + 1, ARG_PREFIX);
        }
