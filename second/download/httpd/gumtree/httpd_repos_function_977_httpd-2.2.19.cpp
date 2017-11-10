static char *data_file(apr_pool_t *p, disk_cache_conf *conf,
                       disk_cache_object_t *dobj, const char *name)
{
    if (!dobj->hashfile) {
        dobj->hashfile = ap_cache_generate_name(p, conf->dirlevels,
                                                conf->dirlength, name);
    }

    if (dobj->prefix) {
        return apr_pstrcat(p, dobj->prefix, CACHE_VDIR_SUFFIX, "/",
                           dobj->hashfile, CACHE_DATA_SUFFIX, NULL);
     }
     else {
        return apr_pstrcat(p, conf->cache_root, "/", dobj->hashfile,
                           CACHE_DATA_SUFFIX, NULL);
     }
}