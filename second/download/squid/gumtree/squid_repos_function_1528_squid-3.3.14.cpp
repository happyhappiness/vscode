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
    debugs(39, 2, "carpSelectParent: Calculating hash for " << urlCanonical(request));

    /* select CachePeer */
    for (k = 0; k < n_carp_peers; ++k) {
        String key;
        tp = carp_peers[k];
        if (tp->options.carp_key.set) {
            //this code follows urlCanonical's pattern.
            //   corner cases should use the canonical URL
            if (tp->options.carp_key.scheme) {
                // temporary, until bug 1961 URL handling is fixed.
                const URLScheme sch = request->protocol;
                key.append(sch.const_str());
                if (key.size()) //if the scheme is not empty
                    key.append("://");
            }
            if (tp->options.carp_key.host) {
                key.append(request->GetHost());
            }
            if (tp->options.carp_key.port) {
                static char portbuf[7];
                snprintf(portbuf,7,":%d", request->port);
                key.append(portbuf);
            }
            if (tp->options.carp_key.path) {
                String::size_type pos;
                if ((pos=request->urlpath.find('?'))!=String::npos)
                    key.append(request->urlpath.substr(0,pos));
                else
                    key.append(request->urlpath);
            }
            if (tp->options.carp_key.params) {
                String::size_type pos;
                if ((pos=request->urlpath.find('?'))!=String::npos)
                    key.append(request->urlpath.substr(pos,request->urlpath.size()));
            }
        }
        // if the url-based key is empty, e.g. because the user is
        // asking to balance on the path but the request doesn't supply any,
        // then fall back to canonical URL

        if (key.size()==0)
            key=urlCanonical(request);

        for (const char *c = key.rawBuf(), *e=key.rawBuf()+key.size(); c < e; ++c)
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