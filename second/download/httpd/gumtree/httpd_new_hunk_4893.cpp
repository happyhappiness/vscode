    if (b->s->wupdated <= b->wupdated)
        return APR_SUCCESS;
    /* balancer sync */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, b->s->lbpname, "0");
    if (lbmethod) {
        b->lbmethod = lbmethod;
    } else {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(02433)
                     "Cannot find LB Method: %s", b->s->lbpname);
        return APR_EINVAL;
    }

    /* worker sync */

    /*
     * Look thru the list of workers in shm
     * and see which one(s) we are lacking...
     * again, the cast to unsigned int is safe
