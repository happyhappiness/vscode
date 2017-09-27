                                                          strict);
        if (interpreter && e_info->cmd_type != APR_SHELLCMD) {
            e_info->cmd_type = APR_PROGRAM_PATH;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 strict ? APLOGNO(03180) "No ExecCGI verb found for files of type '%s'."
                        : APLOGNO(03181) "No ExecCGI or Open verb found for files of type '%s'.",
                 ext);
        }
    }
    if (!interpreter) {
        apr_status_t rv;
        char buffer[1024];
