static const char 
*set_cache_removal_algorithm(cmd_parms *parms, void *name, const char *arg)
{
    if (strcasecmp("LRU", arg)) {
        sconf->cache_remove_algorithm = memcache_lru_algorithm;
    }
    else {
        if (strcasecmp("GDSF", arg)) {
            sconf->cache_remove_algorithm = memcache_gdsf_algorithm;
        }
        else {
            return "currently implemented algorithms are LRU and GDSF";
        }
    }
    return NULL;
}