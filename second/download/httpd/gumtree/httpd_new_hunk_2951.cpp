        cur_lbset++;

    } while (cur_lbset <= max_lbset && !mycandidate);

    if (mycandidate) {
        mycandidate->s->lbstatus -= total_factor;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01212)
                     "proxy: bybusyness selected worker \"%s\" : busy %" APR_SIZE_T_FMT " : lbstatus %d",
                     mycandidate->s->name, mycandidate->s->busy, mycandidate->s->lbstatus);

    }

    return mycandidate;

}

/* assumed to be mutex protected by caller */
static apr_status_t reset(proxy_balancer *balancer, server_rec *s) {
    int i;
    proxy_worker **worker;
    worker = (proxy_worker **)balancer->workers->elts;
    for (i = 0; i < balancer->workers->nelts; i++, worker++) {
        (*worker)->s->lbstatus = 0;
        (*worker)->s->busy = 0;
    }
    return APR_SUCCESS;
}

static apr_status_t age(proxy_balancer *balancer, server_rec *s) {
        return APR_SUCCESS;
}

