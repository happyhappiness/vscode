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
