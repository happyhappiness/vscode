        ap_init_scoreboard(sb_shared);
    }
    else
#endif
    {
        /* A simple malloc will suffice */
        void *sb_mem = calloc(1, scoreboard_size);
        if (sb_mem == NULL) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                         "(%d)%s: cannot allocate scoreboard",
                         errno, strerror(errno));
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_init_scoreboard(sb_mem);
    }

    ap_scoreboard_image->global->sb_type = sb_type;
    ap_scoreboard_image->global->running_generation = running_gen;
    ap_scoreboard_image->global->restart_time = apr_time_now();

    apr_pool_cleanup_register(p, NULL, ap_cleanup_scoreboard, apr_pool_cleanup_null);

    return OK;
}
