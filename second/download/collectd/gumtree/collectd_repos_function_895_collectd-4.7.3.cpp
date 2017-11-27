static int mt_config_add_time_t (time_t *ret_value, /* {{{ */
    oconfig_item_t *ci)
{

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
  {
    ERROR ("timediff match: `%s' needs exactly one numeric argument.",
        ci->key);
    return (-1);
  }

  *ret_value = (time_t) ci->values[0].value.number;

  return (0);
}