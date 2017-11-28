struct squid_radix_node *
squid_rn_insert(void *v_arg, struct squid_radix_node_head *head, int *dupentry, struct squid_radix_node nodes[2]) {
    caddr_t v = v_arg;
    struct squid_radix_node *top = head->rnh_treetop;
    int head_off = top->rn_off, vlen = (int) *((u_char *) v);
    register struct squid_radix_node *t = squid_rn_search(v_arg, top);
    register caddr_t cp = v + head_off;
    register int b;
    struct squid_radix_node *tt;
    /*
     * Find first bit at which v and t->rn_key differ
     */
    {
        register caddr_t cp2 = t->rn_key + head_off;
        register int cmp_res;
        caddr_t cplim = v + vlen;

        while (cp < cplim)
            if (*cp2++ != *cp++)
                goto on1;
        *dupentry = 1;
        return t;
on1:
        *dupentry = 0;
        cmp_res = (cp[-1] ^ cp2[-1]) & 0xff;
        for (b = (cp - v) << 3; cmp_res; b--)
            cmp_res >>= 1;
    }
    {
        register struct squid_radix_node *p, *x = top;
        cp = v;
        do {
            p = x;
            if (cp[x->rn_off] & x->rn_bmask)
                x = x->rn_r;
            else
                x = x->rn_l;
        } while (b > (unsigned) x->rn_b);   /* x->rn_b < b && x->rn_b >= 0 */
#ifdef RN_DEBUG
        if (rn_debug)
            fprintf(stderr, "squid_rn_insert: Going In:\n");
        traverse(p);
#endif
        t = squid_rn_newpair(v_arg, b, nodes);
        tt = t->rn_l;
        if ((cp[p->rn_off] & p->rn_bmask) == 0)
            p->rn_l = t;
        else
            p->rn_r = t;
        x->rn_p = t;
        t->rn_p = p;        /* frees x, p as temp vars below */
        if ((cp[t->rn_off] & t->rn_bmask) == 0) {
            t->rn_r = x;
        } else {
            t->rn_r = tt;
            t->rn_l = x;
        }
#ifdef RN_DEBUG
        if (rn_debug)
            log(LOG_DEBUG, "squid_rn_insert: Coming Out:\n"), traverse(p);
#endif
    }
    return (tt);
}