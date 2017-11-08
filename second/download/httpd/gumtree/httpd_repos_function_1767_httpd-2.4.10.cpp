static void set_fn_info(request_rec *r, const char *name)
{
    if (r)
        ap_set_module_config(r->request_config, &info_module, (void *)name);
    else
        dump_config_fn_info = name;
}