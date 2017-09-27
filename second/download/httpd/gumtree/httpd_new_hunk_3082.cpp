    if (conn->worker->cp->pool) {
        apr_pool_destroy(conn->pool);
    }

    return APR_SUCCESS;
}

/*
 * WORKER related...
 */

PROXY_DECLARE(proxy_worker *) ap_proxy_get_worker(apr_pool_t *p,
                                                  proxy_balancer *balancer,
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

    url_length = strlen(url);
    url_copy = apr_pstrmemdup(p, url, url_length);

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
    /*
     * Do a "longest match" on the worker name to find the worker that
     * fits best to the URL, but keep in mind that we must have at least
     * a minimum matching of length min_match such that
     * scheme://hostname[:port] matches between worker and url.
     */

    if (balancer) {
        proxy_worker **workers = (proxy_worker **)balancer->workers->elts;
        for (i = 0; i < balancer->workers->nelts; i++, workers++) {
            worker = *workers;
            if ( ((worker_name_length = strlen(worker->s->name)) <= url_length)
                && (worker_name_length >= min_match)
                && (worker_name_length > max_match)
                && (strncmp(url_copy, worker->s->name, worker_name_length) == 0) ) {
                max_worker = worker;
                max_match = worker_name_length;
            }

        }
    } else {
        worker = (proxy_worker *)conf->workers->elts;
        for (i = 0; i < conf->workers->nelts; i++, worker++) {
            if ( ((worker_name_length = strlen(worker->s->name)) <= url_length)
                && (worker_name_length >= min_match)
                && (worker_name_length > max_match)
                && (strncmp(url_copy, worker->s->name, worker_name_length) == 0) ) {
                max_worker = worker;
                max_match = worker_name_length;
            }
        }
    }

    return max_worker;
}

/*
 * To create a worker from scratch first we define the
 * specifics of the worker; this is all local data.
 * We then allocate space for it if data needs to be
 * shared. This allows for dynamic addition during
 * config and runtime.
 */
PROXY_DECLARE(char *) ap_proxy_define_worker(apr_pool_t *p,
                                             proxy_worker **worker,
                                             proxy_balancer *balancer,
                                             proxy_server_conf *conf,
                                             const char *url,
                                             int do_malloc)
{
    int rv;
    apr_uri_t uri;
    proxy_worker_shared *wshared;
    char *ptr;

    rv = apr_uri_parse(p, url, &uri);

    if (rv != APR_SUCCESS) {
        return "Unable to parse URL";
    }
    if (!uri.hostname || !uri.scheme) {
        return "URL must be absolute!";
    }

    ap_str_tolower(uri.hostname);
    ap_str_tolower(uri.scheme);
    /*
     * Workers can be associated w/ balancers or on their
     * own; ie: the generic reverse-proxy or a worker
     * in a simple ProxyPass statement. eg:
     *
     *      ProxyPass / http://www.example.com
     *
     * in which case the worker goes in the conf slot.
     */
    if (balancer) {
        proxy_worker **runtime;
        /* recall that we get a ptr to the ptr here */
        runtime = apr_array_push(balancer->workers);
        *worker = *runtime = apr_palloc(p, sizeof(proxy_worker));   /* right to left baby */
        /* we've updated the list of workers associated with
         * this balancer *locally* */
        balancer->wupdated = apr_time_now();
    } else if (conf) {
        *worker = apr_array_push(conf->workers);
    } else {
        /* we need to allocate space here */
        *worker = apr_palloc(p, sizeof(proxy_worker));
    }

    memset(*worker, 0, sizeof(proxy_worker));
    /* right here we just want to tuck away the worker info.
     * if called during config, we don't have shm setup yet,
     * so just note the info for later. */
    if (do_malloc)
        wshared = ap_malloc(sizeof(proxy_worker_shared));  /* will be freed ap_proxy_share_worker */
    else
        wshared = apr_palloc(p, sizeof(proxy_worker_shared));

    memset(wshared, 0, sizeof(proxy_worker_shared));

    ptr = apr_uri_unparse(p, &uri, APR_URI_UNP_REVEALPASSWORD);
    if (PROXY_STRNCPY(wshared->name, ptr) != APR_SUCCESS) {
        return apr_psprintf(p, "worker name (%s) too long", ptr);
    }
    if (PROXY_STRNCPY(wshared->scheme, uri.scheme) != APR_SUCCESS) {
        return apr_psprintf(p, "worker scheme (%s) too long", uri.scheme);
    }
    if (PROXY_STRNCPY(wshared->hostname, uri.hostname) != APR_SUCCESS) {
        return apr_psprintf(p, "worker hostname (%s) too long", uri.hostname);
    }
    wshared->port = uri.port;
    wshared->flush_packets = flush_off;
    wshared->flush_wait = PROXY_FLUSH_WAIT;
    wshared->is_address_reusable = 1;
    wshared->lbfactor = 1;
    wshared->smax = -1;
    wshared->hash.def = ap_proxy_hashfunc(wshared->name, PROXY_HASHFUNC_DEFAULT);
    wshared->hash.fnv = ap_proxy_hashfunc(wshared->name, PROXY_HASHFUNC_FNV);
    wshared->was_malloced = (do_malloc != 0);

    (*worker)->hash = wshared->hash;
    (*worker)->context = NULL;
    (*worker)->cp = NULL;
    (*worker)->balancer = balancer;
    (*worker)->s = wshared;

    return NULL;
}

