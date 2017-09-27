        }
        count++;
    }
    apr_table_add(t, key, value + offset);
}

PROXY_DECLARE(const char *) ap_proxy_location_reverse_map(request_rec *r,
                              proxy_dir_conf *conf, const char *url)
{
    struct proxy_alias *ent;
    int i, l1, l2;
    char *u;

    /*
     * XXX FIXME: Make sure this handled the ambiguous case of the :<PORT>
     * after the hostname
     */

    l1 = strlen(url);
    ent = (struct proxy_alias *)conf->raliases->elts;
    for (i = 0; i < conf->raliases->nelts; i++) {
        l2 = strlen(ent[i].real);
        if (l1 >= l2 && strncasecmp(ent[i].real, url, l2) == 0) {
            u = apr_pstrcat(r->pool, ent[i].fake, &url[l2], NULL);
            return ap_construct_url(r->pool, u, r);
        }
    }

    return url;
}

/*
 * Cookies are a bit trickier to match: we've got two substrings to worry
 * about, and we can't just find them with strstr 'cos of case.  Regexp
 * matching would be an easy fix, but for better consistency with all the
 * other matches we'll refrain and use apr_strmatch to find path=/domain=
 * and stick to plain strings for the config values.
 */
PROXY_DECLARE(const char *) ap_proxy_cookie_reverse_map(request_rec *r,
                              proxy_dir_conf *conf, const char *str)
{
    struct proxy_alias *ent;
    size_t len = strlen(str);
    const char *newpath = NULL;
    const char *newdomain = NULL;
    const char *pathp;
    const char *domainp;
    const char *pathe = NULL;
    const char *domaine = NULL;
    size_t l1, l2, poffs = 0, doffs = 0;
    int i;
    int ddiff = 0;
    int pdiff = 0;
    char *ret;

   /*
    * Find the match and replacement, but save replacing until we've done
    * both path and domain so we know the new strlen
    */
    if ((pathp = apr_strmatch(conf->cookie_path_str, str, len)) != NULL) {
        pathp += 5;
        poffs = pathp - str;
        pathe = ap_strchr_c(pathp, ';');
        l1 = pathe ? (pathe - pathp) : strlen(pathp);
        pathe = pathp + l1 ;
        ent = (struct proxy_alias *)conf->cookie_paths->elts;
        for (i = 0; i < conf->cookie_paths->nelts; i++) {
            l2 = strlen(ent[i].fake);
            if (l1 >= l2 && strncmp(ent[i].fake, pathp, l2) == 0) {
                newpath = ent[i].real;
                pdiff = strlen(newpath) - l1;
                break;
            }
        }
    }

    if ((domainp = apr_strmatch(conf->cookie_domain_str, str, len)) != NULL) {
        domainp += 7;
        doffs = domainp - str;
        domaine = ap_strchr_c(domainp, ';');
        l1 = domaine ? (domaine - domainp) : strlen(domainp);
        domaine = domainp + l1;
        ent = (struct proxy_alias *)conf->cookie_domains->elts;
        for (i = 0; i < conf->cookie_domains->nelts; i++) {
            l2 = strlen(ent[i].fake);
            if (l1 >= l2 && strncasecmp(ent[i].fake, domainp, l2) == 0) {
                newdomain = ent[i].real;
                ddiff = strlen(newdomain) - l1;
                break;
            }
        }
    }

    if (newpath) {
        ret = apr_palloc(r->pool, len + pdiff + ddiff + 1);
        l1 = strlen(newpath);
        if (newdomain) {
            l2 = strlen(newdomain);
            if (doffs > poffs) {
                memcpy(ret, str, poffs);
                memcpy(ret + poffs, newpath, l1);
                memcpy(ret + poffs + l1, pathe, domainp - pathe);
                memcpy(ret + doffs + pdiff, newdomain, l2);
                strcpy(ret + doffs + pdiff + l2, domaine);
            }
            else {
                memcpy(ret, str, doffs) ;
                memcpy(ret + doffs, newdomain, l2);
                memcpy(ret + doffs + l2, domaine, pathp - domaine);
                memcpy(ret + poffs + ddiff, newpath, l1);
                strcpy(ret + poffs + ddiff + l1, pathe);
            }
        }
        else {
            memcpy(ret, str, poffs);
            memcpy(ret + poffs, newpath, l1);
            strcpy(ret + poffs + l1, pathe);
        }
    }
    else {
        if (newdomain) {
            ret = apr_palloc(r->pool, len + pdiff + ddiff + 1);
            l2 = strlen(newdomain);
            memcpy(ret, str, doffs);
            memcpy(ret + doffs, newdomain, l2);
            strcpy(ret + doffs+l2, domaine);
        }
        else {
            ret = (char *)str; /* no change */
        }
    }

    return ret;
}

