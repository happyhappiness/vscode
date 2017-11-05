static const char *
    set_proxy_error_override(cmd_parms *parms, void *dummy, int flag)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    psf->error_override = flag;
    psf->error_override_set = 1;
    return NULL;
}