void activeExpireCycle(int fast) {
    /* This function has some global state in order to continue the work
     * incrementally across calls. */
    static unsigned int current_db = 0; /* Last DB tested. */
    static int timelimit_exit = 0;      /* Time limit hit in previous call? */

    unsigned int j, iteration = 0;
    unsigned int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
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
     * 1) Don't test more DBs than we have.
     * 2) If last time we hit the time limit, we want to scan all DBs
     * in this iteration, as there is work to do in some DB and we don't want
     * expired keys to use memory for too much time. */
    if (dbs_per_call > server.dbnum || timelimit_exit)
        dbs_per_call = server.dbnum;

    /* We can use at max REDIS_EXPIRELOOKUPS_TIME_PERC percentage of CPU time
     * per iteration. Since this function gets called with a frequency of
     * server.hz times per second, the following is the max amount of
     * microseconds we can spend in this function. */
    timelimit = 1000000*REDIS_EXPIRELOOKUPS_TIME_PERC/server.hz/100;
    timelimit_exit = 0;
    if (timelimit <= 0) timelimit = 1;

    if (fast) timelimit = EXPIRE_FAST_CYCLE_DURATION; /* in microseconds. */

    for (j = 0; j < dbs_per_call; j++) {
        int expired;
        redisDb *db = server.db+(current_db % server.dbnum);

        /* Increment the DB now so we are sure if we run out of time
         * in the current DB we'll restart from the next. This allows to
         * distribute the time evenly across DBs. */
        current_db++;

        /* Continue to expire if at the end of the cycle more than 25%
         * of the keys were expired. */
        do {
            unsigned long num, slots;
            long long now;

            /* If there is nothing to expire try next DB ASAP. */
            if ((num = dictSize(db->expires)) == 0) break;
            slots = dictSlots(db->expires);
            now = mstime();

            /* When there are less than 1% filled slots getting random
             * keys is expensive, so stop here waiting for better times...
             * The dictionary will be resized asap. */
            if (num && slots > DICT_HT_INITIAL_SIZE &&
                (num*100/slots < 1)) break;

            /* The main collection cycle. Sample random keys among keys
             * with an expire set, checking for expired ones. */
            expired = 0;
            if (num > REDIS_EXPIRELOOKUPS_PER_CRON)
                num = REDIS_EXPIRELOOKUPS_PER_CRON;
            while (num--) {
                dictEntry *de;

                if ((de = dictGetRandomKey(db->expires)) == NULL) break;
                if (activeExpireCycleTryExpire(db,de,now)) expired++;
            }
            /* We can't block forever here even if there are many keys to
             * expire. So after a given amount of milliseconds return to the
             * caller waiting for the other active expire cycle. */
            iteration++;
            if ((iteration & 0xf) == 0 && /* check once every 16 iterations. */
                (ustime()-start) > timelimit)
            {
                timelimit_exit = 1;
            }
#if 0
            expired_history_id = (expired_history_id+1) % EXPIRED_HISTORY_LEN;
            expired_history[expired_history_id] = expired;
            {
                int i;
                expired_perc_avg = 0;
                for (i = 0; i < EXPIRED_HISTORY_LEN; i++) {
                    expired_perc_avg += expired_history[i];
                }
                expired_perc_avg = (expired_perc_avg * 100) / (REDIS_EXPIRELOOKUPS_PER_CRON*EXPIRED_HISTORY_LEN);
                // printf("Expired AVG: %d\n", expired_perc_avg);
            }
#endif
            if (timelimit_exit) return;
        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
    }
}