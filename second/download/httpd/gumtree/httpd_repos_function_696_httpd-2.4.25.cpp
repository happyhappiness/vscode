apr_status_t ssl_init_ModuleKill(void *data)
{
    SSLSrvConfigRec *sc;
    server_rec *base_server = (server_rec *)data;
    server_rec *s;

    /*
     * Drop the session cache and mutex
     */
    ssl_scache_kill(base_server);

    /*
     * Free the non-pool allocated structures
     * in the per-server configurations
     */
    for (s = base_server; s; s = s->next) {
        sc = mySrvConfig(s);

        ssl_init_ctx_cleanup_proxy(sc->proxy);

        ssl_init_ctx_cleanup(sc->server);
    }

    free_dh_params();

    return APR_SUCCESS;
}