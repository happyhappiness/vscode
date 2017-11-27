static int cdbi_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp ("Query", child->key) == 0)
      udb_query_create (&queries, &queries_num, child,
          /* callback = */ NULL);
    else if (strcasecmp ("Database", child->key) == 0)
      cdbi_config_add_database (child);
    else
    {
      WARNING ("dbi plugin: Ignoring unknown config option `%s'.", child->key);
    }
  } /* for (ci->children) */

  return (0);
}