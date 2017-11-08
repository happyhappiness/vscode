apr_status_t ap_open_htaccess(request_rec *r, const char *dir_name,
                              const char *access_name,
                              ap_configfile_t **conffile,
                              const char **full_name)
{
    *full_name = ap_make_full_path(r->pool, dir_name, access_name);
    return ap_pcfg_openfile(conffile, r->pool, *full_name);
}