            kill(proc->pid, SIGHUP); /* send signal to daemon telling it to die */

            /* Remove the cgi socket, we must do it here in order to try and
             * guarantee the same permissions as when the socket was created.
             */
            if (unlink(sockname) < 0 && errno != ENOENT) {
                ap_log_error(APLOG_MARK, APLOG_ERR, errno, ap_server_conf, APLOGNO(01240)
                             "Couldn't unlink unix domain socket %s",
                             sockname);
            }
            break;
    }
}
