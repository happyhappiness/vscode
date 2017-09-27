        }
        else {
            apr_pool_cleanup_register(r->pool, (void *)((long)sd),
                                      close_unix_socket, apr_pool_cleanup_null);
            break; /* we got connected! */
        }
        /* gotta try again, but make sure the cgid daemon is still around */
        if (kill(daemon_pid, 0) != 0) {
            return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, errno, APLOGNO(01258)
                                   "cgid daemon is gone; is Apache terminating?");
        }
    }
    *sdptr = sd;
    return OK;
}
