static int agg_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  pthread_mutex_lock (&agg_instance_list_lock);

  if (lookup == NULL)
  {
    lookup = lookup_create (agg_lookup_class_callback,
        agg_lookup_obj_callback,
        agg_lookup_free_class_callback,
        agg_lookup_free_obj_callback);
    if (lookup == NULL)
    {
      pthread_mutex_unlock (&agg_instance_list_lock);
      ERROR ("aggregation plugin: lookup_create failed.");
      return (-1);
    }
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Aggregation", child->key) == 0)
      agg_config_aggregation (child);
    else
      WARNING ("aggregation plugin: The \"%s\" key is not allowed inside "
          "<Plugin aggregation /> blocks and will be ignored.", child->key);
  }

  pthread_mutex_unlock (&agg_instance_list_lock);

  return (0);
}