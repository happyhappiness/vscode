static bool
clientIfRangeMatch(ClientHttpRequest * http, HttpReply * rep)
{
    const TimeOrTag spec = http->request->header.getTimeOrTag(Http::HdrType::IF_RANGE);

    /* check for parsing falure */
    if (!spec.valid)
        return false;

    /* got an ETag? */
    if (spec.tag.str) {
        ETag rep_tag = rep->header.getETag(Http::HdrType::ETAG);
        debugs(33, 3, "ETags: " << spec.tag.str << " and " <<
               (rep_tag.str ? rep_tag.str : "<none>"));

        if (!rep_tag.str)
            return false; // entity has no etag to compare with!

        if (spec.tag.weak || rep_tag.weak) {
            debugs(33, DBG_IMPORTANT, "Weak ETags are not allowed in If-Range: " <<
                   spec.tag.str << " ? " << rep_tag.str);
            return false; // must use strong validator for sub-range requests
        }

        return etagIsStrongEqual(rep_tag, spec.tag);
    }

    /* got modification time? */
    if (spec.time >= 0)
        return !http->storeEntry()->modifiedSince(spec.time);

    assert(0);          /* should not happen */
    return false;
}