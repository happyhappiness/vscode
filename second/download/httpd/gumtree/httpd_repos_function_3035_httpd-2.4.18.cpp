static void *merge_netware_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    netware_dir_config *base = (netware_dir_config *) basev;
    netware_dir_config *add = (netware_dir_config *) addv;
    netware_dir_config *new = (netware_dir_config *) apr_palloc(p, sizeof(netware_dir_config));

    new->file_type_handlers = apr_table_overlay(p, add->file_type_handlers, base->file_type_handlers);
    new->file_handler_mode = apr_table_overlay(p, add->file_handler_mode, base->file_handler_mode);
    new->extra_env_vars = apr_table_overlay(p, add->extra_env_vars, base->extra_env_vars);

    return new;
}