static const char
*set_cache_exchk(cmd_parms *parms, void *in_struct_ptr, int flag)
{
    disk_cache_conf *conf = ap_get_module_config(parms->server->module_config,
                                                 &disk_cache_module);
    conf->expirychk = flag;

    return NULL;
}