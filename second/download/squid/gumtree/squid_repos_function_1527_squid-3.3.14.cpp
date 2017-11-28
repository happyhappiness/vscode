void
carpInit(void)
{
    int W = 0;
    int K;
    int k;
    double P_last, X_last, Xn;
    CachePeer *p;
    CachePeer **P;
    char *t;
    /* Clean up */

    for (k = 0; k < n_carp_peers; ++k) {
        cbdataReferenceDone(carp_peers[k]);
    }

    safe_free(carp_peers);
    n_carp_peers = 0;

    /* initialize cache manager before we have a chance to leave the execution path */
    carpRegisterWithCacheManager();

    /* find out which peers we have */

    for (p = Config.peers; p; p = p->next) {
        if (!p->options.carp)
            continue;

        assert(p->type == PEER_PARENT);

        if (p->weight == 0)
            continue;

        ++n_carp_peers;

        W += p->weight;
    }

    if (n_carp_peers == 0)
        return;

    carp_peers = (CachePeer **)xcalloc(n_carp_peers, sizeof(*carp_peers));

    /* Build a list of the found peers and calculate hashes and load factors */
    for (P = carp_peers, p = Config.peers; p; p = p->next) {
        if (!p->options.carp)
            continue;

        if (p->weight == 0)
            continue;

        /* calculate this peers hash */
        p->carp.hash = 0;

        for (t = p->name; *t != 0; ++t)
            p->carp.hash += ROTATE_LEFT(p->carp.hash, 19) + (unsigned int) *t;

        p->carp.hash += p->carp.hash * 0x62531965;

        p->carp.hash = ROTATE_LEFT(p->carp.hash, 21);

        /* and load factor */
        p->carp.load_factor = ((double) p->weight) / (double) W;

        if (floor(p->carp.load_factor * 1000.0) == 0.0)
            p->carp.load_factor = 0.0;

        /* add it to our list of peers */
        *P = cbdataReference(p);
        ++P;
    }

    /* Sort our list on weight */
    qsort(carp_peers, n_carp_peers, sizeof(*carp_peers), peerSortWeight);

    /* Calculate the load factor multipliers X_k
     *
     * X_1 = pow ((K*p_1), (1/K))
     * X_k = ([K-k+1] * [P_k - P_{k-1}])/(X_1 * X_2 * ... * X_{k-1})
     * X_k += pow ((X_{k-1}, {K-k+1})
     * X_k = pow (X_k, {1/(K-k+1)})
     * simplified to have X_1 part of the loop
     */
    K = n_carp_peers;

    P_last = 0.0;		/* Empty P_0 */

    Xn = 1.0;			/* Empty starting point of X_1 * X_2 * ... * X_{x-1} */

    X_last = 0.0;		/* Empty X_0, nullifies the first pow statement */

    for (k = 1; k <= K; ++k) {
        double Kk1 = (double) (K - k + 1);
        p = carp_peers[k - 1];
        p->carp.load_multiplier = (Kk1 * (p->carp.load_factor - P_last)) / Xn;
        p->carp.load_multiplier += pow(X_last, Kk1);
        p->carp.load_multiplier = pow(p->carp.load_multiplier, 1.0 / Kk1);
        Xn *= p->carp.load_multiplier;
        X_last = p->carp.load_multiplier;
        P_last = p->carp.load_factor;
    }
}