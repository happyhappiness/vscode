    }

    if (openslots > 0) {
        apr_uint32_t c = 0;
        apr_uint32_t pick = 0;

        pick = ap_random_pick(0, openslots);

        for (i = 0; i < up_servers->nelts; i++) {
            server = APR_ARRAY_IDX(up_servers, i, hb_server_t *);
            if (pick >= c && pick <= c + server->ready) {
                mycandidate = server->worker;
            }
