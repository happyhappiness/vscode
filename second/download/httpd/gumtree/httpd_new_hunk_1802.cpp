
    printf("Compiled in modules:\n");
    for (n = 0; ap_loaded_modules[n]; ++n)
        printf("  %s\n", ap_loaded_modules[n]->name);
}

AP_DECLARE(void *) ap_retained_data_get(const char *key)
{
    void *retained;

    apr_pool_userdata_get((void *)&retained, key, ap_pglobal);
    return retained;
}

AP_DECLARE(void *) ap_retained_data_create(const char *key, apr_size_t size)
{
    void *retained;

    retained = apr_pcalloc(ap_pglobal, size);
    apr_pool_userdata_set((const void *)retained, key, apr_pool_cleanup_null, ap_pglobal);
    return retained;
}
