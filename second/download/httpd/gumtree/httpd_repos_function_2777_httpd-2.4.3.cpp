static int access_compat_ap_satisfies(request_rec *r)
{
    access_compat_dir_conf *conf = (access_compat_dir_conf *)
        ap_get_module_config(r->per_dir_config, &access_compat_module);

    return conf->satisfy[r->method_number];
}