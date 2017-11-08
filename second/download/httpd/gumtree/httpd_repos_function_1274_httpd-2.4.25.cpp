static const char *set_cache_factor(cmd_parms *parms, void *dummy,
                                    const char *arg)
{
    cache_dir_conf *dconf = (cache_dir_conf *)dummy;
    double val;

    if (sscanf(arg, "%lg", &val) != 1) {
        return "CacheLastModifiedFactor value must be a float";
    }
    dconf->factor = val;
    dconf->factor_set = 1;
    return NULL;
}