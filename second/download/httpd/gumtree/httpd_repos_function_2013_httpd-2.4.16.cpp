static const char *
    set_io_buffer_size(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);
    long s = atol(arg);
    if (s < 512 && s) {
        return "ProxyIOBufferSize must be >= 512 bytes, or 0 for system default.";
    }
    psf->io_buffer_size = (s ? s : AP_IOBUFSIZE);
    psf->io_buffer_size_set = 1;
    return NULL;
}