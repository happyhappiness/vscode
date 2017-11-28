lookup_t
peerDigestLookup(peer * p, HttpRequest * request)
{
#if USE_CACHE_DIGESTS
    const cache_key *key = request ? storeKeyPublicByRequest(request) : NULL;
    assert(p);
    assert(request);
    debugs(15, 5, "peerDigestLookup: peer " << p->host);
    /* does the peeer have a valid digest? */

    if (!p->digest) {
        debugs(15, 5, "peerDigestLookup: gone!");
        return LOOKUP_NONE;
    } else if (!peerHTTPOkay(p, request)) {
        debugs(15, 5, "peerDigestLookup: !peerHTTPOkay");
        return LOOKUP_NONE;
    } else if (!p->digest->flags.needed) {
        debugs(15, 5, "peerDigestLookup: note need");
        peerDigestNeeded(p->digest);
        return LOOKUP_NONE;
    } else if (!p->digest->flags.usable) {
        debugs(15, 5, "peerDigestLookup: !ready && " << (p->digest->flags.requested ? "" : "!") << "requested");
        return LOOKUP_NONE;
    }

    debugs(15, 5, "peerDigestLookup: OK to lookup peer " << p->host);
    assert(p->digest->cd);
    /* does digest predict a hit? */

    if (!cacheDigestTest(p->digest->cd, key))
        return LOOKUP_MISS;

    debugs(15, 5, "peerDigestLookup: peer " << p->host << " says HIT!");

    return LOOKUP_HIT;

#endif

    return LOOKUP_NONE;
}