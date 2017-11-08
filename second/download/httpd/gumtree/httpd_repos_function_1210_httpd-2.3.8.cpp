static void ap_dbd_sql_init(server_rec *s, const char *query)
{
    svr_cfg *svr;
    const char **arr_item;

    svr = ap_get_module_config(s->module_config, &dbd_module);
    if (!svr) {
         /* some modules may call from within config directive handlers, and
          * if these are called in a server context that contains no mod_dbd
          * config directives, then we have to create our own server config
          */
         svr = create_dbd_config(config_pool, s);
         ap_set_module_config(s->module_config, &dbd_module, svr);
    }

    if (query) {
        arr_item = apr_array_push(svr->cfg->init_queries);
        *arr_item = query;
    }
}