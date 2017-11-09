static int is_unsafe(server_rec *s) 
{
    core_server_config *conf = ap_get_core_module_config(s->module_config);
    return (conf->http_conformance == AP_HTTP_CONFORMANCE_UNSAFE);
}