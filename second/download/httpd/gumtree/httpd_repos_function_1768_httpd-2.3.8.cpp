static const char*
    set_proxy_timeout(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);
    int timeout;

    timeout = atoi(arg);
    if (timeout<1) {
        return "Proxy Timeout must be at least 1 second.";
    }
    psf->timeout_set = 1;
    psf->timeout = apr_time_from_sec(timeout);

    return NULL;
}