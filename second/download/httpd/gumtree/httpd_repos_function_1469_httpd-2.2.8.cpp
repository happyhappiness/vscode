static const char *
    set_proxy_req(cmd_parms *parms, void *dummy, int flag)
{
    proxy_server_conf *psf =
    ap_get_module_config(parms->server->module_config, &proxy_module);

    psf->req = flag;
    psf->req_set = 1;

    if (flag && !psf->forward) {
        psf->forward = ap_proxy_create_worker(parms->pool);
        psf->forward->name     = "proxy:forward";
        psf->forward->hostname = "*";
        psf->forward->scheme   = "*";
    }
    return NULL;
}