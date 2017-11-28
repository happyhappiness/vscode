static int
refreshStaleness(const StoreEntry * entry, time_t check_time, const time_t age, const RefreshPattern * R, stale_flags * sf)
{
    /** \par
     * Check for an explicit expiration time (Expires: header).
     */
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

    /** \par
     * Use local heuristics to determine staleness.  Start with the
     * max age from the refresh_pattern rule.
     */
    if (age > R->max) {
        debugs(22, 3, "STALE: age " << age << " > max " << R->max << " ");
        sf->max = true;
        return (age - R->max);
    }

    /** \par
     * Try the last-modified factor algorithm:  refresh_pattern n% percentage of Last-Modified: age.
     */
    if (entry->lastmod > -1 && entry->timestamp > entry->lastmod) {
        /*
         * stale_age is the Age of the response when it became/becomes
         * stale according to the last-modified factor algorithm.
         */
        time_t stale_age = static_cast<time_t>((entry->timestamp - entry->lastmod) * R->pct);
        sf->lmfactor = true;

        if (age >= stale_age) {
            debugs(22, 3, "STALE: age " << age << " > stale_age " << stale_age);
            return (age - stale_age);
        } else {
            debugs(22, 3, "FRESH: age " << age << " <= stale_age " << stale_age);
            return -1;
        }
    }

    /** \par
     * Finally, if all else fails;  staleness is determined by the refresh_pattern
     * configured minimum age.
     */
    if (age < R->min) {
        debugs(22, 3, "FRESH: age " << age << " < min " << R->min);
        sf->min = true;
        return -1;
    }

    debugs(22, 3, "STALE: age " << age << " >= min " << R->min);
    return (age - R->min);
}