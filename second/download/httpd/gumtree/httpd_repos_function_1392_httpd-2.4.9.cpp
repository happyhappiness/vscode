static void *merge_dir_config(apr_pool_t *p, void *basev, void *addv) {
    disk_cache_dir_conf *new = (disk_cache_dir_conf *) apr_pcalloc(p, sizeof(disk_cache_dir_conf));
    disk_cache_dir_conf *add = (disk_cache_dir_conf *) addv;
    disk_cache_dir_conf *base = (disk_cache_dir_conf *) basev;

    new->maxfs = (add->maxfs_set == 0) ? base->maxfs : add->maxfs;
    new->maxfs_set = add->maxfs_set || base->maxfs_set;
    new->minfs = (add->minfs_set == 0) ? base->minfs : add->minfs;
    new->minfs_set = add->minfs_set || base->minfs_set;
    new->readsize = (add->readsize_set == 0) ? base->readsize : add->readsize;
    new->readsize_set = add->readsize_set || base->readsize_set;
    new->readtime = (add->readtime_set == 0) ? base->readtime : add->readtime;
    new->readtime_set = add->readtime_set || base->readtime_set;

    return new;
}