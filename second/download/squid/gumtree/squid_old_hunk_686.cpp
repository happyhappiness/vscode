        do {
            p = x;
            if (cp[x->rn_off] & x->rn_bmask)
                x = x->rn_r;
            else
                x = x->rn_l;
        } while (b > (unsigned) x->rn_b);	/* x->rn_b < b && x->rn_b >= 0 */
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
        t->rn_p = p;		/* frees x, p as temp vars below */
        if ((cp[t->rn_off] & t->rn_bmask) == 0) {
            t->rn_r = x;
        } else {
            t->rn_r = tt;
            t->rn_l = x;
        }
