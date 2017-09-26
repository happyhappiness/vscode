            continue;
        }
        connected = 1;
    }
    return connected ? 0 : 1;
}

static apr_status_t connection_cleanup(void *theconn)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)theconn;
    proxy_worker *worker = conn->worker;

    /*
     * If the connection pool is NULL the worker
     * cleanup has been run. Just return.
     */
    if (!worker->cp)
        return APR_SUCCESS;

    /* deterimine if the connection need to be closed */
    if (conn->close_on_recycle || conn->close) {
        apr_pool_t *p = conn->pool;
        apr_pool_clear(conn->pool);
        memset(conn, 0, sizeof(proxy_conn_rec));
        conn->pool = p;
        conn->worker = worker;
    }
#if APR_HAS_THREADS
    if (worker->hmax && worker->cp->res) {
        apr_reslist_release(worker->cp->res, (void *)conn);
    }
    else
#endif
    {
        worker->cp->conn = conn;
    }

    /* Allways return the SUCCESS */
    return APR_SUCCESS;
}

/* reslist constructor */
static apr_status_t connection_constructor(void **resource, void *params,
                                           apr_pool_t *pool)
{
    apr_pool_t *ctx;
    proxy_conn_rec *conn;
    proxy_worker *worker = (proxy_worker *)params;

    /*
     * Create the subpool for each connection
     * This keeps the memory consumption constant
     * when disconnecting from backend.
     */
    apr_pool_create(&ctx, pool);
    conn = apr_pcalloc(pool, sizeof(proxy_conn_rec));

    conn->pool   = ctx;
    conn->worker = worker;
    *resource = conn;

    return APR_SUCCESS;
}

#if APR_HAS_THREADS /* only needed when threads are used */
/* reslist destructor */
static apr_status_t connection_destructor(void *resource, void *params,
                                          apr_pool_t *pool)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)resource;

    /* Destroy the pool only if not called from reslist_destroy */
    if (conn->worker->cp->pool)
        apr_pool_destroy(conn->pool);

    return APR_SUCCESS;
}
#endif

PROXY_DECLARE(void) ap_proxy_initialize_worker_share(proxy_server_conf *conf,
                                                     proxy_worker *worker,
                                                     server_rec *s)
{
#if PROXY_HAS_SCOREBOARD
    lb_score *score = NULL;
#else
    void *score = NULL;
#endif

    if (worker->s && worker->s->status & PROXY_WORKER_INITIALIZED) {
        /* The worker share is already initialized */
        return;
    }
#if PROXY_HAS_SCOREBOARD
        /* Get scoreboard slot */
    if (ap_scoreboard_image) {
        score = ap_get_scoreboard_lb(worker->id);
    if (!score)
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
              "proxy: ap_get_scoreboard_lb(%d) failed for worker %s",
              worker->id, worker->name);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: initialized scoreboard slot %d for worker %s",
              worker->id, worker->name);
    }
#endif
    if (!score) {
        score = apr_pcalloc(conf->pool, sizeof(proxy_worker_stat));
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: initialized plain memory for worker %s",
              worker->name);
    }
    worker->s = (proxy_worker_stat *)score;
    if (worker->route)
        strcpy(worker->s->route, worker->route);
    else
        *worker->s->route = '\0';
    if (worker->redirect)
        strcpy(worker->s->redirect, worker->redirect);
    else
        *worker->s->redirect = '\0';
    /* Set default parameters */
    if (!worker->retry)
        worker->retry = apr_time_from_sec(PROXY_WORKER_DEFAULT_RETRY);
    /* By default address is reusable */
    worker->is_address_reusable = 1;

}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_worker(proxy_worker *worker, server_rec *s)
{
    apr_status_t rv;

#if APR_HAS_THREADS
    int mpm_threads;
#endif

    if (worker->s->status & PROXY_WORKER_INITIALIZED) {
        /* The worker is already initialized */
        return APR_SUCCESS;
    }

#if APR_HAS_THREADS
    ap_mpm_query(AP_MPMQ_MAX_THREADS, &mpm_threads);
    if (mpm_threads > 1) {
        /* Set hard max to no more then mpm_threads */
        if (worker->hmax == 0 || worker->hmax > mpm_threads)
            worker->hmax = mpm_threads;
        if (worker->smax == 0 || worker->smax > worker->hmax)
            worker->smax = worker->hmax;
        /* Set min to be lower then smax */
        if (worker->min > worker->smax)
            worker->min = worker->smax;
    }
    else {
        /* This will supress the apr_reslist creation */
        worker->min = worker->smax = worker->hmax = 0;
    }
    if (worker->hmax) {
        rv = apr_reslist_create(&(worker->cp->res),
                                worker->min, worker->smax,
                                worker->hmax, worker->ttl,
                                connection_constructor, connection_destructor,
                                worker, worker->cp->pool);

        apr_pool_cleanup_register(worker->cp->pool, (void *)worker,
                                  conn_pool_cleanup,
                                  apr_pool_cleanup_null);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
            "proxy: initialized worker %d in child %" APR_PID_T_FMT " for (%s) min=%d max=%d smax=%d",
             worker->id, getpid(), worker->hostname, worker->min,
             worker->hmax, worker->smax);

#if (APR_MAJOR_VERSION > 0)
        /* Set the acquire timeout */
        if (rv == APR_SUCCESS && worker->acquire_set)
            apr_reslist_timeout_set(worker->cp->res, worker->acquire);
#endif
    }
    else
