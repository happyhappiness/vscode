static int wt_config_tsd(oconfig_item_t *ci)
{
    struct wt_callback *cb;
    user_data_t user_data;
    char callback_name[DATA_MAX_NAME_LEN];
    int i;

    cb = malloc(sizeof(*cb));
    if (cb == NULL)
    {
        ERROR("write_tsdb plugin: malloc failed.");
        return -1;
    }
    memset(cb, 0, sizeof(*cb));
    cb->sock_fd = -1;
    cb->node = NULL;
    cb->service = NULL;
    cb->host_tags = NULL;
    cb->store_rates = 0;

    pthread_mutex_init (&cb->send_lock, NULL);

    for (i = 0; i < ci->children_num; i++)
    {
        oconfig_item_t *child = ci->children + i;

        if (strcasecmp("Host", child->key) == 0)
            cf_util_get_string(child, &cb->node);
        else if (strcasecmp("Port", child->key) == 0)
            cf_util_get_service(child, &cb->service);
        else if (strcasecmp("HostTags", child->key) == 0)
            cf_util_get_string(child, &cb->host_tags);
        else if (strcasecmp("StoreRates", child->key) == 0)
            cf_util_get_boolean(child, &cb->store_rates);
        else if (strcasecmp("AlwaysAppendDS", child->key) == 0)
            cf_util_get_boolean(child, &cb->always_append_ds);
        else
        {
            ERROR("write_tsdb plugin: Invalid configuration "
                  "option: %s.", child->key);
        }
    }

    ssnprintf(callback_name, sizeof(callback_name), "write_tsdb/%s/%s",
              cb->node != NULL ? cb->node : WT_DEFAULT_NODE,
              cb->service != NULL ? cb->service : WT_DEFAULT_SERVICE);

    memset(&user_data, 0, sizeof(user_data));
    user_data.data = cb;
    user_data.free_func = wt_callback_free;
    plugin_register_write(callback_name, wt_write, &user_data);

    user_data.free_func = NULL;
    plugin_register_flush(callback_name, wt_flush, &user_data);

    return 0;
}