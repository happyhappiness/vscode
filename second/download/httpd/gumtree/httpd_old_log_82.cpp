ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, cmd->server,
                 "mod_file_cache: unable to cache file: %s. MMAP is not supported by this OS", filename);