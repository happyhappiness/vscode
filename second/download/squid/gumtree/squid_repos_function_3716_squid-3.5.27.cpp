static int
refreshStaleness(const StoreEntry * entry, time_t check_time, const time_t age, const RefreshPattern * R, stale_flags * sf)
{
    // 1. If the cached object has an explicit expiration time, then we rely on this and
    //    completely ignore the Min, Percent and Max values in the refresh_pattern.
    if (entry->expires > -1) {
        sf->expires = true;

        if (entry->expires > check_time) {
            debugs(22, 3, "FRESH: expires " << entry->expires <<
                   " >= check_time " << check_time << " ");

            return -1;
        } else {
            debugs(22, 3, "STALE: expires " << entry->expires <<
                   " < check_time " << check_time << " ");

            return (check_time - entry->expires);
        }
    }

    debugs(22, 3, "No explicit expiry given, using heuristics to determine freshness");

    // 2. If the entry is older than the maximum age in the refresh_pattern, it is STALE.
    if (age > R->max) {
        debugs(22, 3, "STALE: age " << age << " > max " << R->max << " ");
        sf->max = true;
        return (age - R->max);
    }

    // 3. If there is a Last-Modified header, try the last-modified factor algorithm.
    const time_t lastmod_delta = entry->timestamp - entry->lastModified();
    if (lastmod_delta > 0) {
        /* stale_age is the age of the response when it became/becomes stale according to
         * the last-modified factor algorithm. It's how long we can consider the response
         * fresh from the time we cached it.
         */
        time_t stale_age = static_cast<time_t>(lastmod_delta * R->pct);

        debugs(22,3, "Last modified " << lastmod_delta << " sec before we cached it, L-M factor " <<
               (100.0 * R->pct) << "% = " << stale_age << " sec freshness lifetime");
        sf->lmfactor = true;

        if (age >= stale_age) {
            debugs(22, 3, "STALE: age " << age << " > stale_age " << stale_age);
            return (age - stale_age);
        } else {
            debugs(22, 3, "FRESH: age " << age << " <= stale_age " << stale_age);
            return -1;
        }
    }

    // 4. If the entry is not as old as the minimum age in the refresh_pattern, it is FRESH.
    if (age < R->min) {
        debugs(22, 3, "FRESH: age (" << age << " sec) is less than configured minimum (" << R->min << " sec)");
        sf->min = true;
        return -1;
    }

    // 5. default is stale, by the amount we missed the minimum by
    debugs(22, 3, "STALE: No explicit expiry, no last modified, and older than configured minimum.");
    return (age - R->min);
}