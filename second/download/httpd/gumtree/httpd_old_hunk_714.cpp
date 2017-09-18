    ap_init_scoreboard(sb_shared);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Child %d: Retrieved our scoreboard from the parent.", my_pid);
}

/* 
 * get_listeners_from_parent()
 * The listen sockets are opened in the parent. This function, which runs
 * exclusively in the child process, receives them from the parent and
 * makes them availeble in the child.
 */
