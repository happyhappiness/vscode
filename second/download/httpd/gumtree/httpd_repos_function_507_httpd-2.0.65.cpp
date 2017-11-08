static void *create_headers_config(apr_pool_t *p, char *dummy)
{
    headers_conf *conf = apr_palloc(p, sizeof(*conf));

    conf->fixup_in = apr_array_make(p, 2, sizeof(header_entry));
    conf->fixup_out = apr_array_make(p, 2, sizeof(header_entry));
    conf->fixup_err = apr_array_make(p, 2, sizeof(header_entry));

    return conf;
}