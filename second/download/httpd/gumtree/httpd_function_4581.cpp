static int mpmt_os2_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s )
{
    char *listener_shm_name;
    parent_info_t *parent_info;
    ULONG rc;
    pconf = _pconf;
    ap_server_conf = s;
    restart_pending = 0;

    DosSetMaxFH(ap_thread_limit * 2);
    listener_shm_name = apr_psprintf(pconf, "/sharemem/httpd/parent_info.%d", getppid());
    rc = DosGetNamedSharedMem((PPVOID)&parent_info, listener_shm_name, PAG_READ);
    is_parent_process = rc != 0;
    ap_scoreboard_fname = apr_psprintf(pconf, "/sharemem/httpd/scoreboard.%d", is_parent_process ? getpid() : getppid());

    if (rc == 0) {
        /* Child process */
        ap_listen_rec *lr;
        int num_listeners = 0;

        ap_mpm_accept_mutex = parent_info->accept_mutex;

        /* Set up a default listener if necessary */
        if (ap_listeners == NULL) {
            ap_listen_rec *lr = apr_pcalloc(s->process->pool, sizeof(ap_listen_rec));
            ap_listeners = lr;
            apr_sockaddr_info_get(&lr->bind_addr, "0.0.0.0", APR_UNSPEC,
                                  DEFAULT_HTTP_PORT, 0, s->process->pool);
            apr_socket_create(&lr->sd, lr->bind_addr->family,
                              SOCK_STREAM, 0, s->process->pool);
        }

        for (lr = ap_listeners; lr; lr = lr->next) {
            apr_sockaddr_t *sa;
            apr_os_sock_put(&lr->sd, &parent_info->listeners[num_listeners].listen_fd, pconf);
            apr_socket_addr_get(&sa, APR_LOCAL, lr->sd);
            num_listeners++;
        }

        DosFreeMem(parent_info);

        /* Do the work */
        ap_mpm_child_main(pconf);

        /* Outta here */
        return 1;
    }
    else {
        /* Parent process */
        char restart;
        is_parent_process = TRUE;

        if (ap_setup_listeners(ap_server_conf) < 1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
                         "no listening sockets available, shutting down");
            return 1;
        }

        ap_log_pid(pconf, ap_pid_fname);

        restart = master_main();
        ++ap_my_generation;
        ap_scoreboard_image->global->running_generation = ap_my_generation;

        if (!restart) {
            const char *pidfile = ap_server_root_relative(pconf, ap_pid_fname);

            if (pidfile != NULL && remove(pidfile) == 0) {
                ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
                             ap_server_conf, "removed PID file %s (pid=%d)",
                             pidfile, getpid());
            }

            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "caught SIGTERM, shutting down");
            return 1;
        }
    }  /* Parent process */

    return 0; /* Restart */
}