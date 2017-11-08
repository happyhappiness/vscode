static const char *
    set_proxy_error_override(cmd_parms *parms, void *dconf, int flag)
{
    proxy_dir_conf *conf = dconf;

    conf->error_override = flag;
    conf->error_override_set = 1;
    return NULL;
}