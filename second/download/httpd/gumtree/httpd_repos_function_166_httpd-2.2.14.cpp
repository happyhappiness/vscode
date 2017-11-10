const char *dav_generic_get_lockdb_path(const request_rec *r)
{
    dav_lock_dir_conf *conf;

    conf = ap_get_module_config(r->per_dir_config, &dav_lock_module);
    return conf->lockdb_path;
}