static int cgid_start(apr_pool_t *p, server_rec *main_server,
                      apr_proc_t *procnew)
{

    daemon_should_exit = 0; /* clear setting from previous generation */
    if ((daemon_pid = fork()) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "mod_cgid: Couldn't spawn cgid daemon process");
        return DECLINED;
    }
    else if (daemon_pid == 0) {
        if (pcgi == NULL) {
            apr_pool_create(&pcgi, p);
        }
        exit(cgid_server(main_server) > 0 ? DAEMON_STARTUP_ERROR : -1);
    }
    procnew->pid = daemon_pid;
    procnew->err = procnew->in = procnew->out = NULL;
    apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
#if APR_HAS_OTHER_CHILD
    apr_proc_other_child_register(procnew, cgid_maint, procnew, NULL, p);
#endif
    return OK;
}