	CloseHandle(e);
	return;
    }
    CloseHandle(e);
}

/* set_listeners_noninheritable()
 * Make the listening socket handles noninheritable by processes
 * started out of this process.
 */
static int set_listeners_noninheritable(apr_pool_t *p) 
{
    ap_listen_rec *lr;
    HANDLE dup;
    SOCKET nsd;
    HANDLE hProcess = GetCurrentProcess();

    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_os_sock_get(&nsd,lr->sd);
        if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
            if (!DuplicateHandle(hProcess, (HANDLE) nsd, hProcess, &dup, 
                                 0, FALSE, DUPLICATE_SAME_ACCESS)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "set_listeners_noninheritable: DuplicateHandle failed.");
            }
            else {
                closesocket(nsd);
                nsd = (SOCKET) dup;
                apr_os_sock_put(&lr->sd, &nsd, p);
            }
        }
        else {
            /* A different approach.  Many users report errors such as 
             * (32538)An operation was attempted on something that is not 
             * a socket.  : Parent: WSADuplicateSocket failed...
             *
             * This appears that the duplicated handle is no longer recognized
             * as a socket handle.  SetHandleInformation should overcome that
             * problem by not altering the handle identifier.  But this won't
             * work on 9x - it's unsupported.
             */
            if (!SetHandleInformation((HANDLE)nsd, HANDLE_FLAG_INHERIT, 0)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "set_listeners_noninheritable: SetHandleInformation failed.");
            }
        }
    }

    if (my_pid == parent_pid) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                     "Parent: Marked listeners as not inheritable.");
    } else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                     "Child %d: Marked listeners as not inheritable.", my_pid);
    }
    return 1;
}

/*
 * find_ready_listener()
 * Only used by Win9* and should go away when the win9*_accept() function is 
 * reimplemented using apr_poll().
 */
static ap_listen_rec *head_listener;
static APR_INLINE ap_listen_rec *find_ready_listener(fd_set * main_fds)
{
    ap_listen_rec *lr;
    SOCKET nsd;

    for (lr = head_listener; lr ; lr = lr->next) {
        apr_os_sock_get(&nsd, lr->sd);
	if (FD_ISSET(nsd, main_fds)) {
	    head_listener = lr->next;
            if (head_listener == NULL)
                head_listener = ap_listeners;

	    return (lr);
	}
    }
    return NULL;
}

/*
 *
 */
void get_handles_from_parent(server_rec *s)
{
    HANDLE pipe;
    HANDLE hScore;
    DWORD BytesRead;
    void *sb_shared;
    apr_status_t rv;
    
    pipe = GetStdHandle(STD_INPUT_HANDLE);
    if (!ReadFile(pipe, &exit_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Unable to retrieve the exit event from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }

    if (!ReadFile(pipe, &hScore, sizeof(hScore),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(hScore))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Unable to retrieve the scoreboard from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }

    if ((rv = apr_os_shm_put(&ap_scoreboard_shm, &hScore, s->process->pool)) 
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Child %d: Unable to access the scoreboard from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }

    rv = ap_reopen_scoreboard(s->process->pool, &ap_scoreboard_shm, 1);
    if (rv || !(sb_shared = apr_shm_baseaddr_get(ap_scoreboard_shm))) {
	ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, 
                     "Child %d: Unable to reopen the scoreboard from the parent", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    /* We must 'initialize' the scoreboard to relink all the
     * process-local pointer arrays into the shared memory block.
