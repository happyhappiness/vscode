    HANDLE ready_event;
    HANDLE os_start;
    DWORD BytesRead;
    void *sb_shared;
    apr_status_t rv;

    /* *** We now do this way back in winnt_rewrite_args
     * pipe = GetStdHandle(STD_INPUT_HANDLE);
     */
    if (!ReadFile(pipe, &ready_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00384)
