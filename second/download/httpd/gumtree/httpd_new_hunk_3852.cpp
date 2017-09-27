    HANDLE hCurrentProcess = GetCurrentProcess();
    HANDLE hDup;
    HANDLE os_start;
    HANDLE hScore;
    apr_size_t BytesWritten;

    if ((rv = apr_file_write_full(child_in, &my_generation,
                                  sizeof(my_generation), NULL))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(02964)
                     "Parent: Unable to send its generation to the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, child_ready_event, hProcess, &hDup,
        EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00392)
                     "Parent: Unable to duplicate the ready event handle for the child");
        return -1;
    }
