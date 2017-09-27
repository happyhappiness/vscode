ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 strict ? APLOGNO(03180) "No ExecCGI verb found for files of type '%s'."
                        : APLOGNO(03181) "No ExecCGI or Open verb found for files of type '%s'.",
                 ext);