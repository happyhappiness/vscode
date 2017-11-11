static void purge(char *path, apr_pool_t *pool, apr_off_t max)
{
    apr_off_t sum, total, entries, etotal;
    ENTRY *e, *n, *oldest;

    sum = 0;
    entries = 0;

    for (e = APR_RING_FIRST(&root);
         e != APR_RING_SENTINEL(&root, _entry, link);
         e = APR_RING_NEXT(e, link)) {
        sum += e->hsize;
        sum += e->dsize;
        entries++;
    }

    total = sum;
    etotal = entries;

    if (sum <= max) {
        printstats(total, sum, max, etotal, entries);
        return;
    }

    /* process all entries with a timestamp in the future, this may
     * happen if a wrong system time is corrected
     */

    for (e = APR_RING_FIRST(&root);
         e != APR_RING_SENTINEL(&root, _entry, link) && !interrupted;) {
        n = APR_RING_NEXT(e, link);
        if (e->response_time > now || e->htime > now || e->dtime > now) {
            delete_entry(path, e->basename, pool);
            sum -= e->hsize;
            sum -= e->dsize;
            entries--;
            APR_RING_REMOVE(e, link);
            if (sum <= max) {
                if (!interrupted) {
                    printstats(total, sum, max, etotal, entries);
                }
                return;
            }
        }
        e = n;
    }

    if (interrupted) {
        return;
    }

    /* process all entries with are expired */
    for (e = APR_RING_FIRST(&root);
         e != APR_RING_SENTINEL(&root, _entry, link) && !interrupted;) {
        n = APR_RING_NEXT(e, link);
        if (e->expire != APR_DATE_BAD && e->expire < now) {
            delete_entry(path, e->basename, pool);
            sum -= e->hsize;
            sum -= e->dsize;
            entries--;
            APR_RING_REMOVE(e, link);
            if (sum <= max) {
                if (!interrupted) {
                    printstats(total, sum, max, etotal, entries);
                }
                return;
            }
        }
        e = n;
    }

    if (interrupted) {
         return;
    }

    /* process remaining entries oldest to newest, the check for an emtpy
     * ring actually isn't necessary except when the compiler does
     * corrupt 64bit arithmetics which happend to me once, so better safe
     * than sorry
     */
    while (sum > max && !interrupted && !APR_RING_EMPTY(&root, _entry, link)) {
        oldest = APR_RING_FIRST(&root);

        for (e = APR_RING_NEXT(oldest, link);
             e != APR_RING_SENTINEL(&root, _entry, link);
             e = APR_RING_NEXT(e, link)) {
            if (e->dtime < oldest->dtime) {
                oldest = e;
            }
        }

        delete_entry(path, oldest->basename, pool);
        sum -= oldest->hsize;
        sum -= oldest->dsize;
        entries--;
        APR_RING_REMOVE(oldest, link);
    }

    if (!interrupted) {
        printstats(total, sum, max, etotal, entries);
    }
}