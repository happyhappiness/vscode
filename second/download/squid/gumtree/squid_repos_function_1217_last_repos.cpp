CachePeer *
carpSelectParent(HttpRequest * request)
{
    int k;
    CachePeer *p = NULL;
    CachePeer *tp;
    unsigned int user_hash = 0;
    unsigned int combined_hash;
    double score;
    double high_score = 0;

    if (n_carp_peers == 0)
        return NULL;

    /* calculate hash key */
    debugs(39, 2, "carpSelectParent: Calculating hash for " << request->effectiveRequestUri());

    /* select CachePeer */
    for (k = 0; k < n_carp_peers; ++k) {
        SBuf key;
        tp = carp_peers[k];
        if (tp->options.carp_key.set) {
            // this code follows URI syntax pattern.
            // corner cases should use the full effective request URI
            if (tp->options.carp_key.scheme) {
                key.append(request->url.getScheme().image());
                if (key.length()) //if the scheme is not empty
                    key.append("://");
            }
            if (tp->options.carp_key.host) {
                key.append(request->url.host());
            }
            if (tp->options.carp_key.port) {
                key.appendf(":%u", request->url.port());
            }
            if (tp->options.carp_key.path) {
                // XXX: fix when path and query are separate
                key.append(request->url.path().substr(0,request->url.path().find('?'))); // 0..N
            }
            if (tp->options.carp_key.params) {
                // XXX: fix when path and query are separate
                SBuf::size_type pos;
                if ((pos=request->url.path().find('?')) != SBuf::npos)
                    key.append(request->url.path().substr(pos)); // N..npos
            }
        }
        // if the url-based key is empty, e.g. because the user is
        // asking to balance on the path but the request doesn't supply any,
        // then fall back to the effective request URI

        if (key.isEmpty())
            key=request->effectiveRequestUri();

        for (const char *c = key.rawContent(), *e=key.rawContent()+key.length(); c < e; ++c)
            user_hash += ROTATE_LEFT(user_hash, 19) + *c;
        combined_hash = (user_hash ^ tp->carp.hash);
        combined_hash += combined_hash * 0x62531965;
        combined_hash = ROTATE_LEFT(combined_hash, 21);
        score = combined_hash * tp->carp.load_multiplier;
        debugs(39, 3, "carpSelectParent: key=" << key << " name=" << tp->name << " combined_hash=" << combined_hash  <<
               " score=" << std::setprecision(0) << score);

        if ((score > high_score) && peerHTTPOkay(tp, request)) {
            p = tp;
            high_score = score;
        }
    }

    if (p)
        debugs(39, 2, "carpSelectParent: selected " << p->name);

    return p;
}