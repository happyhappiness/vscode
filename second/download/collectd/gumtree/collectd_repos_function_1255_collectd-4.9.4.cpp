static int o_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp ("Query", child->key) == 0)
      udb_query_create (&queries, &queries_num, child,
          /* callback = */ NULL, /* legacy mode = */ 0);
    else if (strcasecmp ("Database", child->key) == 0)
      o_config_add_database (child);
    else
    {
      WARNING ("oracle plugin: Ignoring unknown config option `%s'.", child->key);
    }

    if (queries_num > 0)
    {
      DEBUG ("oracle plugin: o_config: queries_num = %zu; queries[0] = %p; udb_query_get_user_data (queries[0]) = %p;",
          queries_num, (void *) queries[0], udb_query_get_user_data (queries[0]));
    }
  } /* for (ci->children) */

  return (0);
}