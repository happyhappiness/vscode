static int connect_to_daemon(int *sdptr, request_rec *r,
                             cgid_server_conf *conf)
{
    int sd;
    int connect_tries;
    int connect_errno;
    apr_interval_time_t sliding_timer;

    connect_tries = 0;
    sliding_timer = 100000; /* 100 milliseconds */
    while (1) {
        connect_errno = 0;
        ++connect_tries;
        if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
            return log_scripterror(r, conf, HTTP_INTERNAL_SERVER_ERROR, errno,
                                   APLOGNO(01255) "unable to create socket to cgi daemon");
        }
        if (connect(sd, (struct sockaddr *)server_addr, server_addr_len) < 0) {
            /* Save errno for later */
            connect_errno = errno;
            /* ECONNREFUSED means the listen queue is full; ENOENT means that
             * the cgid server either hasn't started up yet, or we're pointing
             * at the wrong socket file */
            if ((errno == ECONNREFUSED || errno == ENOENT) && 
                 connect_tries < DEFAULT_CONNECT_ATTEMPTS) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, errno, r, APLOGNO(01256)
                              "connect #%d to cgi daemon failed, sleeping before retry",
                              connect_tries);
                close(sd);
                apr_sleep(sliding_timer);
                if (sliding_timer < apr_time_from_sec(2)) {
                    sliding_timer *= 2;
                }
            }
            else {
                close(sd);
                return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, errno, APLOGNO(01257)
                                       "unable to connect to cgi daemon after multiple tries");
            }
        }
        else {
            apr_pool_cleanup_register(r->pool, (void *)((long)sd),
                                      close_unix_socket, apr_pool_cleanup_null);
            break; /* we got connected! */
        }

        /* If we didn't find the socket but the server was not recently restarted,
         * chances are there's something wrong with the cgid daemon
         */
        if (connect_errno == ENOENT &&
            apr_time_sec(apr_time_now() - ap_scoreboard_image->global->restart_time) > 
                DEFAULT_CONNECT_STARTUP_DELAY) {
            return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, connect_errno, 
                                   apr_pstrcat(r->pool, APLOGNO(02833) "ScriptSock ", sockname, " does not exist", NULL));
        }

        /* gotta try again, but make sure the cgid daemon is still around */
        if (connect_errno != ENOENT && kill(daemon_pid, 0) != 0) {
            return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, connect_errno, APLOGNO(01258)
                                   "cgid daemon is gone; is Apache terminating?");
        }
    }
    *sdptr = sd;
    return OK;
}