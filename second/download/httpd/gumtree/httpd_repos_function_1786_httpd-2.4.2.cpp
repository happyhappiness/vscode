static const char *
    set_preserve_host(cmd_parms *parms, void *dconf, int flag)
{
    proxy_dir_conf *conf = dconf;

    conf->preserve_host = flag;
    conf->preserve_host_set = 1;
    return NULL;
}