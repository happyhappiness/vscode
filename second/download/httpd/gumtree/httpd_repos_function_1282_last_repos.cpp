static const char *set_cache_store_expired(cmd_parms *parms, void *dummy,
                                           int flag)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->store_expired = flag;
    dconf->store_expired_set = 1;
    return NULL;
}