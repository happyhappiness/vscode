static int csnmp_read_table (host_definition_t *host, data_definition_t *data)
{
  struct snmp_pdu *req;
  struct snmp_pdu *res;
  struct variable_list *vb;

  const data_set_t *ds;
  oid_t *oid_list;
  uint32_t oid_list_len;

  int status;
  int i;

  /* `value_table' and `value_table_ptr' implement a linked list for each
   * value. `instance_list' and `instance_list_ptr' implement a linked list of
   * instance names. This is used to jump gaps in the table. */
  csnmp_list_instances_t *instance_list;
  csnmp_list_instances_t *instance_list_ptr;
  csnmp_table_values_t **value_table;
  csnmp_table_values_t **value_table_ptr;

  DEBUG ("snmp plugin: csnmp_read_table (host = %s, data = %s)",
      host->name, data->name);

  ds = plugin_get_ds (data->type);
  if (!ds)
  {
    ERROR ("snmp plugin: DataSet `%s' not defined.", data->type);
    return (-1);
  }

  if (ds->ds_num != data->values_len)
  {
    ERROR ("snmp plugin: DataSet `%s' requires %i values, but config talks about %i",
	data->type, ds->ds_num, data->values_len);
    return (-1);
  }

  /* We need a copy of all the OIDs, because GETNEXT will destroy them. */
  oid_list_len = data->values_len + 1;
  oid_list = (oid_t *) malloc (sizeof (oid_t) * (oid_list_len));
  if (oid_list == NULL)
    return (-1);
  memcpy (oid_list, &data->instance.oid, sizeof (oid_t));
  for (i = 0; i < data->values_len; i++)
    memcpy (oid_list + (i + 1), data->values + i, sizeof (oid_t));

  /* Allocate the `value_table' */
  value_table = (csnmp_table_values_t **) malloc (sizeof (csnmp_table_values_t *)
      * 2 * data->values_len);
  if (value_table == NULL)
  {
    sfree (oid_list);
    return (-1);
  }
  memset (value_table, '\0', sizeof (csnmp_table_values_t *) * 2 * data->values_len);
  value_table_ptr = value_table + data->values_len;
  
  instance_list = NULL;
  instance_list_ptr = NULL;

  status = 0;
  while (status == 0)
  {
    csnmp_list_instances_t *il;

    req = snmp_pdu_create (SNMP_MSG_GETNEXT);
    if (req == NULL)
    {
      ERROR ("snmp plugin: snmp_pdu_create failed.");
      status = -1;
      break;
    }

    for (i = 0; i < oid_list_len; i++)
      snmp_add_null_var (req, oid_list[i].oid, oid_list[i].oid_len);

    status = snmp_sess_synch_response (host->sess_handle, req, &res);

    if (status != STAT_SUCCESS)
    {
      char *errstr = NULL;

      snmp_sess_error (host->sess_handle, NULL, NULL, &errstr);
      ERROR ("snmp plugin: snmp_sess_synch_response failed: %s",
	  (errstr == NULL) ? "Unknown problem" : errstr);
      csnmp_host_close_session (host);

      status = -1;
      break;
    }
    status = 0;
    assert (res != NULL);

    vb = res->variables;
    if (vb == NULL)
    {
      status = -1;
      break;
    }

    /* Check if we left the subtree */
    if (snmp_oid_ncompare (data->instance.oid.oid, data->instance.oid.oid_len,
	  vb->name, vb->name_length,
	  data->instance.oid.oid_len) != 0)
      break;

    /* Allocate a new `csnmp_list_instances_t', insert the instance name and
     * add it to the list */
    il = (csnmp_list_instances_t *) malloc (sizeof (csnmp_list_instances_t));
    if (il == NULL)
    {
      status = -1;
      break;
    }
    il->subid = vb->name[vb->name_length - 1];
    il->next = NULL;

    /* Get instance name */
    if ((vb->type == ASN_OCTET_STR) || (vb->type == ASN_BIT_STR))
    {
      char *ptr;
      size_t instance_len;

      instance_len = sizeof (il->instance) - 1;
      if (instance_len > vb->val_len)
	instance_len = vb->val_len;

      strncpy (il->instance, (char *) ((vb->type == ASN_OCTET_STR)
	    ? vb->val.string
	    : vb->val.bitstring),
	  instance_len);
      il->instance[instance_len] = '\0';

      for (ptr = il->instance; *ptr != '\0'; ptr++)
      {
	if ((*ptr > 0) && (*ptr < 32))
	  *ptr = ' ';
	else if (*ptr == '/')
	  *ptr = '_';
      }
      DEBUG ("snmp plugin: il->instance = `%s';", il->instance);
    }
    else
    {
      value_t val = csnmp_value_list_to_value (vb, DS_TYPE_COUNTER);
      snprintf (il->instance, sizeof (il->instance),
	  "%llu", val.counter);
    }
    il->instance[sizeof (il->instance) - 1] = '\0';
    DEBUG ("snmp plugin: data = `%s'; il->instance = `%s';",
	data->name, il->instance);

    if (instance_list_ptr == NULL)
      instance_list = il;
    else
      instance_list_ptr->next = il;
    instance_list_ptr = il;

    /* Copy OID to oid_list[0] */
    memcpy (oid_list[0].oid, vb->name, sizeof (oid) * vb->name_length);
    oid_list[0].oid_len = vb->name_length;

    for (i = 0; i < data->values_len; i++)
    {
      csnmp_table_values_t *vt;

      vb = vb->next_variable;
      if (vb == NULL)
      {
	status = -1;
	break;
      }

      /* Check if we left the subtree */
      if (snmp_oid_ncompare (data->values[i].oid,
	    data->values[i].oid_len,
	    vb->name, vb->name_length,
	    data->values[i].oid_len) != 0)
      {
	DEBUG ("snmp plugin: host = %s; data = %s; Value %i left its subtree.",
	    host->name, data->name, i);
	continue;
      }

      if ((value_table_ptr[i] != NULL)
	  && (vb->name[vb->name_length - 1] <= value_table_ptr[i]->subid))
      {
	DEBUG ("snmp plugin: host = %s; data = %s; i = %i; SUBID is not increasing.",
	    host->name, data->name, i);
	continue;
      }

      vt = (csnmp_table_values_t *) malloc (sizeof (csnmp_table_values_t));
      if (vt != NULL)
      {
	vt->subid = vb->name[vb->name_length - 1];
	vt->value = csnmp_value_list_to_value (vb, ds->ds[i].type);
	vt->next = NULL;

	if (value_table_ptr[i] == NULL)
	  value_table[i] = vt;
	else
	  value_table_ptr[i]->next = vt;
	value_table_ptr[i] = vt;
      }

      /* Copy OID to oid_list[i + 1] */
      memcpy (oid_list[i + 1].oid, vb->name, sizeof (oid) * vb->name_length);
      oid_list[i + 1].oid_len = vb->name_length;
    } /* for (i = data->values_len) */

    if (res != NULL)
      snmp_free_pdu (res);
    res = NULL;
  } /* while (status == 0) */

  if (status == 0)
    csnmp_dispatch_table (host, data, instance_list, value_table);

  /* Free all allocated variables here */
  while (instance_list != NULL)
  {
    instance_list_ptr = instance_list->next;
    sfree (instance_list);
    instance_list = instance_list_ptr;
  }

  for (i = 0; i < data->values_len; i++)
  {
    csnmp_table_values_t *tmp;
    while (value_table[i] != NULL)
    {
      tmp = value_table[i]->next;
      sfree (value_table[i]);
      value_table[i] = tmp;
    }
  }

  sfree (value_table);
  sfree (oid_list);

  return (0);
}