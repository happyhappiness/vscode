static void *fcgi_create_dconf(apr_pool_t *p, char *path)
{
    fcgi_dirconf_t *a;

    a = (fcgi_dirconf_t *)apr_pcalloc(p, sizeof(fcgi_dirconf_t));
    a->backend_type = BACKEND_DEFAULT_UNKNOWN;
    a->env_fixups = apr_array_make(p, 20, sizeof(sei_entry));

    return a;
}