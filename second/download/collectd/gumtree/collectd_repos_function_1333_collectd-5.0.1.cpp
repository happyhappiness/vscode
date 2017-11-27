static int config_set_boolean (int *dest, oconfig_item_t *ci) /* {{{ */
{
        if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
        {
                WARNING ("write_http plugin: The `%s' config option "
                                "needs exactly one boolean argument.", ci->key);
                return (-1);
        }

        *dest = ci->values[0].value.boolean ? 1 : 0;

        return (0);
}