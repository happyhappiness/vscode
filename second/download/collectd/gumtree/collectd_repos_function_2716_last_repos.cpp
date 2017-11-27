int fc_configure(const oconfig_item_t *ci) /* {{{ */
{
  fc_init_once();

  if (ci == NULL)
    return -EINVAL;

  if (strcasecmp("Chain", ci->key) == 0)
    return fc_config_add_chain(ci);

  WARNING("Filter subsystem: Unknown top level config option `%s'.", ci->key);

  return -1;
}