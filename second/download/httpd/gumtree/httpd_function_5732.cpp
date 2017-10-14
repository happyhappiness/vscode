apr_status_t ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
                             apr_pool_t *ptemp,
                             server_rec *base_server)
{
    SSLModConfigRec *mc = myModConfig(base_server);
    SSLSrvConfigRec *sc;
    server_rec *s;
    apr_status_t rv;
    apr_array_header_t *pphrases;

    if (SSLeay() < SSL_LIBRARY_VERSION) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01882)
                     "Init: this version of mod_ssl was compiled against "
                     "a newer library (%s, version currently loaded is %s)"
                     " - may result in undefined or erroneous behavior",
                     SSL_LIBRARY_TEXT, SSLeay_version(SSLEAY_VERSION));
    }

    /* We initialize mc->pid per-process in the child init,
     * but it should be initialized for startup before we
     * call ssl_rand_seed() below.
     */
    mc->pid = getpid();

    /*
     * Let us cleanup on restarts and exits
     */
    apr_pool_cleanup_register(p, base_server,
                              ssl_init_ModuleKill,
                              apr_pool_cleanup_null);

    /*
     * Any init round fixes the global config
     */
    ssl_config_global_create(base_server); /* just to avoid problems */
    ssl_config_global_fix(mc);

    /*
     *  try to fix the configuration and open the dedicated SSL
     *  logfile as early as possible
     */
    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);

        if (sc->server) {
            sc->server->sc = sc;
        }

        if (sc->proxy) {
            sc->proxy->sc = sc;
        }

        /*
         * Create the server host:port string because we need it a lot
         */
        sc->vhost_id = ssl_util_vhostid(p, s);
        sc->vhost_id_len = strlen(sc->vhost_id);

        /* Default to enabled if SSLEngine is not set explicitly, and
         * the protocol is https. */
        if (ap_get_server_protocol(s) 
            && strcmp("https", ap_get_server_protocol(s)) == 0
            && sc->enabled == SSL_ENABLED_UNSET) {
            sc->enabled = SSL_ENABLED_TRUE;
        }

        /* Fix up stuff that may not have been set.  If sc->enabled is
         * UNSET, then SSL is disabled on this vhost.  */
        if (sc->enabled == SSL_ENABLED_UNSET) {
            sc->enabled = SSL_ENABLED_FALSE;
        }
        if (sc->proxy_enabled == UNSET) {
            sc->proxy_enabled = FALSE;
        }

        if (sc->session_cache_timeout == UNSET) {
            sc->session_cache_timeout = SSL_SESSION_CACHE_TIMEOUT;
        }

        if (sc->server && sc->server->pphrase_dialog_type == SSL_PPTYPE_UNSET) {
            sc->server->pphrase_dialog_type = SSL_PPTYPE_BUILTIN;
        }

#ifdef HAVE_FIPS
        if (sc->fips == UNSET) {
            sc->fips = FALSE;
        }
#endif
    }

#if APR_HAS_THREADS
    ssl_util_thread_setup(p);
#endif

    /*
     * SSL external crypto device ("engine") support
     */
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(HAVE_ENGINE_INIT)
    if ((rv = ssl_init_Engine(base_server, p)) != APR_SUCCESS) {
        return rv;
    }
#endif

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01883)
                 "Init: Initialized %s library", SSL_LIBRARY_NAME);

    /*
     * Seed the Pseudo Random Number Generator (PRNG)
     * only need ptemp here; nothing inside allocated from the pool
     * needs to live once we return from ssl_rand_seed().
     */
    ssl_rand_seed(base_server, ptemp, SSL_RSCTX_STARTUP, "Init: ");

#ifdef HAVE_FIPS
    if(sc->fips) {
        if (!FIPS_mode()) {
            if (FIPS_mode_set(1)) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01884)
                             "Operating in SSL FIPS mode");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01885) "FIPS mode failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                return ssl_die(s);
            }
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01886)
                     "SSL FIPS mode disabled");
    }
#endif

    /*
     * initialize the mutex handling
     */
    if (!ssl_mutex_init(base_server, p)) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }
#ifdef HAVE_OCSP_STAPLING
    ssl_stapling_certinfo_hash_init(p);
#endif

    /*
     * initialize session caching
     */
    if ((rv = ssl_scache_init(base_server, p)) != APR_SUCCESS) {
        return rv;
    }

    pphrases = apr_array_make(ptemp, 2, sizeof(char *));

    /*
     *  initialize servers
     */
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, base_server, APLOGNO(01887)
                 "Init: Initializing (virtual) servers for SSL");

    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);
        /*
         * Either now skip this server when SSL is disabled for
         * it or give out some information about what we're
         * configuring.
         */

        /*
         * Read the server certificate and key
         */
        if ((rv = ssl_init_ConfigureServer(s, p, ptemp, sc, pphrases))
            != APR_SUCCESS) {
            return rv;
        }
    }

    if (pphrases->nelts > 0) {
        memset(pphrases->elts, 0, pphrases->elt_size * pphrases->nelts);
        pphrases->nelts = 0;
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02560)
                     "Init: Wiped out the queried pass phrases from memory");
    }

    /*
     * Configuration consistency checks
     */
    if ((rv = ssl_init_CheckServers(base_server, ptemp)) != APR_SUCCESS) {
        return rv;
    }

    /*
     *  Announce mod_ssl and SSL library in HTTP Server field
     *  as ``mod_ssl/X.X.X OpenSSL/X.X.X''
     */
    ssl_add_version_components(p, base_server);

    SSL_init_app_data2_idx(); /* for SSL_get_app_data2() at request time */

    init_dh_params();

    return OK;
}