static const char*
    set_bad_opt(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    if (strcasecmp(arg, "IsError") == 0)
        psf->badopt = bad_error;
    else if (strcasecmp(arg, "Ignore") == 0)
        psf->badopt = bad_ignore;
    else if (strcasecmp(arg, "StartBody") == 0)
        psf->badopt = bad_body;
    else {
        return "ProxyBadHeader must be one of: "
            "IsError | Ignore | StartBody";
    }

    psf->badopt_set = 1;
    return NULL;
}