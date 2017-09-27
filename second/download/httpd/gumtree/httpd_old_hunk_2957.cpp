    }

    if (openslots > 0) {
        apr_uint32_t c = 0;
        apr_uint32_t pick = 0;

        rv = random_pick(&pick, 0, openslots);

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "lb_heartbeat: failed picking a random number. how random.");
            apr_pool_destroy(tpool);
            return NULL;
        }

        for (i = 0; i < up_servers->nelts; i++) {
            server = APR_ARRAY_IDX(up_servers, i, hb_server_t *);
            if (pick >= c && pick <= c + server->ready) {
                mycandidate = server->worker;
            }
