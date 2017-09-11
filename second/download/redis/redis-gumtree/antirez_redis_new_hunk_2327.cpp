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
