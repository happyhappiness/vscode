struct squid_radix_node *
squid_rn_addroute(void *v_arg, void *n_arg, struct squid_radix_node_head *head, struct squid_radix_node treenodes[2]) {
    caddr_t v = (caddr_t) v_arg, netmask = (caddr_t) n_arg;
    register struct squid_radix_node *t, *x = NULL, *tt;
    struct squid_radix_node *saved_tt, *top = head->rnh_treetop;
    short b = 0, b_leaf = 0;
    int keyduplicated;
    caddr_t mmask;
    struct squid_radix_mask *m, **mp;

    /*
     * In dealing with non-contiguous masks, there may be
     * many different routes which have the same mask.
     * We will find it useful to have a unique pointer to
     * the mask to speed avoiding duplicate references at
     * nodes and possibly save time in calculating indices.
     */
    if (netmask) {
        if ((x = squid_rn_addmask(netmask, 0, top->rn_off)) == 0)
            return (0);
        b_leaf = x->rn_b;
        b = -1 - x->rn_b;
        netmask = x->rn_key;
    }
    /*
     * Deal with duplicated keys: attach node to previous instance
     */
    saved_tt = tt = squid_rn_insert(v, head, &keyduplicated, treenodes);
    if (keyduplicated) {
        for (t = tt; tt; t = tt, tt = tt->rn_dupedkey) {
            if (tt->rn_mask == netmask)
                return (0);
            if (netmask == 0 ||
                    (tt->rn_mask &&
                     ((b_leaf < tt->rn_b) ||	/* index(netmask) > node */
                      squid_rn_refines(netmask, tt->rn_mask) ||
                      rn_lexobetter(netmask, tt->rn_mask))))
                break;
        }
        /*
         * If the mask is not duplicated, we wouldn't
         * find it among possible duplicate key entries
         * anyway, so the above test doesn't hurt.
         *
         * We sort the masks for a duplicated key the same way as
         * in a masklist -- most specific to least specific.
         * This may require the unfortunate nuisance of relocating
         * the head of the list.
         */
        if (tt == saved_tt) {
            struct squid_radix_node *xx = x;
            /* link in at head of list */
            tt = treenodes;
            tt->rn_dupedkey = t;
            tt->rn_flags = t->rn_flags;
            tt->rn_p = x = t->rn_p;
            if (x->rn_l == t)
                x->rn_l = tt;
            else
                x->rn_r = tt;
            saved_tt = tt;
            x = xx;
        } else {
            tt = treenodes;
            tt->rn_dupedkey = t->rn_dupedkey;
            t->rn_dupedkey = tt;
        }
#ifdef RN_DEBUG
        t = tt + 1;
        tt->rn_info = rn_nodenum++;
        t->rn_info = rn_nodenum++;
        tt->rn_twin = t;
        tt->rn_ybro = rn_clist;
        rn_clist = tt;
#endif
        tt->rn_key = (caddr_t) v;
        tt->rn_b = -1;
        tt->rn_flags = RNF_ACTIVE;
    }
    /*
     * Put mask in tree.
     */
    if (netmask) {
        tt->rn_mask = netmask;
        tt->rn_b = x->rn_b;
        tt->rn_flags |= x->rn_flags & RNF_NORMAL;
    }
    t = saved_tt->rn_p;
    if (keyduplicated)
        goto on2;
    b_leaf = -1 - t->rn_b;
    if (t->rn_r == saved_tt)
        x = t->rn_l;
    else
        x = t->rn_r;
    /* Promote general routes from below */
    if (x->rn_b < 0) {
        for (mp = &t->rn_mklist; x; x = x->rn_dupedkey)
            if (x->rn_mask && (x->rn_b >= b_leaf) && x->rn_mklist == 0) {
                if ((*mp = m = rn_new_radix_mask(x, 0)))
                    mp = &m->rm_mklist;
            }
    } else if (x->rn_mklist) {
        /*
         * Skip over masks whose index is > that of new node
         */
        for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
            if (m->rm_b >= b_leaf)
                break;
        t->rn_mklist = m;
        *mp = 0;
    }
on2:
    /* Add new route to highest possible ancestor's list */
    if ((netmask == 0) || (b > t->rn_b))
        return tt;		/* can't lift at all */
    b_leaf = tt->rn_b;
    do {
        x = t;
        t = t->rn_p;
    } while (b <= t->rn_b && x != top);
    /*
     * Search through routes associated with node to
     * insert new route according to index.
     * Need same criteria as when sorting dupedkeys to avoid
     * double loop on deletion.
     */
    for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist) {
        if (m->rm_b < b_leaf)
            continue;
        if (m->rm_b > b_leaf)
            break;
        if (m->rm_flags & RNF_NORMAL) {
            mmask = m->rm_leaf->rn_mask;
            if (tt->rn_flags & RNF_NORMAL) {
                fprintf(stderr,
                        "Non-unique normal route, mask not entered");
                return tt;
            }
        } else
            mmask = m->rm_mask;
        if (mmask == netmask) {
            m->rm_refs++;
            tt->rn_mklist = m;
            return tt;
        }
        if (squid_rn_refines(netmask, mmask) || rn_lexobetter(netmask, mmask))
            break;
    }
    *mp = rn_new_radix_mask(tt, *mp);
    return tt;
}