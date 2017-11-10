static ef_filter_t *find_filter_def(const server_rec *s, const char *fname)
{
    ef_server_t *sc;
    ef_filter_t *f;

    sc = ap_get_module_config(s->module_config, &ext_filter_module);
    f = apr_hash_get(sc->h, fname, APR_HASH_KEY_STRING);
    if (!f && s != main_server) {
        s = main_server;
        sc = ap_get_module_config(s->module_config, &ext_filter_module);
        f = apr_hash_get(sc->h, fname, APR_HASH_KEY_STRING);
    }
    return f;
}