/*
 * Create an already defined worker and free up memory
 */
PROXY_DECLARE(apr_status_t) ap_proxy_share_worker(proxy_worker *worker, proxy_worker_shared *shm,
                                                  int i)
{
    if (!shm || !worker->s)
        return APR_EINVAL;

    memcpy(shm, worker->s, sizeof(proxy_worker_shared));
    if (worker->s->was_malloced)
        free(worker->s); /* was malloced in ap_proxy_define_worker */
    worker->s = shm;
    worker->s->index = i;
    return APR_SUCCESS;
}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s, apr_pool_t *p)
{
    apr_status_t rv = APR_SUCCESS;
    int mpm_threads;

    if (worker->s->status & PROXY_WORKER_INITIALIZED) {
        /* The worker is already initialized */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00924)
                     "worker %s shared already initialized", worker->s->name);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00925)
                     "initializing worker %s shared", worker->s->name);
        /* Set default parameters */
        if (!worker->s->retry_set) {
            worker->s->retry = apr_time_from_sec(PROXY_WORKER_DEFAULT_RETRY);
        }
        /* By default address is reusable unless DisableReuse is set */
        if (worker->s->disablereuse) {
            worker->s->is_address_reusable = 0;
        }
        else {
            worker->s->is_address_reusable = 1;
        }

        ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
        if (mpm_threads > 1) {
            /* Set hard max to no more then mpm_threads */
            if (worker->s->hmax == 0 || worker->s->hmax > mpm_threads) {
                worker->s->hmax = mpm_threads;
            }
            if (worker->s->smax == -1 || worker->s->smax > worker->s->hmax) {
                worker->s->smax = worker->s->hmax;
            }
            /* Set min to be lower then smax */
            if (worker->s->min > worker->s->smax) {
                worker->s->min = worker->s->smax;
            }
        }
        else {
            /* This will supress the apr_reslist creation */
            worker->s->min = worker->s->smax = worker->s->hmax = 0;
        }
    }

    /* What if local is init'ed and shm isn't?? Even possible? */
    if (worker->local_status & PROXY_WORKER_INITIALIZED) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00926)
                     "worker %s local already initialized", worker->s->name);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00927)
                     "initializing worker %s local", worker->s->name);
        /* Now init local worker data */
        if (worker->tmutex == NULL) {
            rv = apr_thread_mutex_create(&(worker->tmutex), APR_THREAD_MUTEX_DEFAULT, p);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00928)
                             "can not create worker thread mutex");
                return rv;
            }
        }
        if (worker->cp == NULL)
            init_conn_pool(p, worker);
        if (worker->cp == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00929)
                         "can not create connection pool");
            return APR_EGENERAL;
        }

        if (worker->s->hmax) {
            rv = apr_reslist_create(&(worker->cp->res),
                                    worker->s->min, worker->s->smax,
                                    worker->s->hmax, worker->s->ttl,
                                    connection_constructor, connection_destructor,
                                    worker, worker->cp->pool);

            apr_pool_cleanup_register(worker->cp->pool, (void *)worker,
                                      conn_pool_cleanup,
                                      apr_pool_cleanup_null);

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00930)
                "initialized pool in child %" APR_PID_T_FMT " for (%s) min=%d max=%d smax=%d",
                 getpid(), worker->s->hostname, worker->s->min,
                 worker->s->hmax, worker->s->smax);

            /* Set the acquire timeout */
            if (rv == APR_SUCCESS && worker->s->acquire_set) {
                apr_reslist_timeout_set(worker->cp->res, worker->s->acquire);
            }

        }
        else {
            void *conn;

            rv = connection_constructor(&conn, worker, worker->cp->pool);
            worker->cp->conn = conn;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00931)
                 "initialized single connection worker in child %" APR_PID_T_FMT " for (%s)",
                 getpid(), worker->s->hostname);
        }
    }
    if (rv == APR_SUCCESS) {
        worker->s->status |= (PROXY_WORKER_INITIALIZED);
        worker->local_status |= (PROXY_WORKER_INITIALIZED);
    }
    return rv;
}

