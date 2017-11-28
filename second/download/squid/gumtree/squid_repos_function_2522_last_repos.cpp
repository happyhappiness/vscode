bool
StoreEntry::timestampsSet()
{
    const HttpReply *reply = getReply();
    time_t served_date = reply->date;
    int age = reply->header.getInt(Http::HdrType::AGE);
    /* Compute the timestamp, mimicking RFC2616 section 13.2.3. */
    /* make sure that 0 <= served_date <= squid_curtime */

    if (served_date < 0 || served_date > squid_curtime)
        served_date = squid_curtime;

    /* Bug 1791:
     * If the returned Date: is more than 24 hours older than
     * the squid_curtime, then one of us needs to use NTP to set our
     * clock.  We'll pretend that our clock is right.
     */
    else if (served_date < (squid_curtime - 24 * 60 * 60) )
        served_date = squid_curtime;

    /*
     * Compensate with Age header if origin server clock is ahead
     * of us and there is a cache in between us and the origin
     * server.  But DONT compensate if the age value is larger than
     * squid_curtime because it results in a negative served_date.
     */
    if (age > squid_curtime - served_date)
        if (squid_curtime > age)
            served_date = squid_curtime - age;

    // compensate for Squid-to-server and server-to-Squid delays
    if (mem_obj && mem_obj->request) {
        const time_t request_sent =
            mem_obj->request->hier.peer_http_request_sent.tv_sec;
        if (0 < request_sent && request_sent < squid_curtime)
            served_date -= (squid_curtime - request_sent);
    }

    time_t exp = 0;
    if (reply->expires > 0 && reply->date > -1)
        exp = served_date + (reply->expires - reply->date);
    else
        exp = reply->expires;

    if (timestamp == served_date && expires == exp) {
        // if the reply lacks LMT, then we now know that our effective
        // LMT (i.e., timestamp) will stay the same, otherwise, old and
        // new modification times must match
        if (reply->last_modified < 0 || reply->last_modified == lastModified())
            return false; // nothing has changed
    }

    expires = exp;

    lastModified_ = reply->last_modified;

    timestamp = served_date;

    return true;
}