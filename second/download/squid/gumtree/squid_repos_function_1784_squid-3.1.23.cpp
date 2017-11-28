peer *
neighborsDigestSelect(HttpRequest * request)
{
    peer *best_p = NULL;
#if USE_CACHE_DIGESTS

    int best_rtt = 0;
    int choice_count = 0;
    int ichoice_count = 0;
    peer *p;
    int p_rtt;
    int i;

    if (!request->flags.hierarchical)
        return NULL;

    storeKeyPublicByRequest(request);

    for (i = 0, p = first_ping; i++ < Config.npeers; p = p->next) {
        lookup_t lookup;

        if (!p)
            p = Config.peers;

        if (i == 1)
            first_ping = p;

        lookup = peerDigestLookup(p, request);

        if (lookup == LOOKUP_NONE)
            continue;

        choice_count++;

        if (lookup == LOOKUP_MISS)
            continue;

        p_rtt = netdbHostRtt(p->host);

        debugs(15, 5, "neighborsDigestSelect: peer " << p->host << " rtt: " << p_rtt);

        /* is this peer better than others in terms of rtt ? */
        if (!best_p || (p_rtt && p_rtt < best_rtt)) {
            best_p = p;
            best_rtt = p_rtt;

            if (p_rtt)		/* informative choice (aka educated guess) */
                ichoice_count++;

            debugs(15, 4, "neighborsDigestSelect: peer " << p->host << " leads with rtt " << best_rtt);
        }
    }

    debugs(15, 4, "neighborsDigestSelect: choices: " << choice_count << " (" << ichoice_count << ")");
    peerNoteDigestLookup(request, best_p,
                         best_p ? LOOKUP_HIT : (choice_count ? LOOKUP_MISS : LOOKUP_NONE));
    request->hier.n_choices = choice_count;
    request->hier.n_ichoices = ichoice_count;
#endif

    return best_p;
}