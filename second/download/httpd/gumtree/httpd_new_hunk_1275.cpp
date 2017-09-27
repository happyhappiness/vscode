    }
    if (!shutdown_in_progress) {
        /* Yow, hit an irrecoverable error! Tell the child to die. */
        SetEvent(exit_event);
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
                 "Child %lu: Accept thread exiting.", my_pid);
    return 0;
}


static PCOMP_CONTEXT winnt_get_connection(PCOMP_CONTEXT context)
{
