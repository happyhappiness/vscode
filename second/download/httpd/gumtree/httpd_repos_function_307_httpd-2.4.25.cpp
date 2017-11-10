const char *dav_get_lockdb_path(const request_rec *r)
{
    dav_fs_server_conf *conf;

    conf = ap_get_module_config(r->server->module_config, &dav_fs_module);
    return conf->lockdb_path;
}