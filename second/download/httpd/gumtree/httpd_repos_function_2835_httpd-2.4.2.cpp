static void rebuild_conf_hash(apr_pool_t *p, int add_prelinked)
{
    module **m;

    ap_config_hash = apr_hash_make(p);

    apr_pool_cleanup_register(p, &ap_config_hash, ap_pool_cleanup_set_null,
                              apr_pool_cleanup_null);
    if (add_prelinked) {
        for (m = ap_prelinked_modules; *m != NULL; m++) {
            ap_add_module_commands(*m, p);
        }
    }
}