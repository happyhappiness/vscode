static int wh_config_url (oconfig_item_t *ci) /* {{{ */
{
        wh_callback_t *cb;
        user_data_t user_data;
        int i;

        cb = malloc (sizeof (*cb));
        if (cb == NULL)
        {
                ERROR ("write_http plugin: malloc failed.");
                return (-1);
        }
        memset (cb, 0, sizeof (*cb));
        cb->location = NULL;
        cb->user = NULL;
        cb->pass = NULL;
        cb->credentials = NULL;
        cb->verify_peer = 1;
        cb->verify_host = 1;
        cb->cacert = NULL;
        cb->format = WH_FORMAT_COMMAND;
        cb->curl = NULL;

        pthread_mutex_init (&cb->send_lock, /* attr = */ NULL);

        config_set_string (&cb->location, ci);
        if (cb->location == NULL)
                return (-1);

        for (i = 0; i < ci->children_num; i++)
        {
                oconfig_item_t *child = ci->children + i;

                if (strcasecmp ("User", child->key) == 0)
                        config_set_string (&cb->user, child);
                else if (strcasecmp ("Password", child->key) == 0)
                        config_set_string (&cb->pass, child);
                else if (strcasecmp ("VerifyPeer", child->key) == 0)
                        config_set_boolean (&cb->verify_peer, child);
                else if (strcasecmp ("VerifyHost", child->key) == 0)
                        config_set_boolean (&cb->verify_host, child);
                else if (strcasecmp ("CACert", child->key) == 0)
                        config_set_string (&cb->cacert, child);
                else if (strcasecmp ("Format", child->key) == 0)
                        config_set_format (cb, child);
                else
                {
                        ERROR ("write_http plugin: Invalid configuration "
                                        "option: %s.", child->key);
                }
        }

        DEBUG ("write_http: Registering write callback with URL %s",
                        cb->location);

        memset (&user_data, 0, sizeof (user_data));
        user_data.data = cb;
        user_data.free_func = NULL;
        plugin_register_flush ("write_http", wh_flush, &user_data);

        user_data.free_func = wh_callback_free;
        plugin_register_write ("write_http", wh_write, &user_data);

        return (0);
}