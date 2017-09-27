        char **args;
        const char *pname;

        apr_tokenize_to_argv(pl->program, &args, pl->p);
        pname = apr_pstrdup(pl->p, args[0]);
        procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
        rc = apr_proc_create(procnew, pname, (const char * const *) args,
                             NULL, procattr, pl->p);

        if (rc == APR_SUCCESS) {
            /* pjr - This no longer happens inside the child, */
            /*   I am assuming that if apr_proc_create was  */
            /*   successful that the child is running.        */
            RAISE_SIGSTOP(PIPED_LOG_SPAWN);
            pl->pid = procnew;
            ap_piped_log_write_fd(pl) = procnew->in;
            apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                          ap_piped_log_write_fd(pl), pl->p);
        }
    }

    return 0;
}


static void piped_log_maintenance(int reason, void *data, apr_wait_t status)
{
    piped_log *pl = data;
    apr_status_t stats;

    switch (reason) {
    case APR_OC_REASON_DEATH:
        pl->pid = NULL;
        apr_proc_other_child_unregister(pl);
        if (pl->program == NULL) {
            /* during a restart */
            break;
        }
        break;
    case APR_OC_REASON_LOST:
        pl->pid = NULL;
        apr_proc_other_child_unregister(pl);
        if (pl->program == NULL) {
            /* during a restart */
            break;
        }
        if ((stats = piped_log_spawn(pl)) != APR_SUCCESS) {
            /* what can we do?  This could be the error log we're having
             * problems opening up... */
            char buf[120];
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "piped_log_maintenance: unable to respawn '%s': %s",
                         pl->program, apr_strerror(stats, buf, sizeof(buf)));
        }
        break;

    case APR_OC_REASON_UNWRITABLE:
        /* We should not kill off the pipe here, since it may only be full.
         * If it really is locked, we should kill it off manually. */
    break;

    case APR_OC_REASON_RESTART:
        pl->program = NULL;
        if (pl->pid != NULL) {
            apr_proc_kill(pl->pid, SIGTERM);
        }
        break;

    case APR_OC_REASON_UNREGISTER:
        break;
    }
