static int csnmp_dispatch_table (host_definition_t *host, data_definition_t *data,
    csnmp_list_instances_t *instance_list,
    csnmp_table_values_t **value_table)
{
  const data_set_t *ds;
  value_list_t vl = VALUE_LIST_INIT;

  csnmp_list_instances_t *instance_list_ptr;
  csnmp_table_values_t **value_table_ptr;

  int i;
  oid subid;
  int have_more;

  ds = plugin_get_ds (data->type);
  if (!ds)
  {
    ERROR ("snmp plugin: DataSet `%s' not defined.", data->type);
    return (-1);
  }
  assert (ds->ds_num == data->values_len);

  instance_list_ptr = instance_list;

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
    ERROR ("snmp plugin: malloc failed.");
    sfree (value_table_ptr);
    return (-1);
  }

  sstrncpy (vl.host, host->name, sizeof (vl.host));
  sstrncpy (vl.plugin, "snmp", sizeof (vl.plugin));

  vl.interval = host->interval;

  subid = 0;
  have_more = 1;

  while (have_more != 0)
  {
    if (instance_list != NULL)
    {
      while ((instance_list_ptr != NULL)
	  && (instance_list_ptr->subid < subid))
	instance_list_ptr = instance_list_ptr->next;

      if (instance_list_ptr == NULL)
      {
	have_more = 0;
	continue;
      }
      else if (instance_list_ptr->subid > subid)
      {
	subid = instance_list_ptr->subid;
	continue;
      }
    } /* if (instance_list != NULL) */

    for (i = 0; i < data->values_len; i++)
    {
      while ((value_table_ptr[i] != NULL)
	  && (value_table_ptr[i]->subid < subid))
	value_table_ptr[i] = value_table_ptr[i]->next;

      if (value_table_ptr[i] == NULL)
      {
	have_more = 0;
	break;
      }
      else if (value_table_ptr[i]->subid > subid)
      {
	subid = value_table_ptr[i]->subid;
	break;
      }
    } /* for (i = 0; i < columns; i++) */
    /* The subid has been increased - start scanning from the beginning
     * again.. */
    if (i < data->values_len)
      continue;

    /* if we reach this line, all value_table_ptr[i] are non-NULL and are set
     * to the same subid. instance_list_ptr is either NULL or points to the
     * same subid, too. */
#if COLLECT_DEBUG
    for (i = 1; i < data->values_len; i++)
    {
      assert (value_table_ptr[i] != NULL);
      assert (value_table_ptr[i-1]->subid == value_table_ptr[i]->subid);
    }
    assert ((instance_list_ptr == NULL)
	|| (instance_list_ptr->subid == value_table_ptr[0]->subid));
#endif

    sstrncpy (vl.type, data->type, sizeof (vl.type));

    {
      char temp[DATA_MAX_NAME_LEN];

      if (instance_list_ptr == NULL)
	ssnprintf (temp, sizeof (temp), "%"PRIu32, (uint32_t) subid);
      else
	sstrncpy (temp, instance_list_ptr->instance, sizeof (temp));

      if (data->instance_prefix == NULL)
	sstrncpy (vl.type_instance, temp, sizeof (vl.type_instance));
      else
	ssnprintf (vl.type_instance, sizeof (vl.type_instance), "%s%s",
	    data->instance_prefix, temp);
    }

    for (i = 0; i < data->values_len; i++)
      vl.values[i] = value_table_ptr[i]->value;

    /* If we get here `vl.type_instance' and all `vl.values' have been set */
    plugin_dispatch_values (&vl);

    subid++;
  } /* while (have_more != 0) */

  sfree (vl.values);
  sfree (value_table_ptr);

  return (0);
}