
/* ======================= Cron: called every 100 ms ======================== */

/* Try to expire a few timed out keys. The algorithm used is adaptive and
 * will use few CPU cycles if there are few expiring keys, otherwise
 * it will get more aggressive to avoid that too much memory is used by
 * keys that can be removed from the keyspace.
 *
 * No more than REDIS_DBCRON_DBS_PER_CALL databases are tested at every
 * iteration. */
void activeExpireCycle(void) {
    /* This function has some global state in order to continue the work
     * incrementally across calls. */
    static unsigned int current_db = 0; /* Last DB tested. */
