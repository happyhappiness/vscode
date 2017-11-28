struct squid_radix_node *
squid_rn_delete(void *v_arg, void *netmask_arg, struct squid_radix_node_head *head) {
    register struct squid_radix_node *t, *p, *x, *tt;
    struct squid_radix_mask *m, *saved_m, **mp;
    struct squid_radix_node *dupedkey, *saved_tt, *top;
    caddr_t v, netmask;
    int b, head_off, vlen;

    v = v_arg;
    netmask = netmask_arg;
    x = head->rnh_treetop;
    tt = squid_rn_search(v, x);
    head_off = x->rn_off;
    vlen = *(u_char *) v;
    saved_tt = tt;
    top = x;
    if (tt == 0 ||
            memcmp(v + head_off, tt->rn_key + head_off, vlen - head_off))
        return (0);
    /*
     * Delete our route from mask lists.
     */
    if (netmask) {
        if ((x = squid_rn_addmask(netmask, 1, head_off)) == 0)
            return (0);
        netmask = x->rn_key;
        while (tt->rn_mask != netmask)
            if ((tt = tt->rn_dupedkey) == 0)
                return (0);
    }
    if (tt->rn_mask == 0 || (saved_m = m = tt->rn_mklist) == 0)
        goto on1;
    if (tt->rn_flags & RNF_NORMAL) {
        if (m->rm_leaf != tt || m->rm_refs > 0) {
            fprintf(stderr, "squid_rn_delete: inconsistent annotation\n");
            return 0;       /* dangling ref could cause disaster */
        }
    } else {
        if (m->rm_mask != tt->rn_mask) {
            fprintf(stderr, "squid_rn_delete: inconsistent annotation\n");
            goto on1;
        }
        if (--m->rm_refs >= 0)
            goto on1;
    }
    b = -1 - tt->rn_b;
    t = saved_tt->rn_p;
    if (b > t->rn_b)
        goto on1;       /* Wasn't lifted at all */
    do {
        x = t;
        t = t->rn_p;
    } while (b <= t->rn_b && x != top);
    for (mp = &x->rn_mklist; (m = *mp); mp = &m->rm_mklist)
        if (m == saved_m) {
            *mp = m->rm_mklist;
            squid_MKFree(m);
            break;
        }
    if (m == 0) {
        fprintf(stderr, "squid_rn_delete: couldn't find our annotation\n");
        if (tt->rn_flags & RNF_NORMAL)
            return (0);     /* Dangling ref to us */
    }
on1:
    /*
     * Eliminate us from tree
     */
    if (tt->rn_flags & RNF_ROOT)
        return (0);
#ifdef RN_DEBUG
    /* Get us out of the creation list */
    for (t = rn_clist; t && t->rn_ybro != tt; t = t->rn_ybro) {
    }
    if (t)
        t->rn_ybro = tt->rn_ybro;
#endif
    t = tt->rn_p;
    if ((dupedkey = saved_tt->rn_dupedkey)) {
        if (tt == saved_tt) {
            x = dupedkey;
            x->rn_p = t;
            if (t->rn_l == tt)
                t->rn_l = x;
            else
                t->rn_r = x;
        } else {
            for (x = p = saved_tt; p && p->rn_dupedkey != tt;)
                p = p->rn_dupedkey;
            if (p)
                p->rn_dupedkey = tt->rn_dupedkey;
            else
                fprintf(stderr, "squid_rn_delete: couldn't find us\n");
        }
        t = tt + 1;
        if (t->rn_flags & RNF_ACTIVE) {
#ifndef RN_DEBUG
            *++x = *t;
            p = t->rn_p;
#else
            b = t->rn_info;
            *++x = *t;
            t->rn_info = b;
            p = t->rn_p;
#endif
            if (p->rn_l == t)
                p->rn_l = x;
            else
                p->rn_r = x;
            x->rn_l->rn_p = x;
            x->rn_r->rn_p = x;
        }
        goto out;
    }
    if (t->rn_l == tt)
        x = t->rn_r;
    else
        x = t->rn_l;
    p = t->rn_p;
    if (p->rn_r == t)
        p->rn_r = x;
    else
        p->rn_l = x;
    x->rn_p = p;
    /*
     * Demote routes attached to us.
     */
    if (t->rn_mklist) {
        if (x->rn_b >= 0) {
            for (mp = &x->rn_mklist; (m = *mp);)
                mp = &m->rm_mklist;
            *mp = t->rn_mklist;
        } else {
            /* If there are any key,mask pairs in a sibling
             * duped-key chain, some subset will appear sorted
             * in the same order attached to our mklist */
            for (m = t->rn_mklist; m && x; x = x->rn_dupedkey)
                if (m == x->rn_mklist) {
                    struct squid_radix_mask *mm = m->rm_mklist;
                    x->rn_mklist = 0;
                    if (--(m->rm_refs) < 0)
                        squid_MKFree(m);
                    m = mm;
                }
#if RN_DEBUG
            if (m)
                fprintf(stderr, "%s %x at %x\n",
                        "squid_rn_delete: Orphaned Mask", (int) m, (int) x);
#else
            assert(m == NULL);
#endif
        }
    }
    /*
     * We may be holding an active internal node in the tree.
     */
    x = tt + 1;
    if (t != x) {
#ifndef RN_DEBUG
        *t = *x;
#else
        b = t->rn_info;
        *t = *x;
        t->rn_info = b;
#endif
        t->rn_l->rn_p = t;
        t->rn_r->rn_p = t;
        p = x->rn_p;
        if (p->rn_l == x)
            p->rn_l = t;
        else
            p->rn_r = t;
    }
out:
    tt->rn_flags &= ~RNF_ACTIVE;
    tt[1].rn_flags &= ~RNF_ACTIVE;
    return (tt);
}