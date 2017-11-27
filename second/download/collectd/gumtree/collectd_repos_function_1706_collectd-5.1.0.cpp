static int wg_config_carbon (oconfig_item_t *ci)
{
    struct wg_callback *cb;
    user_data_t user_data;
    char callback_name[DATA_MAX_NAME_LEN];
    int i;

    cb = malloc (sizeof (*cb));
    if (cb == NULL)
    {
        ERROR ("write_graphite plugin: malloc failed.");
        return (-1);
    }
    memset (cb, 0, sizeof (*cb));
    cb->sock_fd = -1;
    cb->node = NULL;
    cb->service = NULL;
    cb->prefix = NULL;
    cb->postfix = NULL;
    cb->escape_char = WG_DEFAULT_ESCAPE;
    cb->store_rates = 1;

    pthread_mutex_init (&cb->send_lock, /* attr = */ NULL);

    for (i = 0; i < ci->children_num; i++)
    {
        oconfig_item_t *child = ci->children + i;

        if (strcasecmp ("Host", child->key) == 0)
            cf_util_get_string (child, &cb->node);
        else if (strcasecmp ("Port", child->key) == 0)
            cf_util_get_service (child, &cb->service);
        else if (strcasecmp ("Prefix", child->key) == 0)
            cf_util_get_string (child, &cb->prefix);
        else if (strcasecmp ("Postfix", child->key) == 0)
            cf_util_get_string (child, &cb->postfix);
        else if (strcasecmp ("StoreRates", child->key) == 0)
            cf_util_get_boolean (child, &cb->store_rates);
        else if (strcasecmp ("SeparateInstances", child->key) == 0)
            cf_util_get_boolean (child, &cb->separate_instances);
        else if (strcasecmp ("AlwaysAppendDS", child->key) == 0)
            cf_util_get_boolean (child, &cb->always_append_ds);
        else if (strcasecmp ("EscapeCharacter", child->key) == 0)
            config_set_char (&cb->escape_char, child);
        else
        {
            ERROR ("write_graphite plugin: Invalid configuration "
                        "option: %s.", child->key);
        }
    }

    ssnprintf (callback_name, sizeof (callback_name), "write_graphite/%s/%s",
            cb->node != NULL ? cb->node : WG_DEFAULT_NODE,
            cb->service != NULL ? cb->service : WG_DEFAULT_SERVICE);

    memset (&user_data, 0, sizeof (user_data));
    user_data.data = cb;
    user_data.free_func = wg_callback_free;
    plugin_register_write (callback_name, wg_write, &user_data);

    user_data.free_func = NULL;
    plugin_register_flush (callback_name, wg_flush, &user_data);

    return (0);
}