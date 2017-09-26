        if (reclaim_one_pid(cur_extra->pid, DO_NOTHING)) {
            AP_DEBUG_ASSERT(1 == ap_unregister_extra_mpm_process(cur_extra->pid));
        }
        cur_extra = next;
    }
}

/* Before sending the signal to the pid this function verifies that
 * the pid is a member of the current process group; either using
 * apr_proc_wait(), where waitpid() guarantees to fail for non-child
 * processes; or by using getpgid() directly, if available. */
apr_status_t ap_mpm_safe_kill(pid_t pid, int sig)
{
#ifndef HAVE_GETPGID
    apr_proc_t proc;
    apr_status_t rv;
    apr_exit_why_e why;
    int status;

    /* Ensure pid sanity */
    if (pid < 1) {
        return APR_EINVAL;
    }

    proc.pid = pid;
    rv = apr_proc_wait(&proc, &status, &why, APR_NOWAIT);
    if (rv == APR_CHILD_DONE) {
#ifdef AP_MPM_WANT_PROCESS_CHILD_STATUS
        /* The child already died - log the termination status if
         * necessary: */
        ap_process_child_status(&proc, why, status);
#endif
        return APR_EINVAL;
    }
    else if (rv != APR_CHILD_NOTDONE) {
        /* The child is already dead and reaped, or was a bogus pid -
         * log this either way. */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
                     "cannot send signal %d to pid %ld (non-child or "
                     "already dead)", sig, (long)pid);
        return APR_EINVAL;
    }
#else
    pid_t pg;

    /* Ensure pid sanity. */
    if (pid < 1) {
        return APR_EINVAL;
    }

    pg = getpgid(pid);    
    if (pg == -1) {
        /* Process already dead... */
        return errno;
    }

    if (pg != getpgrp()) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
                     "refusing to send signal %d to pid %ld outside "
                     "process group", sig, (long)pid);
        return APR_EINVAL;
    }
#endif        

    return kill(pid, sig) ? errno : APR_SUCCESS;
}
#endif /* AP_MPM_WANT_RECLAIM_CHILD_PROCESSES */

#ifdef AP_MPM_WANT_WAIT_OR_TIMEOUT

/* number of calls to wait_or_timeout between writable probes */
#ifndef INTERVAL_OF_WRITABLE_PROBES
