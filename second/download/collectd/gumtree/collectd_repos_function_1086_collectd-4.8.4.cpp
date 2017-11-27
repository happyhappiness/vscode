static int wh_config (oconfig_item_t *ci) /* {{{ */
{
        int i;

        for (i = 0; i < ci->children_num; i++)
        {
                oconfig_item_t *child = ci->children + i;

                if (strcasecmp ("URL", child->key) == 0)
                        wh_config_url (child);
                else
                {
                        ERROR ("write_http plugin: Invalid configuration "
                                        "option: %s.", child->key);
                }
        }

        return (0);
}