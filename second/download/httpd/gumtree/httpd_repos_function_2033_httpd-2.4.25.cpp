static const char *set_source_address(cmd_parms *parms, void *dummy,
                                      const char *arg)
{
    proxy_server_conf *psf =
        ap_get_module_config(parms->server->module_config, &proxy_module);
    struct apr_sockaddr_t *addr;

    if (APR_SUCCESS == apr_sockaddr_info_get(&addr, arg, APR_UNSPEC, 0, 0,
                                             psf->pool)) {
        psf->source_address = addr;
        psf->source_address_set = 1;
    }
    else {
        return "ProxySourceAddress invalid value";
    }

    return NULL;
}