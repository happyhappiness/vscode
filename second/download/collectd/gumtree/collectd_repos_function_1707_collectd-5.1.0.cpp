static int wg_config (oconfig_item_t *ci)
{
    int i;

    for (i = 0; i < ci->children_num; i++)
    {
        oconfig_item_t *child = ci->children + i;

        if (strcasecmp ("Carbon", child->key) == 0)
            wg_config_carbon (child);
        else
        {
            ERROR ("write_graphite plugin: Invalid configuration "
                    "option: %s.", child->key);
        }
    }

    return (0);
}