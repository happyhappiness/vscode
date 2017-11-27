static int mysql_config(oconfig_item_t *ci) /* {{{ */
{
  if (ci == NULL)
    return (EINVAL);

  /* Fill the `mysql_database_t' structure.. */
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Database", child->key) == 0)
      mysql_config_database(child);
    else
      WARNING("mysql plugin: Option \"%s\" not allowed here.", child->key);
  }

  return (0);
}