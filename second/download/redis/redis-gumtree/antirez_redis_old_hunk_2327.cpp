    unsigned int j, iteration = 0;
    unsigned int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
    long long start = ustime(), timelimit;

#if 0
    static int expired_history[EXPIRED_HISTORY_LEN];
    static int expired_history_id = 0;
    static int expired_perc_avg = 0;
#endif

    if (fast && !timelimit_exit) return;

#if 0
    if (fast) {
