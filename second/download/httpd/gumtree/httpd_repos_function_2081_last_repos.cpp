static const char *set_bgrowth(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    int growth = atoi(arg);
    if (growth < 0 || growth > 1000) {
        return "BalancerGrowth must be between 0 and 1000";
    }
    psf->bgrowth = growth;
    psf->bgrowth_set = 1;

    return NULL;
}