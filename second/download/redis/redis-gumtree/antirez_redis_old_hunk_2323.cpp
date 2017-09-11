    long long start = ustime(), timelimit;
    static long long last_fast_cycle = 0;

#if 0
    static int expired_history[EXPIRED_HISTORY_LEN];
    static int expired_history_id = 0;
    static int expired_perc_avg = 0;
#endif

    if (fast) {
        /* Don't start a fast cycle if the previous cycle did not exited
         * for time limt. Also don't repeat a fast cycle for the same period
         * as the fast cycle total duration itself. */
        if (!timelimit_exit) return;
        if (start < last_fast_cycle + EXPIRE_FAST_CYCLE_DURATION) {
            printf("CANT START A FAST CYCLE\n");
            return;
        }
        last_fast_cycle = start;
    }

#if 0
    if (fast) {
        if (!timelimit_exit) return;

        /* Let's try to expire a single key from the previous DB, the one that
         * had enough keys expiring to reach the time limit. */
        redisDb *db = server.db+((current_db+server.dbnum-1) % server.dbnum);
        dictEntry *de;

        for (j = 0; j < 100; j++) {
            if ((de = dictGetRandomKey(db->expires)) == NULL) break;
            activeExpireCycleTryExpire(db,de,server.mstime);
        }
        return;
    }
#endif

    /* We usually should test REDIS_DBCRON_DBS_PER_CALL per iteration, with
     * two exceptions:
     *
