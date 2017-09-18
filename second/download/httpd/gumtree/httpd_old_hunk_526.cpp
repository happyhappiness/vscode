            || (BytesWritten != sizeof(hDup))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to send the scoreboard handle to the child");
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, ap_server_conf,
                 "Parent: Sent the scoreboard to the child");
    return 0;
}

static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId, HANDLE hPipeWrite)
{
