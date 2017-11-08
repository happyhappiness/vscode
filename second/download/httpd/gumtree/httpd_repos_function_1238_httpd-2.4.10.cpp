static const char *set_cache_store_nostore(cmd_parms *parms, void *dummy,
                                           int flag)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->store_nostore = flag;
    dconf->store_nostore_set = 1;
    return NULL;
}