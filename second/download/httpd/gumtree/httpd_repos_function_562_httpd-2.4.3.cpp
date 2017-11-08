static void *create_ident_dir_config(apr_pool_t *p, char *d)
{
    ident_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->do_rfc1413 = DEFAULT_RFC1413 | RFC1413_UNSET;
    conf->timeout = apr_time_from_sec(RFC1413_TIMEOUT);
    conf->timeout_unset = 1;

    return (void *)conf;
}