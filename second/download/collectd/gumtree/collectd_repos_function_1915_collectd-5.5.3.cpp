static int wg_config_node (oconfig_item_t *ci)
{
    struct wg_callback *cb;
    user_data_t user_data;
    char callback_name[DATA_MAX_NAME_LEN];
    int i;
    int status = 0;

    cb = malloc (sizeof (*cb));
    if (cb == NULL)
    {
        ERROR ("write_graphite plugin: malloc failed.");
        return (-1);
    }
    memset (cb, 0, sizeof (*cb));
    cb->sock_fd = -1;
    cb->name = NULL;
    cb->node = NULL;
    cb->service = NULL;
    cb->protocol = NULL;
    cb->log_send_errors = WG_DEFAULT_LOG_SEND_ERRORS;
    cb->prefix = NULL;
    cb->postfix = NULL;
    cb->escape_char = WG_DEFAULT_ESCAPE;
    cb->format_flags = GRAPHITE_STORE_RATES;

    /* FIXME: Legacy configuration syntax. */
    if (strcasecmp ("Carbon", ci->key) != 0)
    {
        status = cf_util_get_string (ci, &cb->name);
        if (status != 0)
        {
            wg_callback_free (cb);
            return (status);
        }
    }

    pthread_mutex_init (&cb->send_lock, /* attr = */ NULL);
    C_COMPLAIN_INIT (&cb->init_complaint);

    for (i = 0; i < ci->children_num; i++)
    {
        oconfig_item_t *child = ci->children + i;

        if (strcasecmp ("Host", child->key) == 0)
            cf_util_get_string (child, &cb->node);
        else if (strcasecmp ("Port", child->key) == 0)
            cf_util_get_service (child, &cb->service);
        else if (strcasecmp ("Protocol", child->key) == 0)
        {
            cf_util_get_string (child, &cb->protocol);

            if (strcasecmp ("UDP", cb->protocol) != 0 &&
                strcasecmp ("TCP", cb->protocol) != 0)
            {
                ERROR ("write_graphite plugin: Unknown protocol (%s)",
                        cb->protocol);
                status = -1;
            }
        }
        else if (strcasecmp ("LogSendErrors", child->key) == 0)
            cf_util_get_boolean (child, &cb->log_send_errors);
        else if (strcasecmp ("Prefix", child->key) == 0)
            cf_util_get_string (child, &cb->prefix);
        else if (strcasecmp ("Postfix", child->key) == 0)
            cf_util_get_string (child, &cb->postfix);
        else if (strcasecmp ("StoreRates", child->key) == 0)
            cf_util_get_flag (child, &cb->format_flags,
                    GRAPHITE_STORE_RATES);
        else if (strcasecmp ("SeparateInstances", child->key) == 0)
            cf_util_get_flag (child, &cb->format_flags,
                    GRAPHITE_SEPARATE_INSTANCES);
        else if (strcasecmp ("AlwaysAppendDS", child->key) == 0)
            cf_util_get_flag (child, &cb->format_flags,
                    GRAPHITE_ALWAYS_APPEND_DS);
        else if (strcasecmp ("EscapeCharacter", child->key) == 0)
            config_set_char (&cb->escape_char, child);
        else
        {
            ERROR ("write_graphite plugin: Invalid configuration "
                        "option: %s.", child->key);
            status = -1;
        }

        if (status != 0)
            break;
    }

    if (status != 0)
    {
        wg_callback_free (cb);
        return (status);
    }

    /* FIXME: Legacy configuration syntax. */
    if (cb->name == NULL)
        ssnprintf (callback_name, sizeof (callback_name), "write_graphite/%s/%s/%s",
                cb->node != NULL ? cb->node : WG_DEFAULT_NODE,
                cb->service != NULL ? cb->service : WG_DEFAULT_SERVICE,
                cb->protocol != NULL ? cb->protocol : WG_DEFAULT_PROTOCOL);
    else
        ssnprintf (callback_name, sizeof (callback_name), "write_graphite/%s",
                cb->name);

    memset (&user_data, 0, sizeof (user_data));
    user_data.data = cb;
    user_data.free_func = wg_callback_free;
    plugin_register_write (callback_name, wg_write, &user_data);

    user_data.free_func = NULL;
    plugin_register_flush (callback_name, wg_flush, &user_data);

    return (0);
}