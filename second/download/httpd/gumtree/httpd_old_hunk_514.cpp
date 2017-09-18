    }
    /* We must 'initialize' the scoreboard to relink all the
     * process-local pointer arrays into the shared memory block.
     */
    ap_init_scoreboard(sb_shared);

    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, ap_server_conf,
                 "Child %d: Retrieved our scoreboard from the parent.", my_pid);
}

/* 
 * get_listeners_from_parent()
 * The listen sockets are opened in the parent. This function, which runs
