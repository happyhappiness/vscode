ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                 "mod_file_cache: unable to cache file: %s. Sendfile is not supported on this OS", filename);