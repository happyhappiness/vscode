static const char *set_ppinherit(cmd_parms *parms, void *dummy, int flag)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    psf->ppinherit = flag;
    psf->ppinherit_set = 1;
    return NULL;
}