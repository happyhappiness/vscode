    if (b->s->wupdated <= b->wupdated)
        return APR_SUCCESS;
    /* balancer sync */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, b->s->lbpname, "0");
    if (lbmethod) {
        b->lbmethod = lbmethod;
    }
    /* worker sync */

    /*
     * Look thru the list of workers in shm
     * and see which one(s) we are lacking...
     * again, the cast to unsigned int is safe
