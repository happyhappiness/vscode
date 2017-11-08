static int create_request_config(request_rec *r)
{
    ap_lua_request_cfg *cfg = apr_palloc(r->pool, sizeof(ap_lua_request_cfg));
    cfg->mapped_request_details = NULL;
    cfg->request_scoped_vms = apr_hash_make(r->pool);
    ap_set_module_config(r->request_config, &lua_module, cfg);
    return OK;
}