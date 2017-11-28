peer *
carpSelectParent(HttpRequest * request)
{
    int k;
    const char *c;
    peer *p = NULL;
    peer *tp;
    unsigned int user_hash = 0;
    unsigned int combined_hash;
    double score;
    double high_score = 0;
    const char *key = NULL;

    if (n_carp_peers == 0)
        return NULL;

    key = urlCanonical(request);

    /* calculate hash key */
    debugs(39, 2, "carpSelectParent: Calculating hash for " << key);

    for (c = key; *c != 0; c++)
        user_hash += ROTATE_LEFT(user_hash, 19) + *c;

    /* select peer */
    for (k = 0; k < n_carp_peers; k++) {
        tp = carp_peers[k];
        combined_hash = (user_hash ^ tp->carp.hash);
        combined_hash += combined_hash * 0x62531965;
        combined_hash = ROTATE_LEFT(combined_hash, 21);
        score = combined_hash * tp->carp.load_multiplier;
        debugs(39, 3, "carpSelectParent: " << tp->name << " combined_hash " << combined_hash  <<
               " score " << std::setprecision(0) << score);

        if ((score > high_score) && peerHTTPOkay(tp, request)) {
            p = tp;
            high_score = score;
        }
    }

    if (p)
        debugs(39, 2, "carpSelectParent: selected " << p->name);

    return p;
}