#endif
    {

        rv = connection_constructor((void **)&(worker->cp->conn), worker, worker->cp->pool);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
             "proxy: initialized single connection worker %d in child %" APR_PID_T_FMT " for (%s)",
             worker->id, getpid(), worker->hostname);
    }
    if (rv == APR_SUCCESS)
        worker->s->status |= (worker->status | PROXY_WORKER_INITIALIZED);
    return rv;
}

PROXY_DECLARE(int) ap_proxy_retry_worker(const char *proxy_function,
                                         proxy_worker *worker,
                                         server_rec *s)
{
    if (worker->s->status & PROXY_WORKER_IN_ERROR) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                    "proxy: %s: retrying the worker for (%s)",
                     proxy_function, worker->hostname);
        if (apr_time_now() > worker->s->error_time + worker->retry) {
            ++worker->s->retries;
            worker->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: %s: worker for (%s) has been marked for retry",
                         proxy_function, worker->hostname);
            return OK;
        }
        else
            return DECLINED;
    }
    else
        return OK;
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
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "proxy: %s: disabled connection for (%s)",
                         proxy_function, worker->hostname);
            return HTTP_SERVICE_UNAVAILABLE;
        }
    }
#if APR_HAS_THREADS
    if (worker->hmax && worker->cp->res) {
        rv = apr_reslist_acquire(worker->cp->res, (void **)conn);
    }
    else
#endif
    {
        /* create the new connection if the previous was destroyed */
        if (!worker->cp->conn)
            connection_constructor((void **)conn, worker, worker->cp->pool);
        else {
            *conn = worker->cp->conn;
            worker->cp->conn = NULL;
        }
        rv = APR_SUCCESS;
    }

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "proxy: %s: failed to acquire connection for (%s)",
                     proxy_function, worker->hostname);
        return HTTP_SERVICE_UNAVAILABLE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: has acquired connection for (%s)",
                 proxy_function, worker->hostname);

    (*conn)->worker = worker;
    (*conn)->close  = 0;
    (*conn)->close_on_recycle = 0;

    return OK;
}

PROXY_DECLARE(int) ap_proxy_release_connection(const char *proxy_function,
                                               proxy_conn_rec *conn,
                                               server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: has released connection for (%s)",
                 proxy_function, conn->worker->hostname);
    /* If there is a connection kill it's cleanup */
    if (conn->connection) {
        apr_pool_cleanup_kill(conn->connection->pool, conn, connection_cleanup);
        conn->connection = NULL;
    }
    connection_cleanup(conn);

    return OK;
}

