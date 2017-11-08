static const char*
    set_status_opt(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    if (strcasecmp(arg, "Off") == 0)
        psf->proxy_status = status_off;
    else if (strcasecmp(arg, "On") == 0)
        psf->proxy_status = status_on;
    else if (strcasecmp(arg, "Full") == 0)
        psf->proxy_status = status_full;
    else {
        return "ProxyStatus must be one of: "
            "off | on | block";
    }

    psf->proxy_status_set = 1;
    return NULL;
}