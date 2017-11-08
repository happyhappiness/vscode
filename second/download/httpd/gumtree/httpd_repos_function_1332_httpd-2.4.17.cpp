static void *merge_dir_config(apr_pool_t *p, void *basev, void *addv)
{
    cache_socache_dir_conf
            *new =
                    (cache_socache_dir_conf *) apr_pcalloc(p, sizeof(cache_socache_dir_conf));
    cache_socache_dir_conf *add = (cache_socache_dir_conf *) addv;
    cache_socache_dir_conf *base = (cache_socache_dir_conf *) basev;

    new->max = (add->max_set == 0) ? base->max : add->max;
    new->max_set = add->max_set || base->max_set;
    new->maxtime = (add->maxtime_set == 0) ? base->maxtime : add->maxtime;
    new->maxtime_set = add->maxtime_set || base->maxtime_set;
    new->mintime = (add->mintime_set == 0) ? base->mintime : add->mintime;
    new->mintime_set = add->mintime_set || base->mintime_set;
    new->readsize = (add->readsize_set == 0) ? base->readsize : add->readsize;
    new->readsize_set = add->readsize_set || base->readsize_set;
    new->readtime = (add->readtime_set == 0) ? base->readtime : add->readtime;
    new->readtime_set = add->readtime_set || base->readtime_set;

    return new;
}