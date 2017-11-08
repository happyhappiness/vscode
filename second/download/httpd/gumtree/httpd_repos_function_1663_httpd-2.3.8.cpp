static int drive_serf(request_rec *r, serf_config_t *conf)
{
    apr_status_t rv = 0;
    apr_pool_t *pool;
    apr_sockaddr_t *address;
    s_baton_t *baton = apr_palloc(r->pool, sizeof(s_baton_t));
    /* XXXXX: make persistent/per-process or something.*/
    serf_context_t *serfme;
    serf_connection_t *conn;
    serf_request_t *srequest;
    serf_server_config_t *ctx = 
        (serf_server_config_t *)ap_get_module_config(r->server->module_config,
                                                     &serf_module);

    /* Allocate everything out of a subpool, with a shorter lifetime than
     * the main request, so that we can cleanup safely and remove our events
     * from the main serf context in the async mpm mode.
     */
    apr_pool_create(&pool, r->pool);
    if (strcmp(conf->url.scheme, "cluster") == 0) {
        int rc;
        ap_serf_cluster_provider_t *cp;
        serf_cluster_t *cluster;
        apr_array_header_t *servers = NULL;
        apr_uint32_t pick = 0;
        ap_serf_server_t *choice;

        /* TODO: could this be optimized in post-config to pre-setup the 
         * pointers to the right cluster inside the conf structure?
         */
        cluster = apr_hash_get(ctx->clusters,
                               conf->url.hostname,
                               APR_HASH_KEY_STRING);
        if (!cluster) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "SerfCluster: unable to find cluster %s", conf->url.hostname);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        cp = ap_lookup_provider(AP_SERF_CLUSTER_PROVIDER, cluster->provider, "0");
        
        if (cp == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "SerfCluster: unable to find provider %s", cluster->provider);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        if (cp->list_servers == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "SerfCluster: %s is missing list servers provider.", cluster->provider);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        
        rc = cp->list_servers(cp->baton,
                              r,
                              cluster->params,
                              &servers);

        if (rc != OK) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "SerfCluster: %s list servers returned failure", cluster->provider);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        if (servers == NULL || apr_is_empty_array(servers)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "SerfCluster: %s failed to provide a list of servers", cluster->provider);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        /* TOOD: restructure try all servers in the array !! */
        if (random_pick(&pick, 0, servers->nelts-1) != APR_SUCCESS)
            pick = 0;
        choice = APR_ARRAY_IDX(servers, pick, ap_serf_server_t *);

        rv = apr_sockaddr_info_get(&address, choice->ip,
                                   APR_UNSPEC, choice->port, 0,
                                   pool);
    }
    else {
        /* XXXXX: cache dns? */
        rv = apr_sockaddr_info_get(&address, conf->url.hostname,
                                   APR_UNSPEC, conf->url.port, 0,
                                   pool);
    }

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "Unable to resolve: %s", conf->url.hostname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (mpm_supprts_serf) {
        serfme = ap_lookup_provider("mpm_serf", "instance", "0");
        if (!serfme) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "mpm lied to us about supporting serf.");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    else {
        serfme = serf_context_create(pool);
    }

    baton->r = r;
    baton->conf = conf;
    baton->serf_pool = pool;
    baton->bkt_alloc = serf_bucket_allocator_create(pool, NULL, NULL);
    baton->body_bkt = NULL;
    baton->ssl_ctx = NULL;
    baton->rstatus = OK;

    baton->tmpbb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    baton->done_headers = 0;
    baton->keep_reading = 1;

    if (strcasecmp(conf->url.scheme, "https") == 0) {
        baton->want_ssl = 1;
    }
    else {
        baton->want_ssl = 0;
    }

    rv = ap_setup_client_block(baton->r, REQUEST_CHUNKED_DECHUNK);
    if (rv) {
        return rv;
    }

    /* TODO: create custom serf bucket, which does async request body reads */
    if (ap_should_client_block(r)) {
        apr_size_t len;
        apr_off_t flen = 0;
        char buf[AP_IOBUFSIZE];
        apr_file_t *fp;

        rv = apr_file_mktemp(&fp, "mod_serf_buffer.XXXXXX", 0, pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "mod_serf: Unable to create temp request body buffer file.");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        do {
            len = sizeof(buf);
            rv = ap_get_client_block(baton->r, buf, len);
            if (rv > 0) {
                rv = apr_file_write_full(fp, buf, rv, NULL);
                if (rv) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "mod_serf: failed to read request body");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
            }
        } while(rv > 0);

        if (rv < 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "mod_serf: failed to read request body");
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        apr_file_seek(fp, APR_SET, &flen);
        baton->body_bkt = serf_bucket_file_create(fp, baton->bkt_alloc);
    }
    
    conn = serf_connection_create(serfme, address,
                                  conn_setup, baton,
                                  closed_connection, baton,
                                  pool);

    srequest = serf_connection_request_create(conn, setup_request,
                                              baton);

    if (mpm_supprts_serf) {
        return SUSPENDED;
    }
    else {
        do {
            rv = serf_context_run(serfme, SERF_DURATION_FOREVER, pool);
            
            /* XXXX: Handle timeouts */
            if (APR_STATUS_IS_TIMEUP(rv)) {
                continue;
            }
            
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "serf_context_run() for %pI", address);
                return HTTP_INTERNAL_SERVER_ERROR;       
            }
            
            serf_debug__closed_conn(baton->bkt_alloc);
        } while (baton->keep_reading);
        
        return baton->rstatus;
    }
}