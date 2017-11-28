struct squid_radix_node *
squid_rn_match(void *v_arg, struct squid_radix_node_head *head) {
    caddr_t v = v_arg;
    register struct squid_radix_node *t = head->rnh_treetop, *x;
    register caddr_t cp = v, cp2;
    caddr_t cplim;
    struct squid_radix_node *saved_t, *top = t;
    int off = t->rn_off, vlen = *(u_char *) cp, matched_off;
    register int test, b, rn_b;

    /*
     * Open code squid_rn_search(v, top) to avoid overhead of extra
     * subroutine call.
     */
    for (; t->rn_b >= 0;) {
        if (t->rn_bmask & cp[t->rn_off])
            t = t->rn_r;
        else
            t = t->rn_l;
    }
    /*
     * See if we match exactly as a host destination
     * or at least learn how many bits match, for normal mask finesse.
     *
     * It doesn't hurt us to limit how many bytes to check
     * to the length of the mask, since if it matches we had a genuine
     * match and the leaf we have is the most specific one anyway;
     * if it didn't match with a shorter length it would fail
     * with a long one.  This wins big for class B&C netmasks which
     * are probably the most common case...
     */
    if (t->rn_mask)
        vlen = *(u_char *) t->rn_mask;
    cp += off;
    cp2 = t->rn_key + off;
    cplim = v + vlen;
    for (; cp < cplim; cp++, cp2++)
        if (*cp != *cp2)
            goto on1;
    /*
     * This extra grot is in case we are explicitly asked
     * to look up the default.  Ugh!
     */
    if ((t->rn_flags & RNF_ROOT) && t->rn_dupedkey)
        t = t->rn_dupedkey;
    return t;
on1:
    test = (*cp ^ *cp2) & 0xff;	/* find first bit that differs */
    for (b = 7; (test >>= 1) > 0;)
        b--;
    matched_off = cp - v;
    b += matched_off << 3;
    rn_b = -1 - b;
    /*
     * If there is a host route in a duped-key chain, it will be first.
     */
    if ((saved_t = t)->rn_mask == 0)
        t = t->rn_dupedkey;
    for (; t; t = t->rn_dupedkey)
        /*
         * Even if we don't match exactly as a host,
         * we may match if the leaf we wound up at is
         * a route to a net.
         */
        if (t->rn_flags & RNF_NORMAL) {
            if (rn_b <= t->rn_b)
                return t;
        } else if (rn_satsifies_leaf(v, t, matched_off))
            return t;
    t = saved_t;
    /* start searching up the tree */
    do {
        register struct squid_radix_mask *m;
        t = t->rn_p;
        if ((m = t->rn_mklist)) {
            /*
             * If non-contiguous masks ever become important
             * we can restore the masking and open coding of
             * the search and satisfaction test and put the
             * calculation of "off" back before the "do".
             */
            do {
                if (m->rm_flags & RNF_NORMAL) {
                    if (rn_b <= m->rm_b)
                        return (m->rm_leaf);
                } else {
                    off = min(t->rn_off, matched_off);
                    x = squid_rn_search_m(v, t, m->rm_mask);
                    while (x && x->rn_mask != m->rm_mask)
                        x = x->rn_dupedkey;
                    if (x && rn_satsifies_leaf(v, x, off))
                        return x;
                }
            } while ((m = m->rm_mklist));
        }
    } while (t != top);
    return 0;
}