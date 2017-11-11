static void *create_netware_dir_config(apr_pool_t *p, char *dir)
{
    netware_dir_config *new = (netware_dir_config*) apr_palloc(p, sizeof(netware_dir_config));

    new->file_type_handlers = apr_table_make(p, 10);
    new->file_handler_mode = apr_table_make(p, 10);
    new->extra_env_vars = apr_table_make(p, 10);

    apr_table_set(new->file_type_handlers, "NLM", "OS");

    return new;
}