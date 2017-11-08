static char *ssl_add_version_component(apr_pool_t *p,
                                       server_rec *s,
                                       char *name)
{
    char *val = ssl_var_lookup(p, s, NULL, NULL, name);

    if (val && *val) {
        ap_add_version_component(p, val);
    }

    return val;
}