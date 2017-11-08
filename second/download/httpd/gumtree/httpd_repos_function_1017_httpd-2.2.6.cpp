static void *so_sconf_create(apr_pool_t *p, server_rec *s)
{
    so_server_conf *soc;

    soc = (so_server_conf *)apr_pcalloc(p, sizeof(so_server_conf));
    soc->loaded_modules = apr_array_make(p, DYNAMIC_MODULE_LIMIT,
                                     sizeof(ap_module_symbol_t));

    return (void *)soc;
}