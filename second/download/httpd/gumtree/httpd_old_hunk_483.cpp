        ap_scoreboard_image->global->running_generation = ap_my_generation;

        if (!restart) {
            const char *pidfile = ap_server_root_relative(pconf, ap_pid_fname);

            if (pidfile != NULL && remove(pidfile) == 0) {
                ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, APR_SUCCESS,
                             ap_server_conf, "removed PID file %s (pid=%d)",
                             pidfile, getpid());
            }

            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
                         "caught SIGTERM, shutting down");
            return 1;
        }
    }  /* Parent process */

    return 0; /* Restart */
