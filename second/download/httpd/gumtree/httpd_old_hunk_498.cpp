#endif
#if APR_HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef AP_MPM_WANT_RECLAIM_CHILD_PROCESSES
void ap_reclaim_child_processes(int terminate)
{
    int i;
    long int waittime = 1024 * 16;      /* in usecs */
    apr_status_t waitret;
    int tries;
    int not_dead_yet;
    int max_daemons;

    ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);

    for (tries = terminate ? 4 : 1; tries <= 9; ++tries) {
        /* don't want to hold up progress any more than
         * necessary, but we need to allow children a few moments to exit.
         * Set delay with an exponential backoff.
         */
        apr_sleep(waittime);
        waittime = waittime * 4;

        /* now see who is done */
        not_dead_yet = 0;
        for (i = 0; i < max_daemons; ++i) {
            pid_t pid = MPM_CHILD_PID(i);
            apr_proc_t proc;

            if (pid == 0)
                continue;

            proc.pid = pid;
            waitret = apr_proc_wait(&proc, NULL, NULL, APR_NOWAIT);
            if (waitret != APR_CHILD_NOTDONE) {
                MPM_NOTE_CHILD_KILLED(i);
                continue;
            }

            ++not_dead_yet;
            switch (tries) {
            case 1:     /*  16ms */
            case 2:     /*  82ms */
            case 3:     /* 344ms */
            case 4:     /*  16ms */
                break;

            case 5:     /*  82ms */
            case 6:     /* 344ms */
            case 7:     /* 1.4sec */
                /* ok, now it's being annoying */
                ap_log_error(APLOG_MARK, APLOG_WARNING,
                             0, ap_server_conf,
                             "child process %ld still did not exit, "
                             "sending a SIGTERM",
                             (long)pid);
                kill(pid, SIGTERM);
                break;

            case 8:     /*  6 sec */
                /* die child scum */
                ap_log_error(APLOG_MARK, APLOG_ERR,
                             0, ap_server_conf,
                             "child process %ld still did not exit, "
                             "sending a SIGKILL",
                             (long)pid);
#ifndef BEOS
                kill(pid, SIGKILL);
#else
                /* sending a SIGKILL kills the entire team on BeOS, and as
                 * httpd thread is part of that team it removes any chance
                 * of ever doing a restart.  To counter this I'm changing to
                 * use a kinder, gentler way of killing a specific thread
                 * that is just as effective.
                 */
                kill_thread(pid);
#endif
                break;

            case 9:     /* 14 sec */
                /* gave it our best shot, but alas...  If this really
                 * is a child we are trying to kill and it really hasn't
                 * exited, we will likely fail to bind to the port
                 * after the restart.
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR,
                             0, ap_server_conf,
                             "could not make child process %ld exit, "
                             "attempting to continue anyway",
                             (long)pid);
                break;
            }
        }

#if APR_HAS_OTHER_CHILD
        apr_proc_other_child_check();
#endif

        if (!not_dead_yet) {
            /* nothing left to wait for */
            break;
        }
    }
}
#endif /* AP_MPM_WANT_RECLAIM_CHILD_PROCESSES */

#ifdef AP_MPM_WANT_WAIT_OR_TIMEOUT

/* number of calls to wait_or_timeout between writable probes */
