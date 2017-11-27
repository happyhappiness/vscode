static int network_config_set_cache_flush (const oconfig_item_t *ci) /* {{{ */
{
  int tmp;
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
  {
    WARNING ("network plugin: The `CacheFlush' config option needs exactly "
        "one numeric argument.");
    return (-1);
  }

  tmp = (int) ci->values[0].value.number;
  if (tmp > 0)
    cache_flush_interval = tmp;

  return (0);
}