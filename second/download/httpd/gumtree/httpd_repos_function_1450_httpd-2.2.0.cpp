static const char *
    set_io_buffer_size(cmd_parms *parms, void *dummy, const char *arg)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);
    long s = atol(arg);

    psf->io_buffer_size = ((s > AP_IOBUFSIZE) ? s : AP_IOBUFSIZE);
    psf->io_buffer_size_set = 1;
    return NULL;
}