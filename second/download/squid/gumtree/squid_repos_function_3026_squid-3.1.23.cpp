peer *
peerUserHashSelectParent(HttpRequest * request)
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

    if (n_userhash_peers == 0)
        return NULL;

    if (request->auth_user_request)
        key = request->auth_user_request->username();

    if (!key)
        return NULL;

    /* calculate hash key */
    debugs(39, 2, "peerUserHashSelectParent: Calculating hash for " << key);

    for (c = key; *c != 0; c++)
        user_hash += ROTATE_LEFT(user_hash, 19) + *c;

    /* select peer */
    for (k = 0; k < n_userhash_peers; k++) {
        tp = userhash_peers[k];
        combined_hash = (user_hash ^ tp->userhash.hash);
        combined_hash += combined_hash * 0x62531965;
        combined_hash = ROTATE_LEFT(combined_hash, 21);
        score = combined_hash * tp->userhash.load_multiplier;
        debugs(39, 3, "peerUserHashSelectParent: " << tp->name << " combined_hash " << combined_hash  <<
               " score " << std::setprecision(0) << score);

        if ((score > high_score) && peerHTTPOkay(tp, request)) {
            p = tp;
            high_score = score;
        }
    }

    if (p)
        debugs(39, 2, "peerUserHashSelectParent: selected " << p->name);

    return p;
}