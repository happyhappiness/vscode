ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, LOG_PREFIX
                        "warning: crypto for '%s' was already initialised, "
                        "using existing configuration", conf->library);