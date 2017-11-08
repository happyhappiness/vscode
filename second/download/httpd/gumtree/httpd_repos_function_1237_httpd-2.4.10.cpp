static const char *set_cache_store_private(cmd_parms *parms, void *dummy,
                                           int flag)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->store_private = flag;
    dconf->store_private_set = 1;
    return NULL;
}