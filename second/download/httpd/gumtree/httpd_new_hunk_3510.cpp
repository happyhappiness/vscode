        ap_init_scoreboard(sb_shared);
    }
    else
#endif
    {
        /* A simple malloc will suffice */
        void *sb_mem = ap_calloc(1, scoreboard_size);
        ap_init_scoreboard(sb_mem);
    }

    scoreboard_type = sb_type;
    ap_scoreboard_image->global->running_generation = 0;
    ap_scoreboard_image->global->restart_time = apr_time_now();

    apr_pool_cleanup_register(p, NULL, ap_cleanup_scoreboard, apr_pool_cleanup_null);

    return OK;
}
