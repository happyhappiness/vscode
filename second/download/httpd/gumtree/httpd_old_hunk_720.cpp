                if (sliding_timer < apr_time_from_sec(2)) {
                    sliding_timer *= 2;
                }
            }
            else {
                close(sd);
                return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, errno, 
                                       "unable to connect to cgi daemon after multiple tries");
            }
        }
        else {
            apr_pool_cleanup_register(r->pool, (void *)sd, close_unix_socket,
                                      apr_pool_cleanup_null);
            break; /* we got connected! */
        }
        /* gotta try again, but make sure the cgid daemon is still around */
        if (kill(daemon_pid, 0) != 0) {
            return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, errno,
                                   "cgid daemon is gone; is Apache terminating?");