PROXY_DECLARE(proxy_balancer *) ap_proxy_get_balancer(apr_pool_t *p,
                                                      proxy_server_conf *conf,
                                                      const char *url)
{
    proxy_balancer *balancer;
    char *c, *uri = apr_pstrdup(p, url);
    int i;

    c = strchr(uri, ':');
    if (c == NULL || c[1] != '/' || c[2] != '/' || c[3] == '\0')
       return NULL;
    /* remove path from uri */
    if ((c = strchr(c + 3, '/')))
        *c = '\0';
    balancer = (proxy_balancer *)conf->balancers->elts;
    for (i = 0; i < conf->balancers->nelts; i++) {
        if (strcasecmp(balancer->name, uri) == 0)
            return balancer;
        balancer++;
    }
    return NULL;
}

PROXY_DECLARE(const char *) ap_proxy_add_balancer(proxy_balancer **balancer,
                                                  apr_pool_t *p,
                                                  proxy_server_conf *conf,
                                                  const char *url)
{
    char *c, *q, *uri = apr_pstrdup(p, url);
    proxy_balancer_method *lbmethod;

    c = strchr(uri, ':');
    if (c == NULL || c[1] != '/' || c[2] != '/' || c[3] == '\0')
       return "Bad syntax for a balancer name";
    /* remove path from uri */
    if ((q = strchr(c + 3, '/')))
        *q = '\0';

    ap_str_tolower(uri);
    *balancer = apr_array_push(conf->balancers);
    memset(*balancer, 0, sizeof(proxy_balancer));

    /*
     * NOTE: The default method is byrequests, which we assume
     * exists!
     */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, "byrequests", "0");
    if (!lbmethod) {
        return "Can't find 'byrequests' lb method";
    }

    (*balancer)->name = uri;
    (*balancer)->lbmethod = lbmethod;
    (*balancer)->workers = apr_array_make(p, 5, sizeof(proxy_worker));
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
    int worker_name_length;
    const char *c;
    char *url_copy;
    int i;

    c = ap_strchr_c(url, ':');
    if (c == NULL || c[1] != '/' || c[2] != '/' || c[3] == '\0')
       return NULL;

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
        *pathstart = '/';
    } else {
        ap_str_tolower(url_copy);
    }

    worker = (proxy_worker *)conf->workers->elts;

    /*
     * Do a "longest match" on the worker name to find the worker that
     * fits best to the URL.
     */
    for (i = 0; i < conf->workers->nelts; i++) {
        if ( ((worker_name_length = strlen(worker->name)) <= url_length)
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
        apr_reslist_destroy(worker->cp->res);
    }
    return APR_SUCCESS;
}
#endif

static void init_conn_pool(apr_pool_t *p, proxy_worker *worker)
{
    apr_pool_t *pool;
    proxy_conn_pool *cp;

    /*
     * Create a connection pool's subpool.
     * This pool is used for connection recycling.
     * Once the worker is added it is never removed but
     * it can be disabled.
     */
    apr_pool_create(&pool, p);
    /*
     * Alloc from the same pool as worker.
     * proxy_conn_pool is permanently attached to the worker.
     */
    cp = (proxy_conn_pool *)apr_pcalloc(p, sizeof(proxy_conn_pool));
    cp->pool = pool;
    worker->cp = cp;
}

