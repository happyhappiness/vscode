            procnew->in = NULL;
            apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                          pl->write_fd, pl->p);
            close_handle_in_child(pl->p, pl->read_fd);
        }
        else {
            char buf[120];
            /* Something bad happened, give up and go away. */
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00104)
                         "unable to start piped log program '%s': %s",
                         pl->program, apr_strerror(status, buf, sizeof(buf)));
        }
    }

    return status;
}


static void piped_log_maintenance(int reason, void *data, apr_wait_t status)
{
    piped_log *pl = data;
    apr_status_t stats;
    int mpm_state;

    switch (reason) {
    case APR_OC_REASON_DEATH:
    case APR_OC_REASON_LOST:
        pl->pid = NULL; /* in case we don't get it going again, this
                         * tells other logic not to try to kill it
                         */
        apr_proc_other_child_unregister(pl);
        stats = ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state);
        if (stats != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00105)
                         "can't query MPM state; not restarting "
                         "piped log program '%s'",
                         pl->program);
        }
        else if (mpm_state != AP_MPMQ_STOPPING) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00106)
                         "piped log program '%s' failed unexpectedly",
                         pl->program);
            if ((stats = piped_log_spawn(pl)) != APR_SUCCESS) {
                /* what can we do?  This could be the error log we're having
                 * problems opening up... */
                char buf[120];
                ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00107)
                             "piped_log_maintenance: unable to respawn '%s': %s",
                             pl->program, apr_strerror(stats, buf, sizeof(buf)));
            }
        }
        break;

    case APR_OC_REASON_UNWRITABLE:
        /* We should not kill off the pipe here, since it may only be full.
