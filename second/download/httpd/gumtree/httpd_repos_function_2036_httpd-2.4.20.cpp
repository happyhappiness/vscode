static const char *set_persist(cmd_parms *parms, void *dummy, int flag)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    psf->bal_persist = flag;
    return NULL;
}