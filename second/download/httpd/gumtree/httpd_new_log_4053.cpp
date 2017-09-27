ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01320)
                     "LDAP: SSL support unavailable%s%s",
                     result_err ? ": " : "",
                     result_err ? result_err->reason : "");