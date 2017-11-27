static int camqp_config (oconfig_item_t *ci) /* {{{ */
{
    for (int i = 0; i < ci->children_num; i++)
    {
        oconfig_item_t *child = ci->children + i;

        if (strcasecmp ("Publish", child->key) == 0)
            camqp_config_connection (child, /* publish = */ 1);
        else if (strcasecmp ("Subscribe", child->key) == 0)
            camqp_config_connection (child, /* publish = */ 0);
        else
            WARNING ("amqp plugin: Ignoring unknown config option \"%s\".",
                    child->key);
    } /* for (ci->children_num) */

    return (0);
}