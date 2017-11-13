ap_log_error(APLOG_MARK, APLOG_WARNING, rc, cmd->server,
                         "mod_file_cache: unable to mmap %s, skipping", filename);