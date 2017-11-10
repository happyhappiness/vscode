static const char *set_cache_stale_on_error(cmd_parms *parms, void *dummy,
        int flag)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->stale_on_error = flag;
    dconf->stale_on_error_set = 1;
    return NULL;
}