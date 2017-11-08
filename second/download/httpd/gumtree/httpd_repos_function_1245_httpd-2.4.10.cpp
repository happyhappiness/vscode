static const char *set_cache_defex(cmd_parms *parms, void *dummy,
                                   const char *arg)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->defex = (apr_time_t) (atol(arg) * MSEC_ONE_SEC);
    dconf->defex_set = 1;
    return NULL;
}