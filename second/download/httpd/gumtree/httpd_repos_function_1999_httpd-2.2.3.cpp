static ap_conf_vector_t *create_empty_config(apr_pool_t *p)
{
    void *conf_vector = apr_pcalloc(p, sizeof(void *) *
                                    (total_modules + DYNAMIC_MODULE_LIMIT));
    return conf_vector;
}