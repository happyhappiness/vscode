int
squid_rn_walktree(struct squid_radix_node_head *h, int (*f) (struct squid_radix_node *, void *), void *w)
{
    int error;
    struct squid_radix_node *base, *next;
    register struct squid_radix_node *rn = h->rnh_treetop;
    /*
     * This gets complicated because we may delete the node
     * while applying the function f to it, so we need to calculate
     * the successor node in advance.
     */
    /* First time through node, go left */
    while (rn->rn_b >= 0)
        rn = rn->rn_l;
    for (;;) {
        base = rn;
        /* If at right child go back up, otherwise, go right */
        while (rn->rn_p->rn_r == rn && (rn->rn_flags & RNF_ROOT) == 0)
            rn = rn->rn_p;
        /* Find the next *leaf* since next node might vanish, too */
        for (rn = rn->rn_p->rn_r; rn->rn_b >= 0;)
            rn = rn->rn_l;
        next = rn;
        /* Process leaves */
        while ((rn = base)) {
            base = rn->rn_dupedkey;
            if (!(rn->rn_flags & RNF_ROOT) && (error = (*f) (rn, w)))
                return (error);
        }
        rn = next;
        if (rn->rn_flags & RNF_ROOT)
            return (0);
    }
    /* NOTREACHED */
}