PROXY_DECLARE(int)
ap_proxy_determine_connection(apr_pool_t *p, request_rec *r,
                              proxy_server_conf *conf,
                              proxy_worker *worker,
                              proxy_conn_rec *conn,
                              apr_uri_t *uri,
                              char **url,
                              const char *proxyname,
                              apr_port_t proxyport,
                              char *server_portstr,
                              int server_portstr_size)
{
    int server_port;
    apr_status_t err = APR_SUCCESS;

    /*
     * Break up the URL to determine the host to connect to
     */

    /* we break the URL into host, port, uri */
    if (APR_SUCCESS != apr_uri_parse(p, *url, uri)) {
        return ap_proxyerror(r, HTTP_BAD_REQUEST,
                             apr_pstrcat(p,"URI cannot be parsed: ", *url,
                                         NULL));
    }
    if (!uri->port) {
        uri->port = apr_uri_port_of_scheme(uri->scheme);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: connecting %s to %s:%d", *url, uri->hostname,
                 uri->port);

    /*
     * allocate these out of the specified connection pool
     * The scheme handler decides if this is permanent or
     * short living pool.
     */
    /* are we connecting directly, or via a proxy? */
    if (!proxyname) {
        *url = apr_pstrcat(p, uri->path, uri->query ? "?" : "",
                           uri->query ? uri->query : "",
                           uri->fragment ? "#" : "",
                           uri->fragment ? uri->fragment : "", NULL);
    }
    if (!worker->is_address_reusable) {
        if (proxyname) {
            conn->hostname = proxyname;
            conn->port = proxyport;
        } else {
            conn->hostname = uri->hostname;
            conn->port = uri->port;
        }
    }
    else if (!conn->hostname) {
        if (proxyname) {
            conn->hostname = apr_pstrdup(conn->pool, proxyname);
            conn->port = proxyport;
        } else {
            conn->hostname = apr_pstrdup(conn->pool, uri->hostname);
            conn->port = uri->port;
        }
    }
    /*
     * TODO: add address cache for generic forward proxies.
     * At least level 0 -> compare with previous hostname:port
     */
    if (r->proxyreq == PROXYREQ_PROXY || r->proxyreq == PROXYREQ_REVERSE ||
        !worker->is_address_reusable) {
        /*
         * TODO: Check if the connection can be reused
         */
        if (conn->connection) {
            if (conn->sock) {
                apr_socket_close(conn->sock);
                conn->sock = NULL;
            }
            apr_pool_cleanup_kill(conn->connection->pool, conn, connection_cleanup);
            conn->connection = NULL;
        }
        err = apr_sockaddr_info_get(&(conn->addr),
                                    conn->hostname, APR_UNSPEC,
                                    conn->port, 0,
                                    conn->pool);
    }
    else if (!worker->cp->addr) {
        if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server,
                         "proxy: lock");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        /*
         * Worker can have the single constant backend adress.
         * The single DNS lookup is used once per worker.
         * If dynamic change is needed then set the addr to NULL
         * inside dynamic config to force the lookup.
         */
        err = apr_sockaddr_info_get(&(worker->cp->addr),
                                    conn->hostname, APR_UNSPEC,
                                    conn->port, 0,
                                    worker->cp->pool);
        conn->addr = worker->cp->addr;
        PROXY_THREAD_UNLOCK(worker);
    }
    else
        conn->addr = worker->cp->addr;

    if (err != APR_SUCCESS) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             apr_pstrcat(p, "DNS lookup failure for: ",
                                         conn->hostname, NULL));
    }

    /* Get the server port for the Via headers */
    {
        server_port = ap_get_server_port(r);
        if (ap_is_default_port(server_port, r)) {
            strcpy(server_portstr,"");
        } else {
            apr_snprintf(server_portstr, server_portstr_size, ":%d",
                         server_port);
        }
    }
    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, conn->addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: connected %s to %s:%d", *url, conn->hostname,
                 conn->port);
    return OK;
}

static int is_socket_connected(apr_socket_t *sock)

{
    apr_size_t buffer_len = 1;
    char test_buffer[1];
    apr_status_t socket_status;
    apr_interval_time_t current_timeout;

    /* save timeout */
    apr_socket_timeout_get(sock, &current_timeout);
    /* set no timeout */
    apr_socket_timeout_set(sock, 0);
    socket_status = apr_socket_recv(sock, test_buffer, &buffer_len);
    /* put back old timeout */
    apr_socket_timeout_set(sock, current_timeout);
    if (APR_STATUS_IS_EOF(socket_status))
        return 0;
    else
        return 1;
}

PROXY_DECLARE(int) ap_proxy_connect_backend(const char *proxy_function,
                                            proxy_conn_rec *conn,
                                            proxy_worker *worker,
                                            server_rec *s)
{
    apr_status_t rv;
    int connected = 0;
    int loglevel;
    apr_sockaddr_t *backend_addr = conn->addr;
    apr_socket_t *newsock;

    if (conn->sock) {
        /*
         * This increases the connection pool size
         * but the number of dropped connections is
         * relatively small compared to connection lifetime
         */
        if (!(connected = is_socket_connected(conn->sock))) {
            apr_socket_close(conn->sock);
            conn->sock = NULL;
        }
    }
    while (backend_addr && !connected) {
        if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                SOCK_STREAM, APR_PROTO_TCP,
                                conn->pool)) != APR_SUCCESS) {
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: error creating fam %d socket for target %s",
                         proxy_function,
                         backend_addr->family,
                         worker->hostname);
            /*
             * this could be an IPv6 address from the DNS but the
             * local machine won't give us an IPv6 socket; hopefully the
             * DNS returned an additional address to try
             */
            backend_addr = backend_addr->next;
            continue;
        }

