void activeExpireCycle(void) {
    int j, iteration = 0;
    long long start = ustime(), timelimit;

    /* We can use at max REDIS_EXPIRELOOKUPS_TIME_PERC percentage of CPU time
     * per iteration. Since this function gets called with a frequency of
     * server.hz times per second, the following is the max amount of
     * microseconds we can spend in this function. */
    timelimit = 1000000*REDIS_EXPIRELOOKUPS_TIME_PERC/server.hz/100;
    if (timelimit <= 0) timelimit = 1;

    for (j = 0; j < server.dbnum; j++) {
        int expired;
        redisDb *db = server.db+j;

        /* Continue to expire if at the end of the cycle more than 25%
         * of the keys were expired. */
        do {
            unsigned long num = dictSize(db->expires);
            unsigned long slots = dictSlots(db->expires);
            long long now = mstime();

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
                long long t;

                if ((de = dictGetRandomKey(db->expires)) == NULL) break;
                t = dictGetSignedIntegerVal(de);
                if (now > t) {
                    sds key = dictGetKey(de);
                    robj *keyobj = createStringObject(key,sdslen(key));

                    propagateExpire(db,keyobj);
                    dbDelete(db,keyobj);
                    decrRefCount(keyobj);
                    expired++;
                    server.stat_expiredkeys++;
                }
            }
            /* We can't block forever here even if there are many keys to
             * expire. So after a given amount of milliseconds return to the
             * caller waiting for the other active expire cycle. */
            iteration++;
            if ((iteration & 0xf) == 0 && /* check once every 16 cycles. */
                (ustime()-start) > timelimit) return;
        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
    }
}