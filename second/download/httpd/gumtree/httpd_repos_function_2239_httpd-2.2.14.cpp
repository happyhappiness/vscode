static apr_status_t cached_explode(apr_time_exp_t *xt, apr_time_t t,
                                   struct exploded_time_cache_element *cache,
                                   int use_gmt)
{
    apr_int64_t seconds = apr_time_sec(t);
    struct exploded_time_cache_element *cache_element =
        &(cache[seconds & TIME_CACHE_MASK]);
    struct exploded_time_cache_element cache_element_snapshot;

    /* The cache is implemented as a ring buffer.  Each second,
     * it uses a different element in the buffer.  The timestamp
     * in the element indicates whether the element contains the
     * exploded time for the current second (vs the time
     * 'now - AP_TIME_RECENT_THRESHOLD' seconds ago).  If the
     * cached value is for the current time, we use it.  Otherwise,
     * we compute the apr_time_exp_t and store it in this
     * cache element. Note that the timestamp in the cache
     * element is updated only after the exploded time.  Thus
     * if two threads hit this cache element simultaneously
     * at the start of a new second, they'll both explode the
     * time and store it.  I.e., the writers will collide, but
     * they'll be writing the same value.
     */
    if (cache_element->t >= seconds) {
        /* There is an intentional race condition in this design:
         * in a multithreaded app, one thread might be reading
         * from this cache_element to resolve a timestamp from
         * TIME_CACHE_SIZE seconds ago at the same time that
         * another thread is copying the exploded form of the
         * current time into the same cache_element.  (I.e., the
         * first thread might hit this element of the ring buffer
         * just as the element is being recycled.)  This can
         * also happen at the start of a new second, if a
         * reader accesses the cache_element after a writer
         * has updated cache_element.t but before the writer
         * has finished updating the whole cache_element.
         *
         * Rather than trying to prevent this race condition
         * with locks, we allow it to happen and then detect
         * and correct it.  The detection works like this:
         *   Step 1: Take a "snapshot" of the cache element by
         *           copying it into a temporary buffer.
         *   Step 2: Check whether the snapshot contains consistent
         *           data: the timestamps at the start and end of
         *           the cache_element should both match the 'seconds'
         *           value that we computed from the input time.
         *           If these three don't match, then the snapshot
         *           shows the cache_element in the middle of an
         *           update, and its contents are invalid.
         *   Step 3: If the snapshot is valid, use it.  Otherwise,
         *           just give up on the cache and explode the
         *           input time.
         */
        memcpy(&cache_element_snapshot, cache_element,
               sizeof(struct exploded_time_cache_element));
        if ((seconds != cache_element_snapshot.t) ||
            (seconds != cache_element_snapshot.t_validate)) {
            /* Invalid snapshot */
            if (use_gmt) {
                return apr_time_exp_gmt(xt, t);
            }
            else {
                return apr_time_exp_lt(xt, t);
            }
        }
        else {
            /* Valid snapshot */
            memcpy(xt, &(cache_element_snapshot.xt),
                   sizeof(apr_time_exp_t));
        }
    }
    else {
        apr_status_t r;
        if (use_gmt) {
            r = apr_time_exp_gmt(xt, t);
        }
        else {
            r = apr_time_exp_lt(xt, t);
        }
        if (r != APR_SUCCESS) {
            return r;
        }
        cache_element->t = seconds;
        memcpy(&(cache_element->xt), xt, sizeof(apr_time_exp_t));
        cache_element->t_validate = seconds;
    }
    xt->tm_usec = (int)apr_time_usec(t);
    return APR_SUCCESS;
}