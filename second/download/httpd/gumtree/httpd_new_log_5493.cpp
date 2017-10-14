ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00023)
                 "Couldn't create the %s mutex %s%s%s", type,
                 fname ? "(file " : "",
                 fname ? fname : "",
                 fname ? ")" : "");