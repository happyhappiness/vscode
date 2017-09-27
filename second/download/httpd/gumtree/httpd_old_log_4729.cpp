ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, LOG_PREFIX
                        "warning: crypto for '%s' was not previously initialised "
                        "when it was expected to be, initialised instead by "
                        "mod_session_crypto", conf->library);