static int ap_proxy_retry_worker(const char *proxy_function, proxy_worker *worker,
        server_rec *s)
{
    if (worker->s->status & PROXY_WORKER_IN_ERROR) {
        if (apr_time_now() > worker->s->error_time + worker->s->retry) {
            ++worker->s->retries;
            worker->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00932)
                         "%s: worker for (%s) has been marked for retry",
                         proxy_function, worker->s->hostname);
            return OK;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00933)
                         "%s: too soon to retry worker for (%s)",
                         proxy_function, worker->s->hostname);
            return DECLINED;
        }
    }
    else {
        return OK;
    }
}

PROXY_DECLARE(int) ap_proxy_pre_request(proxy_worker **worker,
                                        proxy_balancer **balancer,
                                        request_rec *r,
                                        proxy_server_conf *conf, char **url)
{
    int access_status;

    access_status = proxy_run_pre_request(worker, balancer, r, conf, url);
    if (access_status == DECLINED && *balancer == NULL) {
        *worker = ap_proxy_get_worker(r->pool, NULL, conf, *url);
        if (*worker) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "%s: found worker %s for %s",
                          (*worker)->s->scheme, (*worker)->s->name, *url);

            *balancer = NULL;
            access_status = OK;
        }
        else if (r->proxyreq == PROXYREQ_PROXY) {
            if (conf->forward) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "*: found forward proxy worker for %s", *url);
                *balancer = NULL;
                *worker = conf->forward;
                access_status = OK;
                /*
                 * The forward worker does not keep connections alive, so
                 * ensure that mod_proxy_http does the correct thing
                 * regarding the Connection header in the request.
                 */
                apr_table_setn(r->subprocess_env, "proxy-nokeepalive", "1");
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "*: found reverse proxy worker for %s", *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;
                /*
                 * The reverse worker does not keep connections alive, so
                 * ensure that mod_proxy_http does the correct thing
                 * regarding the Connection header in the request.
                 */
                apr_table_setn(r->subprocess_env, "proxy-nokeepalive", "1");
            }
        }
    }
    else if (access_status == DECLINED && *balancer != NULL) {
        /* All the workers are busy */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00934)
                      "all workers are busy.  Unable to serve %s", *url);
        access_status = HTTP_SERVICE_UNAVAILABLE;
    }
    return access_status;
}

