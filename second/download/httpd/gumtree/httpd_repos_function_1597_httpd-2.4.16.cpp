static int do_cache_negotiated_docs(server_rec *s)
{
    return (ap_get_module_config(s->module_config,
                                 &negotiation_module) != NULL);
}