static int dumpio_pre_conn(conn_rec *c, void *csd)
{
    dumpio_conf_t *ptr =
    (dumpio_conf_t *) ap_get_module_config(c->base_server->module_config,
                                           &dumpio_module);
    
    if (ptr->enable_input)
        ap_add_input_filter("DUMPIO_IN", NULL, NULL, c);
    if (ptr->enable_output)
        ap_add_output_filter("DUMPIO_OUT", NULL, NULL, c);
    return OK;
}