void
peerSourceHashInit(void)
{
    int W = 0;
    int K;
    int k;
    double P_last, X_last, Xn;
    peer *p;
    peer **P;
    char *t;
    /* Clean up */

    for (k = 0; k < n_sourcehash_peers; k++) {
        cbdataReferenceDone(sourcehash_peers[k]);
    }

    safe_free(sourcehash_peers);
    n_sourcehash_peers = 0;
    /* find out which peers we have */

    for (p = Config.peers; p; p = p->next) {
        if (!p->options.sourcehash)
            continue;

        assert(p->type == PEER_PARENT);

        if (p->weight == 0)
            continue;

        n_sourcehash_peers++;

        W += p->weight;
    }

    peerSourceHashRegisterWithCacheManager();

    if (n_sourcehash_peers == 0)
        return;

    sourcehash_peers = (peer **)xcalloc(n_sourcehash_peers, sizeof(*sourcehash_peers));

    /* Build a list of the found peers and calculate hashes and load factors */
    for (P = sourcehash_peers, p = Config.peers; p; p = p->next) {
        if (!p->options.sourcehash)
            continue;

        if (p->weight == 0)
            continue;

        /* calculate this peers hash */
        p->sourcehash.hash = 0;

        for (t = p->name; *t != 0; t++)
            p->sourcehash.hash += ROTATE_LEFT(p->sourcehash.hash, 19) + (unsigned int) *t;

        p->sourcehash.hash += p->sourcehash.hash * 0x62531965;

        p->sourcehash.hash = ROTATE_LEFT(p->sourcehash.hash, 21);

        /* and load factor */
        p->sourcehash.load_factor = ((double) p->weight) / (double) W;

        if (floor(p->sourcehash.load_factor * 1000.0) == 0.0)
            p->sourcehash.load_factor = 0.0;

        /* add it to our list of peers */
        *P++ = cbdataReference(p);
    }

    /* Sort our list on weight */
    qsort(sourcehash_peers, n_sourcehash_peers, sizeof(*sourcehash_peers), peerSortWeight);

    /* Calculate the load factor multipliers X_k
     *
     * X_1 = pow ((K*p_1), (1/K))
     * X_k = ([K-k+1] * [P_k - P_{k-1}])/(X_1 * X_2 * ... * X_{k-1})
     * X_k += pow ((X_{k-1}, {K-k+1})
     * X_k = pow (X_k, {1/(K-k+1)})
     * simplified to have X_1 part of the loop
     */
    K = n_sourcehash_peers;

    P_last = 0.0;		/* Empty P_0 */

    Xn = 1.0;			/* Empty starting point of X_1 * X_2 * ... * X_{x-1} */

    X_last = 0.0;		/* Empty X_0, nullifies the first pow statement */

    for (k = 1; k <= K; k++) {
        double Kk1 = (double) (K - k + 1);
        p = sourcehash_peers[k - 1];
        p->sourcehash.load_multiplier = (Kk1 * (p->sourcehash.load_factor - P_last)) / Xn;
        p->sourcehash.load_multiplier += pow(X_last, Kk1);
        p->sourcehash.load_multiplier = pow(p->sourcehash.load_multiplier, 1.0 / Kk1);
        Xn *= p->sourcehash.load_multiplier;
        X_last = p->sourcehash.load_multiplier;
        P_last = p->sourcehash.load_factor;
    }
}