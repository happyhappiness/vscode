static int
clientIfRangeMatch(ClientHttpRequest * http, HttpReply * rep)
{
    const TimeOrTag spec = http->request->header.getTimeOrTag(HDR_IF_RANGE);
    /* check for parsing falure */

    if (!spec.valid)
        return 0;

    /* got an ETag? */
    if (spec.tag.str) {
        ETag rep_tag = rep->header.getETag(HDR_ETAG);
        debugs(33, 3, "clientIfRangeMatch: ETags: " << spec.tag.str << " and " <<
               (rep_tag.str ? rep_tag.str : "<none>"));

        if (!rep_tag.str)
            return 0;		/* entity has no etag to compare with! */

        if (spec.tag.weak || rep_tag.weak) {
            debugs(33, 1, "clientIfRangeMatch: Weak ETags are not allowed in If-Range: " << spec.tag.str << " ? " << rep_tag.str);
            return 0;		/* must use strong validator for sub-range requests */
        }

        return etagIsStrongEqual(rep_tag, spec.tag);
    }

    /* got modification time? */
    if (spec.time >= 0) {
        return http->storeEntry()->lastmod <= spec.time;
    }

    assert(0);			/* should not happen */
    return 0;
}