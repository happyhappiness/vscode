static int noloris_monitor(apr_pool_t *pool, server_rec *s)
{
    static apr_hash_t *connections = NULL;
    static apr_time_t last_check = 0;
    static int *totals;

    int i, j;
    int *n;
    int index = 0;
    apr_hash_index_t *hi;
    char *ip;
    apr_time_t time_now;
    char *shm_rec;
    worker_score *ws;

    /* do nothing if disabled */
    if (shm == NULL) {
        return 0;
    }

    /* skip check if it's not due yet */
    time_now = apr_time_now();
    if (time_now - last_check < recheck_time) {
        return 0;
    }
    last_check = time_now;

    /* alloc lots of stuff at start, so we don't leak memory per-call */
    if (connections == NULL) {
        connections = apr_hash_make(pool);
        totals = apr_palloc(pool, server_limit*thread_limit);
        ip = apr_palloc(pool, ADDR_MAX_SIZE);
    }

    /* Get a per-client count of connections in READ state */
    for (i = 0; i < server_limit; ++i) {
        for (j = 0; j < thread_limit; ++j) {
            ws = ap_get_scoreboard_worker_from_indexes(i, j);
            if (ws->status == SERVER_BUSY_READ) {
                n = apr_hash_get(connections, ws->client, APR_HASH_KEY_STRING);
                if (n == NULL) {
                    n = totals + index++ ;
                    *n = 0;
                }
                ++*n;
                apr_hash_set(connections, ws->client, APR_HASH_KEY_STRING, n);
            }
        }
    }

    /* reset shm before writing to it.
     * We're only dealing with approx. counts, so we ignore the race condition
     * with our prospective readers
     */
    shm_rec = apr_shm_baseaddr_get(shm);
    memset(shm_rec, 0, shm_size);

    /* Now check the hash for clients with too many connections in READ state */
    for (hi = apr_hash_first(NULL, connections); hi; hi = apr_hash_next(hi)) {
        apr_hash_this(hi, (const void**) &ip, NULL, (void**)&n);
        if (*n >= default_max_connections) {
            /* if this isn't a trusted proxy, we mark it as bad */
            if (!apr_hash_get(trusted, ip, APR_HASH_KEY_STRING)) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, 0,
                       "noloris: banning %s with %d connections in READ state",
                       ip, *n);
                strcpy(shm_rec, ip);
                shm_rec += ADDR_MAX_SIZE;
            }
        }
    }
    apr_hash_clear(connections);
    return 0;
}