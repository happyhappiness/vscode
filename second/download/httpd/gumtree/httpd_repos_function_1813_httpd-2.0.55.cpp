static ap_conf_vector_t *create_default_per_dir_config(apr_pool_t *p)
{
    void **conf_vector = apr_pcalloc(p, sizeof(void *) *
                                     (total_modules + DYNAMIC_MODULE_LIMIT));
    module *modp;

    for (modp = ap_top_module; modp; modp = modp->next) {
        dir_maker_func df = modp->create_dir_config;

        if (df)
            conf_vector[modp->module_index] = (*df)(p, NULL);
    }

    return (ap_conf_vector_t *)conf_vector;
}