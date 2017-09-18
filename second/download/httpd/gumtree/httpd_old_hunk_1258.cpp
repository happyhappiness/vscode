        apr_signal(SIGTERM, just_die);
        child_main(slot);

        clean_child_exit(0);
    }
    /* else */
    ap_scoreboard_image->parent[slot].quiescing = 0;
    ap_scoreboard_image->parent[slot].pid = pid;
    return 0;
}

/* start up a bunch of children */