#if !defined(TPF) && !defined(BEOS)
        if (worker->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(newsock, APR_SO_RCVBUF,
                                     worker->recv_buffer_size))) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                         "ProxyReceiveBufferSize, using default");
        }
#endif

        /* Set a timeout on the socket */
        if (worker->timeout_set == 1) {
            apr_socket_timeout_set(newsock, worker->timeout);
        }
        else {
             apr_socket_timeout_set(newsock, s->timeout);
        }
        /* Set a keepalive option */
        if (worker->keepalive) {
            if ((rv = apr_socket_opt_set(newsock,
                            APR_SO_KEEPALIVE, 1)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                             "apr_socket_opt_set(SO_KEEPALIVE): Failed to set"
                             " Keepalive");
            }
        }
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "proxy: %s: fam %d socket created to connect to %s",
                     proxy_function, backend_addr->family, worker->hostname);

        /* make the connection out of the socket */
        rv = apr_socket_connect(newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_error(APLOG_MARK, loglevel, rv, s,
                         "proxy: %s: attempt to connect to %pI (%s) failed",
                         proxy_function,
                         backend_addr,
                         worker->hostname);
            backend_addr = backend_addr->next;
            continue;
        }

        conn->sock   = newsock;
        connected    = 1;
    }
    /*
     * Put the entire worker to error state if
     * the PROXY_WORKER_IGNORE_ERRORS flag is not set.
     * Altrough some connections may be alive
     * no further connections to the worker could be made
     */
    if (!connected && PROXY_WORKER_IS_USABLE(worker) &&
        !(worker->s->status & PROXY_WORKER_IGNORE_ERRORS)) {
        worker->s->status |= PROXY_WORKER_IN_ERROR;
        worker->s->error_time = apr_time_now();
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
            "ap_proxy_connect_backend disabling worker for (%s)",
            worker->hostname);
    }
    else {
        worker->s->error_time = 0;
        worker->s->retries = 0;
    }
    return connected ? OK : DECLINED;
}

PROXY_DECLARE(int) ap_proxy_connection_create(const char *proxy_function,
                                              proxy_conn_rec *conn,
                                              conn_rec *c,
                                              server_rec *s)
{
    apr_sockaddr_t *backend_addr = conn->addr;
    int rc;

    /*
     * The socket is now open, create a new backend server connection
     */
    conn->connection = ap_run_create_connection(c->pool, s, conn->sock,
                                                c->id, c->sbh,
                                                c->bucket_alloc);

    if (!conn->connection) {
        /*
         * the peer reset the connection already; ap_run_create_connection()
         * closed the socket
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                     s, "proxy: %s: an error occurred creating a "
                     "new connection to %pI (%s)", proxy_function,
                     backend_addr, conn->hostname);
        /* XXX: Will be closed when proxy_conn is closed */
        apr_socket_close(conn->sock);
        conn->sock = NULL;
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    /*
     * register the connection cleanup to client connection
     * so that the connection can be closed or reused
     */
    apr_pool_cleanup_register(c->pool, (void *)conn,
                              connection_cleanup,
                              apr_pool_cleanup_null);

    /* For ssl connection to backend */
    if (conn->is_ssl) {
        if (!ap_proxy_ssl_enable(conn->connection)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         s, "proxy: %s: failed to enable ssl support "
                         "for %pI (%s)", proxy_function,
                         backend_addr, conn->hostname);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    else {
        /* TODO: See if this will break FTP */
        ap_proxy_ssl_disable(conn->connection);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: connection complete to %pI (%s)",
                 proxy_function, backend_addr, conn->hostname);

    /* set up the connection filters */
    rc = ap_run_pre_connection(conn->connection, conn->sock);
    if (rc != OK && rc != DONE) {
        conn->connection->aborted = 1;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "proxy: %s: pre_connection setup failed (%d)",
                     proxy_function, rc);
        return rc;
    }

    return OK;
}

int ap_proxy_lb_workers(void)
{
    /*
     * Since we can't resize the scoreboard when reconfiguring, we
     * have to impose a limit on the number of workers, we are
     * able to reconfigure to.
     */
    if (!lb_workers_limit)
    lb_workers_limit = proxy_lb_workers + PROXY_DYNAMIC_BALANCER_LIMIT;
    return lb_workers_limit;
}
