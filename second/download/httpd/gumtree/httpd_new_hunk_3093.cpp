    APR_BRIGADE_INSERT_TAIL(brigade, e);
    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(brigade, e);
}

/*
 * Provide a string hashing function for the proxy.
 * We offer 2 methods: one is the APR model but we
 * also provide our own, based on either FNV or SDBM.
 * The reason is in case we want to use both to ensure no
 * collisions.
 */
PROXY_DECLARE(unsigned int)
ap_proxy_hashfunc(const char *str, proxy_hash_t method)
{
    if (method == PROXY_HASHFUNC_APR) {
        apr_ssize_t slen = strlen(str);
        return apr_hashfunc_default(str, &slen);
    }
    else if (method == PROXY_HASHFUNC_FNV) {
        /* FNV model */
        unsigned int hash;
        const unsigned int fnv_prime = 0x811C9DC5;
        for (hash = 0; *str; str++) {
            hash *= fnv_prime;
            hash ^= (*str);
        }
        return hash;
    }
    else { /* method == PROXY_HASHFUNC_DEFAULT */
        /* SDBM model */
        unsigned int hash;
        for (hash = 0; *str; str++) {
            hash = (*str) + (hash << 6) + (hash << 16) - hash;
        }
        return hash;
    }
}

PROXY_DECLARE(apr_status_t) ap_proxy_set_wstatus(char c, int set, proxy_worker *w)
{
    unsigned int *status = &w->s->status;
    char flag = toupper(c);
    struct wstat *pwt = wstat_tbl;
    while (pwt->bit) {
        if (flag == pwt->flag) {
            if (set)
                *status |= pwt->bit;
            else
                *status &= ~(pwt->bit);
            return APR_SUCCESS;
        }
        pwt++;
    }
    return APR_EINVAL;
}

PROXY_DECLARE(char *) ap_proxy_parse_wstatus(apr_pool_t *p, proxy_worker *w)
{
    char *ret = "";
    unsigned int status = w->s->status;
    struct wstat *pwt = wstat_tbl;
    while (pwt->bit) {
        if (status & pwt->bit)
            ret = apr_pstrcat(p, ret, pwt->name, NULL);
        pwt++;
    }
    if (PROXY_WORKER_IS_USABLE(w))
        ret = apr_pstrcat(p, ret, "Ok ", NULL);
    return ret;
}

PROXY_DECLARE(apr_status_t) ap_proxy_sync_balancer(proxy_balancer *b, server_rec *s,
                                                    proxy_server_conf *conf)
{
    proxy_worker **workers;
    int i;
    int index;
    proxy_worker_shared *shm;
    proxy_balancer_method *lbmethod;
    ap_slotmem_provider_t *storage = b->storage;

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
     * since our upper limit is always max_workers
     * which is int.
     */
    for (index = 0; index < b->max_workers; index++) {
        int found;
        apr_status_t rv;
        if ((rv = storage->dptr(b->wslot, (unsigned int)index, (void *)&shm)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00965) "worker slotmem_dptr failed");
            return APR_EGENERAL;
        }
        /* account for possible "holes" in the slotmem
         * (eg: slots 0-2 are used, but 3 isn't, but 4-5 is)
         */
        if (!shm->hash.def || !shm->hash.fnv)
            continue;
        found = 0;
        workers = (proxy_worker **)b->workers->elts;
        for (i = 0; i < b->workers->nelts; i++, workers++) {
            proxy_worker *worker = *workers;
            if (worker->hash.def == shm->hash.def && worker->hash.fnv == shm->hash.fnv) {
                found = 1;
                break;
            }
        }
        if (!found) {
            proxy_worker **runtime;
            runtime = apr_array_push(b->workers);
            *runtime = apr_palloc(conf->pool, sizeof(proxy_worker));
            (*runtime)->hash = shm->hash;
            (*runtime)->context = NULL;
            (*runtime)->cp = NULL;
            (*runtime)->balancer = b;
            (*runtime)->s = shm;
            (*runtime)->tmutex = NULL;
            if ((rv = ap_proxy_initialize_worker(*runtime, s, conf->pool)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00966) "Cannot init worker");
                return rv;
            }
        }
    }
    if (b->s->need_reset) {
        if (b->lbmethod && b->lbmethod->reset)
            b->lbmethod->reset(b, s);
        b->s->need_reset = 0;
    }
    b->wupdated = b->s->wupdated;
    return APR_SUCCESS;
}

void proxy_util_register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(ap_proxy_retry_worker);
}
