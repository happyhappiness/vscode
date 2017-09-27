     */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, "byrequests", "0");
    if (!lbmethod) {
        return "Can't find 'byrequests' lb method";
    }

    (*balancer)->name = uri;
    (*balancer)->lbmethod = lbmethod;
    (*balancer)->workers = apr_array_make(p, 5, sizeof(proxy_worker *));
    (*balancer)->updated = apr_time_now();
    /* XXX Is this a right place to create mutex */
#if APR_HAS_THREADS
    if (apr_thread_mutex_create(&((*balancer)->mutex),
                APR_THREAD_MUTEX_DEFAULT, p) != APR_SUCCESS) {
        /* XXX: Do we need to log something here */
        return "can not create thread mutex";
    }
#endif

    return NULL;
}

PROXY_DECLARE(proxy_worker *) ap_proxy_get_worker(apr_pool_t *p,
                                                  proxy_server_conf *conf,
                                                  const char *url)
{
    proxy_worker *worker;
    proxy_worker *max_worker = NULL;
    int max_match = 0;
    int url_length;
    int min_match;
    int worker_name_length;
    const char *c;
    char *url_copy;
    int i;

    c = ap_strchr_c(url, ':');
    if (c == NULL || c[1] != '/' || c[2] != '/' || c[3] == '\0') {
       return NULL;
    }

    url_copy = apr_pstrdup(p, url);
    url_length = strlen(url);

    /*
     * We need to find the start of the path and
     * therefore we know the length of the scheme://hostname/
     * part to we can force-lowercase everything up to
     * the start of the path.
     */
    c = ap_strchr_c(c+3, '/');
    if (c) {
        char *pathstart;
        pathstart = url_copy + (c - url);
        *pathstart = '\0';
        ap_str_tolower(url_copy);
        min_match = strlen(url_copy);
        *pathstart = '/';
    }
    else {
        ap_str_tolower(url_copy);
        min_match = strlen(url_copy);
    }

    worker = (proxy_worker *)conf->workers->elts;

    /*
     * Do a "longest match" on the worker name to find the worker that
     * fits best to the URL, but keep in mind that we must have at least
     * a minimum matching of length min_match such that
     * scheme://hostname[:port] matches between worker and url.
     */
    for (i = 0; i < conf->workers->nelts; i++) {
        if ( ((worker_name_length = strlen(worker->name)) <= url_length)
           && (worker_name_length >= min_match)
           && (worker_name_length > max_match)
           && (strncmp(url_copy, worker->name, worker_name_length) == 0) ) {
            max_worker = worker;
            max_match = worker_name_length;
        }
        worker++;
    }
    return max_worker;
}

#if APR_HAS_THREADS
static apr_status_t conn_pool_cleanup(void *theworker)
{
    proxy_worker *worker = (proxy_worker *)theworker;
    if (worker->cp->res) {
        worker->cp->pool = NULL;
    }
    return APR_SUCCESS;
}
#endif

static void init_conn_pool(apr_pool_t *p, proxy_worker *worker)
{
    apr_pool_t *pool;
    proxy_conn_pool *cp;

