            break;
        case APR_OC_REASON_UNREGISTER:
            /* we get here when pcgi is cleaned up; pcgi gets cleaned
             * up when pconf gets cleaned up
             */
            kill(proc->pid, SIGHUP); /* send signal to daemon telling it to die */

            /* Remove the cgi socket, we must do it here in order to try and
             * guarantee the same permissions as when the socket was created.
             */
            if (unlink(sockname) < 0 && errno != ENOENT) {
                ap_log_error(APLOG_MARK, APLOG_ERR, errno, NULL,
                             "Couldn't unlink unix domain socket %s",
                             sockname);
            }
            break;
    }
}
#endif

/* deal with incomplete reads and signals
