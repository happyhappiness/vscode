static void *create_info_config(apr_pool_t * p, server_rec * s)
{
    info_svr_conf *conf =
        (info_svr_conf *) apr_pcalloc(p, sizeof(info_svr_conf));

    conf->more_info = apr_array_make(p, 20, sizeof(info_entry));
    return conf;
}