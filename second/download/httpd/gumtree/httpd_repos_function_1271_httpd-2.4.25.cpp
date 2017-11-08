static const char *set_cache_maxex(cmd_parms *parms, void *dummy,
                                   const char *arg)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->maxex = (apr_time_t) (atol(arg) * MSEC_ONE_SEC);
    dconf->maxex_set = 1;
    return NULL;
}