PROXY_DECLARE(int) ap_proxy_post_request(proxy_worker *worker,
                                         proxy_balancer *balancer,
                                         request_rec *r,
                                         proxy_server_conf *conf)
{
    int access_status = OK;
    if (balancer) {
        access_status = proxy_run_post_request(worker, balancer, r, conf);
        if (access_status == DECLINED) {
            access_status = OK; /* no post_request handler available */
            /* TODO: recycle direct worker */
        }
    }

    return access_status;
}

/* DEPRECATED */
PROXY_DECLARE(int) ap_proxy_connect_to_backend(apr_socket_t **newsock,
                                               const char *proxy_function,
                                               apr_sockaddr_t *backend_addr,
                                               const char *backend_name,
                                               proxy_server_conf *conf,
                                               request_rec *r)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;

    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(newsock, backend_addr->family,
                                    SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r, APLOGNO(00935)
                          "%s: error creating fam %d socket for target %s",
                          proxy_function, backend_addr->family, backend_name);
            /*
             * this could be an IPv6 address from the DNS but the
             * local machine won't give us an IPv6 socket; hopefully the
             * DNS returned an additional address to try
             */
            backend_addr = backend_addr->next;
            continue;
        }

        if (conf->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(*newsock, APR_SO_RCVBUF,
                                     conf->recv_buffer_size))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00936)
                          "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                          "ProxyReceiveBufferSize, using default");
        }

        rv = apr_socket_opt_set(*newsock, APR_TCP_NODELAY, 1);
        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00937)
                          "apr_socket_opt_set(APR_TCP_NODELAY): "
                          "Failed to set");
        }

        /* Set a timeout on the socket */
        if (conf->timeout_set) {
            apr_socket_timeout_set(*newsock, conf->timeout);
        }
        else {
            apr_socket_timeout_set(*newsock, r->server->timeout);
        }

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "%s: fam %d socket created to connect to %s",
                      proxy_function, backend_addr->family, backend_name);

        if (conf->source_address) {
            rv = apr_socket_bind(*newsock, conf->source_address);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00938)
                              "%s: failed to bind socket to local address",
                              proxy_function);
            }
        }

        /* make the connection out of the socket */
        rv = apr_socket_connect(*newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r, APLOGNO(00939)
                          "%s: attempt to connect to %pI (%s) failed",
                          proxy_function, backend_addr, backend_name);
            backend_addr = backend_addr->next;
            continue;
        }
        connected = 1;
    }
    return connected ? 0 : 1;
}

PROXY_DECLARE(int) ap_proxy_acquire_connection(const char *proxy_function,
                                               proxy_conn_rec **conn,
                                               proxy_worker *worker,
                                               server_rec *s)
{
    apr_status_t rv;

    if (!PROXY_WORKER_IS_USABLE(worker)) {
        /* Retry the worker */
        ap_proxy_retry_worker(proxy_function, worker, s);

        if (!PROXY_WORKER_IS_USABLE(worker)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00940)
                         "%s: disabled connection for (%s)",
                         proxy_function, worker->s->hostname);
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }

    if (worker->s->hmax && worker->cp->res) {
        rv = apr_reslist_acquire(worker->cp->res, (void **)conn);
    }
    else {
        /* create the new connection if the previous was destroyed */
        if (!worker->cp->conn) {
            connection_constructor((void **)conn, worker, worker->cp->pool);
        }
        else {
            *conn = worker->cp->conn;
            worker->cp->conn = NULL;
        }
        rv = APR_SUCCESS;
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00941)
                     "%s: failed to acquire connection for (%s)",
                     proxy_function, worker->s->hostname);
        return HTTP_SERVICE_UNAVAILABLE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00942)
                 "%s: has acquired connection for (%s)",
                 proxy_function, worker->s->hostname);

    (*conn)->worker = worker;
    (*conn)->close  = 0;
    (*conn)->inreslist = 0;

    return OK;
}

PROXY_DECLARE(int) ap_proxy_release_connection(const char *proxy_function,
                                               proxy_conn_rec *conn,
                                               server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00943)
                "%s: has released connection for (%s)",
                proxy_function, conn->worker->s->hostname);
    connection_cleanup(conn);

    return OK;
}

PROXY_DECLARE(int)
