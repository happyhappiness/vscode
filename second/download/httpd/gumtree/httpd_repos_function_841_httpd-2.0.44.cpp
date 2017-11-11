static int ssl_hook_pre_config(apr_pool_t *pconf,
                               apr_pool_t *plog,
                               apr_pool_t *ptemp)
{
    /* Preregister the malloc callbacks so cmds can make library calls */
    CRYPTO_malloc_init();

    /* Register us to handle mod_log_config %c/%x variables */
    ssl_var_log_config_register(pconf);
#if 0 /* XXX */
    /* XXX: Register us to handle mod_status extensions that don't exist yet */
    ssl_scache_status_register(pconf);
#endif /* -0- */

    return OK;
}