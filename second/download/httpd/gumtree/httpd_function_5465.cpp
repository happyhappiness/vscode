int ap_create_scoreboard(apr_pool_t *p, ap_scoreboard_e sb_type)
{
    int running_gen = 0;
    int i;
#if APR_HAS_SHARED_MEMORY
    apr_status_t rv;
#endif

    pfn_ap_logio_get_last_bytes = APR_RETRIEVE_OPTIONAL_FN(ap_logio_get_last_bytes);

    if (ap_scoreboard_image) {
        running_gen = ap_scoreboard_image->global->running_generation;
        ap_scoreboard_image->global->restart_time = apr_time_now();
        memset(ap_scoreboard_image->parent, 0,
               sizeof(process_score) * server_limit);
        for (i = 0; i < server_limit; i++) {
            memset(ap_scoreboard_image->servers[i], 0,
                   sizeof(worker_score) * thread_limit);
        }
        /* Clean up the lb workers data */
        if (lb_limit && lb_size) {
            memset(ap_scoreboard_image->balancers, 0,
                   lb_size * lb_limit);
        }
        return OK;
    }

    ap_calc_scoreboard_size();
#if APR_HAS_SHARED_MEMORY
    if (sb_type == SB_SHARED) {
        void *sb_shared;
        rv = open_scoreboard(p);
        if (rv || !(sb_shared = apr_shm_baseaddr_get(ap_scoreboard_shm))) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        memset(sb_shared, 0, scoreboard_size);
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