     */
    cp = (proxy_conn_pool *)apr_pcalloc(p, sizeof(proxy_conn_pool));
    cp->pool = pool;
    worker->cp = cp;
}

PROXY_DECLARE(const char *) ap_proxy_add_worker_wid(proxy_worker **worker,
                                                apr_pool_t *p,
                                                proxy_server_conf *conf,
                                                const char *url,
                                                int id)
{
    int rv;
    apr_uri_t uri;

    rv = apr_uri_parse(p, url, &uri);

    if (rv != APR_SUCCESS) {
        return "Unable to parse URL";
    }
    if (!uri.hostname || !uri.scheme) {
        return "URL must be absolute!";
    }

    ap_str_tolower(uri.hostname);
    ap_str_tolower(uri.scheme);
    *worker = apr_array_push(conf->workers);
    memset(*worker, 0, sizeof(proxy_worker));
    (*worker)->name = apr_uri_unparse(p, &uri, APR_URI_UNP_REVEALPASSWORD);
    (*worker)->scheme = uri.scheme;
    (*worker)->hostname = uri.hostname;
    (*worker)->port = uri.port;
    if (id < 0) {
        (*worker)->id   = proxy_lb_workers;
        /* Increase the total worker count */
        proxy_lb_workers++;
    } else {
        (*worker)->id   = id;
    }
    (*worker)->flush_packets = flush_off;
    (*worker)->flush_wait = PROXY_FLUSH_WAIT;
    (*worker)->smax = -1;
    (*worker)->our_hash = ap_proxy_hashfunc((*worker)->name, PROXY_HASHFUNC_PROXY);
    (*worker)->apr_hash = ap_proxy_hashfunc((*worker)->name, PROXY_HASHFUNC_APR);
    (*worker)->cp = NULL;
    (*worker)->mutex = NULL;

    return NULL;
}

PROXY_DECLARE(const char *) ap_proxy_add_worker(proxy_worker **worker,
                                                apr_pool_t *p,
                                                proxy_server_conf *conf,
                                                const char *url)
{
    return ap_proxy_add_worker_wid(worker, p, conf, url, -1);
}

PROXY_DECLARE(proxy_worker *) ap_proxy_create_worker_wid(apr_pool_t *p, int id)
{

    proxy_worker *worker;
    worker = (proxy_worker *)apr_pcalloc(p, sizeof(proxy_worker));
    if (id < 0) {
        worker->id = proxy_lb_workers;
        /* Increase the total worker count */
        proxy_lb_workers++;
    } else {
        worker->id = id;
    }
    worker->smax = -1;
    worker->cp = NULL;
    worker->mutex = NULL;

    return worker;
}

PROXY_DECLARE(proxy_worker *) ap_proxy_create_worker(apr_pool_t *p)
{
    return ap_proxy_create_worker_wid(p, -1);
}

PROXY_DECLARE(void)
ap_proxy_add_worker_to_balancer_wid(apr_pool_t *pool, proxy_balancer *balancer,
                                proxy_worker *worker, int id)
{
    proxy_worker **runtime;

    runtime = apr_array_push(balancer->workers);
    *runtime = worker;
    if (id < 0) {
        (*runtime)->id = proxy_lb_workers;
        /* Increase the total runtime count */
        proxy_lb_workers++;
    } else {
        (*runtime)->id = id;
    }
    balancer->updated = apr_time_now();

}

PROXY_DECLARE(void)
ap_proxy_add_worker_to_balancer(apr_pool_t *pool, proxy_balancer *balancer,
                                proxy_worker *worker)
{
    ap_proxy_add_worker_to_balancer_wid(pool, balancer, worker, -1);
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
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "proxy: %s: found worker %s for %s",
                          (*worker)->scheme, (*worker)->name, *url);

            *balancer = NULL;
            access_status = OK;
        }
        else if (r->proxyreq == PROXYREQ_PROXY) {
            if (conf->forward) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "proxy: *: found forward proxy worker for %s",
                              *url);
                *balancer = NULL;
                *worker = conf->forward;
                access_status = OK;
                /*
                 * The forward worker does not keep connections alive, so
                 * ensure that mod_proxy_http does the correct thing
                 * regarding the Connection header in the request.
                 */
                apr_table_set(r->subprocess_env, "proxy-nokeepalive", "1");
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "proxy: *: found reverse proxy worker for %s",
                               *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;
                /*
                 * The reverse worker does not keep connections alive, so
                 * ensure that mod_proxy_http does the correct thing
                 * regarding the Connection header in the request.
                 */
                apr_table_set(r->subprocess_env, "proxy-nokeepalive", "1");
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
            ap_log_rerror(APLOG_MARK, loglevel, rv, r,
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

        if (conf->recv_buffer_size > 0 &&
            (rv = apr_socket_opt_set(*newsock, APR_SO_RCVBUF,
                                     conf->recv_buffer_size))) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "apr_socket_opt_set(SO_RCVBUF): Failed to set "
                          "ProxyReceiveBufferSize, using default");
        }

        rv = apr_socket_opt_set(*newsock, APR_TCP_NODELAY, 1);
        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                           "apr_socket_opt_set(APR_TCP_NODELAY): "
                           "Failed to set");
        }

        /* Set a timeout on the socket */
        if (conf->timeout_set == 1) {
            apr_socket_timeout_set(*newsock, conf->timeout);
        }
        else {
             apr_socket_timeout_set(*newsock, r->server->timeout);
        }

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                      "proxy: %s: fam %d socket created to connect to %s",
                      proxy_function, backend_addr->family, backend_name);

        /* make the connection out of the socket */
        rv = apr_socket_connect(*newsock, backend_addr);

        /* if an error occurred, loop round and try again */
        if (rv != APR_SUCCESS) {
            apr_socket_close(*newsock);
            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
            ap_log_rerror(APLOG_MARK, loglevel, rv, r,
                          "proxy: %s: attempt to connect to %pI (%s) failed",
                          proxy_function,
                          backend_addr,
                          backend_name);
            backend_addr = backend_addr->next;
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
    if (!worker->cp) {
        return APR_SUCCESS;
    }

#if APR_HAS_THREADS
    /* Sanity check: Did we already return the pooled connection? */
    if (conn->inreslist) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, conn->pool,
                      "proxy: Pooled connection 0x%pp for worker %s has been"
                      " already returned to the connection pool.", conn,
                      worker->name);
        return APR_SUCCESS;
    }
#endif

    /* determine if the connection need to be closed */
    if (conn->close || !worker->is_address_reusable || worker->disablereuse) {
        apr_pool_t *p = conn->pool;
        apr_pool_clear(p);
        conn = apr_pcalloc(p, sizeof(proxy_conn_rec));
        conn->pool = p;
        conn->worker = worker;
        apr_pool_create(&(conn->scpool), p);
        apr_pool_tag(conn->scpool, "proxy_conn_scpool");
    }
#if APR_HAS_THREADS
    if (worker->hmax && worker->cp->res) {
        conn->inreslist = 1;
        apr_reslist_release(worker->cp->res, (void *)conn);
    }
    else
#endif
    {
        worker->cp->conn = conn;
    }

    /* Always return the SUCCESS */
    return APR_SUCCESS;
