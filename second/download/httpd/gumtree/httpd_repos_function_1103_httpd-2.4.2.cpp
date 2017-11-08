static const char *set_cache_ignore_no_last_mod(cmd_parms *parms, void *dummy,
                                                int flag)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;

    dconf->no_last_mod_ignore = flag;
    dconf->no_last_mod_ignore_set = 1;
    return NULL;

}