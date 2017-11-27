static int camqp_config_set_format (oconfig_item_t *ci, /* {{{ */
        camqp_config_t *conf)
{
    char *string;
    int status;

    string = NULL;
    status = cf_util_get_string (ci, &string);
    if (status != 0)
        return (status);

    assert (string != NULL);
    if (strcasecmp ("Command", string) == 0)
        conf->format = CAMQP_FORMAT_COMMAND;
    else if (strcasecmp ("JSON", string) == 0)
        conf->format = CAMQP_FORMAT_JSON;
    else if (strcasecmp ("Graphite", string) == 0)
        conf->format = CAMQP_FORMAT_GRAPHITE;
    else
    {
        WARNING ("amqp plugin: Invalid format string: %s",
                string);
    }

    free (string);

    return (0);
}