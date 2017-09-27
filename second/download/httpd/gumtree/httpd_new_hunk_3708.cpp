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
