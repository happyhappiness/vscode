static const char *get_fn_info(request_rec *r)
{
    if (r)
        return ap_get_module_config(r->request_config, &info_module);
    else
        return dump_config_fn_info;
}