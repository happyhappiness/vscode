    }

    /* Find our pid in the scoreboard so we know what slot our parent allocated us */
    for (child_slot = 0; ap_scoreboard_image->parent[child_slot].pid != my_pid && child_slot < HARD_SERVER_LIMIT; child_slot++);

    if (child_slot == HARD_SERVER_LIMIT) {
        ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, ap_server_conf,
                     "child pid not found in scoreboard, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    ap_my_generation = ap_scoreboard_image->parent[child_slot].generation;
    memset(ap_scoreboard_image->servers[child_slot], 0, sizeof(worker_score) * HARD_THREAD_LIMIT);
