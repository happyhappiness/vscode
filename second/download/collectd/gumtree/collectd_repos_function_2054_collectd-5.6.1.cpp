static int wg_config (oconfig_item_t *ci)
{
    for (int i = 0; i < ci->children_num; i++)
    {
        oconfig_item_t *child = ci->children + i;

        if (strcasecmp ("Node", child->key) == 0)
            wg_config_node (child);
        /* FIXME: Remove this legacy mode in version 6. */
        else if (strcasecmp ("Carbon", child->key) == 0)
            wg_config_node (child);
        else
        {
            ERROR ("write_graphite plugin: Invalid configuration "
                    "option: %s.", child->key);
        }
    }

    return (0);
}