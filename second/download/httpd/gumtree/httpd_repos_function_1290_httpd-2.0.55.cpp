static const char *
    set_preserve_host(cmd_parms *parms, void *dummy, int flag)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    psf->preserve_host = flag;
    psf->preserve_host_set = 1;
    return NULL;
}