h2_config *h2_config_rget(request_rec *r)
{
    h2_config *cfg = (h2_config *)ap_get_module_config(r->per_dir_config, 
                                                       &http2_module);
    return cfg? cfg : h2_config_sget(r->server); 
}