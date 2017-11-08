const h2_config *h2_config_sget(server_rec *s)
{
    h2_config *cfg = (h2_config *)ap_get_module_config(s->module_config, 
                                                       &http2_module);
    AP_DEBUG_ASSERT(cfg);
    return cfg;
}