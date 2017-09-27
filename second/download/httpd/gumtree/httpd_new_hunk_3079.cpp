     */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, "byrequests", "0");
    if (!lbmethod) {
        return "Can't find 'byrequests' lb method";
    }

    (*balancer)->workers = apr_array_make(p, 5, sizeof(proxy_worker *));
    (*balancer)->gmutex = NULL;
    (*balancer)->tmutex = NULL;
    (*balancer)->lbmethod = lbmethod;

    if (do_malloc)
        bshared = ap_malloc(sizeof(proxy_balancer_shared));
    else
        bshared = apr_palloc(p, sizeof(proxy_balancer_shared));

    memset(bshared, 0, sizeof(proxy_balancer_shared));

    bshared->was_malloced = (do_malloc != 0);
    PROXY_STRNCPY(bshared->lbpname, "byrequests");
    if (PROXY_STRNCPY(bshared->name, uri) != APR_SUCCESS) {
        return apr_psprintf(p, "balancer name (%s) too long", uri);
    }
    ap_pstr2_alnum(p, bshared->name + sizeof(BALANCER_PREFIX) - 1,
                   &sname);
    sname = apr_pstrcat(p, conf->id, "_", sname, NULL);
    if (PROXY_STRNCPY(bshared->sname, sname) != APR_SUCCESS) {
        return apr_psprintf(p, "balancer safe-name (%s) too long", sname);
    }
    bshared->hash.def = ap_proxy_hashfunc(bshared->name, PROXY_HASHFUNC_DEFAULT);
    bshared->hash.fnv = ap_proxy_hashfunc(bshared->name, PROXY_HASHFUNC_FNV);
    (*balancer)->hash = bshared->hash;

    /* Retrieve a UUID and store the nonce for the lifetime of
     * the process. */
    apr_uuid_get(&uuid);
    apr_uuid_format(nonce, &uuid);
    if (PROXY_STRNCPY(bshared->nonce, nonce) != APR_SUCCESS) {
        return apr_psprintf(p, "balancer nonce (%s) too long", nonce);
    }

    (*balancer)->s = bshared;
    (*balancer)->sconf = conf;

    return ap_proxy_update_balancer(p, *balancer, alias);
}

/*
 * Create an already defined balancer and free up memory.
 */
PROXY_DECLARE(apr_status_t) ap_proxy_share_balancer(proxy_balancer *balancer,
                                                    proxy_balancer_shared *shm,
                                                    int i)
{
    proxy_balancer_method *lbmethod;
    if (!shm || !balancer->s)
        return APR_EINVAL;

    memcpy(shm, balancer->s, sizeof(proxy_balancer_shared));
    if (balancer->s->was_malloced)
        free(balancer->s);
    balancer->s = shm;
    balancer->s->index = i;
    /* the below should always succeed */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, balancer->s->lbpname, "0");
    if (lbmethod)
        balancer->lbmethod = lbmethod;
    return APR_SUCCESS;
}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_balancer(proxy_balancer *balancer, server_rec *s, apr_pool_t *p)
{
    apr_status_t rv = APR_SUCCESS;
    ap_slotmem_provider_t *storage = balancer->storage;
    apr_size_t size;
    unsigned int num;

    if (!storage) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00918)
                     "no provider for %s", balancer->s->name);
        return APR_EGENERAL;
    }
    /*
     * for each balancer we need to init the global
     * mutex and then attach to the shared worker shm
     */
    if (!balancer->gmutex) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00919)
                     "no mutex %s", balancer->s->name);
        return APR_EGENERAL;
    }

    /* Re-open the mutex for the child. */
    rv = apr_global_mutex_child_init(&(balancer->gmutex),
                                     apr_global_mutex_lockfile(balancer->gmutex),
                                     p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00920)
                     "Failed to reopen mutex %s in child",
                     balancer->s->name);
        return rv;
    }

    /* now attach */
    storage->attach(&(balancer->wslot), balancer->s->sname, &size, &num, p);
    if (!balancer->wslot) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00921) "slotmem_attach failed");
        return APR_EGENERAL;
    }
    if (balancer->lbmethod && balancer->lbmethod->reset)
        balancer->lbmethod->reset(balancer, s);

    if (balancer->tmutex == NULL) {
        rv = apr_thread_mutex_create(&(balancer->tmutex), APR_THREAD_MUTEX_DEFAULT, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(00922)
                         "can not create balancer thread mutex");
            return rv;
        }
    }
    return APR_SUCCESS;
}

/*
 * CONNECTION related...
 */

static apr_status_t conn_pool_cleanup(void *theworker)
{
    proxy_worker *worker = (proxy_worker *)theworker;
    if (worker->cp->res) {
        worker->cp->pool = NULL;
    }
    return APR_SUCCESS;
}

static void init_conn_pool(apr_pool_t *p, proxy_worker *worker)
{
    apr_pool_t *pool;
    proxy_conn_pool *cp;

