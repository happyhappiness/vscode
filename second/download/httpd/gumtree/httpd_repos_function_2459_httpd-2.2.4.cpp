static char master_main()
{
    server_rec *s = ap_server_conf;
    ap_listen_rec *lr;
    parent_info_t *parent_info;
    char *listener_shm_name;
    int listener_num, num_listeners, slot;
    ULONG rc;

    printf("%s \n", ap_get_server_description());
    set_signals();

    if (ap_setup_listeners(ap_server_conf) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
                     "no listening sockets available, shutting down");
        return FALSE;
    }

    /* Allocate a shared memory block for the array of listeners */
    for (num_listeners = 0, lr = ap_listeners; lr; lr = lr->next) {
        num_listeners++;
    }

    listener_shm_name = apr_psprintf(pconf, "/sharemem/httpd/parent_info.%d", getpid());
    rc = DosAllocSharedMem((PPVOID)&parent_info, listener_shm_name,
                           sizeof(parent_info_t) + num_listeners * sizeof(listen_socket_t),
                           PAG_READ|PAG_WRITE|PAG_COMMIT);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, APR_FROM_OS_ERROR(rc), s,
                     "failure allocating shared memory, shutting down");
        return FALSE;
    }

    /* Store the listener sockets in the shared memory area for our children to see */
    for (listener_num = 0, lr = ap_listeners; lr; lr = lr->next, listener_num++) {
        apr_os_sock_get(&parent_info->listeners[listener_num].listen_fd, lr->sd);
    }

    /* Create mutex to prevent multiple child processes from detecting
     * a connection with apr_poll()
     */

    rc = DosCreateMutexSem(NULL, &ap_mpm_accept_mutex, DC_SEM_SHARED, FALSE);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, APR_FROM_OS_ERROR(rc), s,
                     "failure creating accept mutex, shutting down");
        return FALSE;
    }

    parent_info->accept_mutex = ap_mpm_accept_mutex;

    /* Allocate shared memory for scoreboard */
    if (ap_scoreboard_image == NULL) {
        void *sb_mem;
        rc = DosAllocSharedMem(&sb_mem, ap_scoreboard_fname,
                               ap_calc_scoreboard_size(),
                               PAG_COMMIT|PAG_READ|PAG_WRITE);

        if (rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                         "unable to allocate shared memory for scoreboard , exiting");
            return FALSE;
        }

        ap_init_scoreboard(sb_mem);
    }

    ap_scoreboard_image->global->restart_time = apr_time_now();
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                "%s configured -- resuming normal operations",
                ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                "Server built: %s", ap_get_server_built());
#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                "AcceptMutex: %s (default: %s)",
                apr_proc_mutex_name(accept_mutex),
                apr_proc_mutex_defname());
#endif
    if (one_process) {
        ap_scoreboard_image->parent[0].pid = getpid();
        ap_mpm_child_main(pconf);
        return FALSE;
    }

    while (!restart_pending && !shutdown_pending) {
        RESULTCODES proc_rc;
        PID child_pid;
        int active_children = 0;

        /* Count number of active children */
        for (slot=0; slot < HARD_SERVER_LIMIT; slot++) {
            active_children += ap_scoreboard_image->parent[slot].pid != 0 &&
                !ap_scoreboard_image->parent[slot].quiescing;
        }

        /* Spawn children if needed */
        for (slot=0; slot < HARD_SERVER_LIMIT && active_children < ap_daemons_to_start; slot++) {
            if (ap_scoreboard_image->parent[slot].pid == 0) {
                spawn_child(slot);
                active_children++;
            }
        }

        rc = DosWaitChild(DCWA_PROCESSTREE, DCWW_NOWAIT, &proc_rc, &child_pid, 0);

        if (rc == 0) {
            /* A child has terminated, remove its scoreboard entry & terminate if necessary */
            for (slot=0; ap_scoreboard_image->parent[slot].pid