static const char *
    set_proxy_domain(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    if (arg[0] != '.')
        return "ProxyDomain: domain name must start with a dot.";

    psf->domain = arg;
    return NULL;
}