PROXY_DECLARE(const char *) ap_proxy_add_worker(proxy_worker **worker,
                                                apr_pool_t *p,
                                                proxy_server_conf *conf,
                                                const char *url)
{
    int rv;
    apr_uri_t uri;

    rv = apr_uri_parse(p, url, &uri);

    if (rv != APR_SUCCESS) {
        return "Unable to parse URL";
    }

    ap_str_tolower(uri.hostname);
    ap_str_tolower(uri.scheme);
    *worker = apr_array_push(conf->workers);
    memset(*worker, 0, sizeof(proxy_worker));
    (*worker)->name = apr_uri_unparse(p, &uri, APR_URI_UNP_REVEALPASSWORD);
    (*worker)->scheme = uri.scheme;
    (*worker)->hostname = uri.hostname;
    (*worker)->port = uri.port;
    (*worker)->id   = proxy_lb_workers;
    /* Increase the total worker count */
    proxy_lb_workers++;
    init_conn_pool(p, *worker);
#if APR_HAS_THREADS
    if (apr_thread_mutex_create(&((*worker)->mutex),
                APR_THREAD_MUTEX_DEFAULT, p) != APR_SUCCESS) {
        /* XXX: Do we need to log something here */
        return "can not create thread mutex";
    }
#endif

    return NULL;
}

PROXY_DECLARE(proxy_worker *) ap_proxy_create_worker(apr_pool_t *p)
{

    proxy_worker *worker;
    worker = (proxy_worker *)apr_pcalloc(p, sizeof(proxy_worker));
    worker->id = proxy_lb_workers;
    /* Increase the total worker count */
    proxy_lb_workers++;
    init_conn_pool(p, worker);

    return worker;
}

PROXY_DECLARE(void)
ap_proxy_add_worker_to_balancer(apr_pool_t *pool, proxy_balancer *balancer,
                                proxy_worker *worker)
{
    proxy_worker *runtime;

    runtime = apr_array_push(balancer->workers);
    memcpy(runtime, worker, sizeof(proxy_worker));
    runtime->id = proxy_lb_workers;
    /* Increase the total runtime count */
    proxy_lb_workers++;

}

PROXY_DECLARE(int) ap_proxy_pre_request(proxy_worker **worker,
                                        proxy_balancer **balancer,
                                        request_rec *r,
                                        proxy_server_conf *conf, char **url)
{
    int access_status;

    access_status = proxy_run_pre_request(worker, balancer, r, conf, url);
    if (access_status == DECLINED && *balancer == NULL) {
        *worker = ap_proxy_get_worker(r->pool, conf, *url);
        if (*worker) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: %s: found worker %s for %s",
                           (*worker)->scheme, (*worker)->name, *url);

            *balancer = NULL;
            access_status = OK;
        }
        else if (r->proxyreq == PROXYREQ_PROXY) {
            if (conf->forward) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: *: found forward proxy worker for %s",
                               *url);
                *balancer = NULL;
                *worker = conf->forward;
                access_status = OK;
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: *: found reverse proxy worker for %s",
                               *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;
            }
        }
    }
    else if (access_status == DECLINED && *balancer != NULL) {
        /* All the workers are busy */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
          "proxy: all workers are busy.  Unable to serve %s",
          *url);
        access_status = HTTP_SERVICE_UNAVAILABLE;
    }
    return access_status;
}

PROXY_DECLARE(int) ap_proxy_post_request(proxy_worker *worker,
                                         proxy_balancer *balancer,
                                         request_rec *r,
                                         proxy_server_conf *conf)
{
    int access_status;
    if (balancer)
        access_status = proxy_run_post_request(worker, balancer, r, conf);
    else {


        access_status = OK;
    }

    return access_status;
}

/* DEPRECATED */
PROXY_DECLARE(int) ap_proxy_connect_to_backend(apr_socket_t **newsock,
                                               const char *proxy_function,
                                               apr_sockaddr_t *backend_addr,
                                               const char *backend_name,
                                               proxy_server_conf *conf,
                                               server_rec *s,
                                               apr_pool_t *p)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;

    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(newsock, backend_addr->family,
                                    SOCK_STREAM, 0, p)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: error creating fam %d socket for target %s",
                         proxy_function,
                         backend_addr->family,
                         backend_name);
            /*
             * this could be an IPv6 address from the DNS but the
             * local machine won't give us an IPv6 socket; hopefully the
             * DNS returned an additional address to try
             */
            backend_addr = backend_addr->next;
            continue;
        }
