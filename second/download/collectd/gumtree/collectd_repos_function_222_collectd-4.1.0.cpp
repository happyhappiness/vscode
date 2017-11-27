static int csnmp_dispatch_table (host_definition_t *host, data_definition_t *data,
    csnmp_list_instances_t *instance_list,
    csnmp_table_values_t **value_table)
{
  const data_set_t *ds;
  value_list_t vl = VALUE_LIST_INIT;

  csnmp_list_instances_t *instance_list_ptr;
  csnmp_table_values_t **value_table_ptr;

  int i;

  ds = plugin_get_ds (data->type);
  if (!ds)
  {
    ERROR ("snmp plugin: DataSet `%s' not defined.", data->type);
    return (-1);
  }
  assert (ds->ds_num == data->values_len);

  value_table_ptr = (csnmp_table_values_t **) malloc (sizeof (csnmp_table_values_t *)
      * data->values_len);
  if (value_table_ptr == NULL)
    return (-1);
  for (i = 0; i < data->values_len; i++)
    value_table_ptr[i] = value_table[i];

  vl.values_len = ds->ds_num;
  vl.values = (value_t *) malloc (sizeof (value_t) * vl.values_len);
  if (vl.values == NULL)
  {
    sfree (value_table_ptr);
    return (-1);
  }

  strncpy (vl.host, host->name, sizeof (vl.host));
  vl.host[sizeof (vl.host) - 1] = '\0';
  strcpy (vl.plugin, "snmp");

  vl.interval = host->skip_num;
  vl.time = time (NULL);

  for (instance_list_ptr = instance_list;
      instance_list_ptr != NULL;
      instance_list_ptr = instance_list_ptr->next)
  {
    strncpy (vl.type_instance, instance_list_ptr->instance, sizeof (vl.type_instance));
    vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

    for (i = 0; i < data->values_len; i++)
    {
      while ((value_table_ptr[i] != NULL)
	  && (value_table_ptr[i]->subid < instance_list_ptr->subid))
	value_table_ptr[i] = value_table_ptr[i]->next;
      if ((value_table_ptr[i] == NULL)
	  || (value_table_ptr[i]->subid != instance_list_ptr->subid))
	break;
      vl.values[i] = value_table_ptr[i]->value;
    } /* for (data->values_len) */

    /* If the for-loop was aborted early, not all subid's match. */
    if (i < data->values_len)
    {
      DEBUG ("snmp plugin: host = %s; data = %s; i = %i; "
	  "Skipping SUBID %i",
	  host->name, data->name, i, instance_list_ptr->subid);
      continue;
    }

    /* If we get here `vl.type_instance' and all `vl.values' have been set */
    plugin_dispatch_values (data->type, &vl);
  } /* for (instance_list) */

  sfree (vl.values);
  sfree (value_table_ptr);

  return (0);
}