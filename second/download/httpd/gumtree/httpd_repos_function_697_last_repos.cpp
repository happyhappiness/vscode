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

	/* Not Sure but possibly clear X509 trusted cert file */
	#ifndef OPENSSL_NO_OCSP
		sk_X509_pop_free(sc->server->ocsp_certs, X509_free);
	#endif

    }

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
    free_bio_methods();
#endif
    free_dh_params();

    return APR_SUCCESS;
}