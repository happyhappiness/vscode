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

  if (host->sess_handle == NULL)
  {
    DEBUG ("snmp plugin: csnmp_read_table: host->sess_handle == NULL");
    return (-1);
  }

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
  {
    ERROR ("snmp plugin: csnmp_read_table: malloc failed.");
    return (-1);
  }
  memcpy (oid_list, data->values, data->values_len * sizeof (oid_t));
  if (data->instance.oid.oid_len > 0)
    memcpy (oid_list + data->values_len, &data->instance.oid, sizeof (oid_t));
  else
    oid_list_len--;

  /* Allocate the `value_table' */
  value_table = (csnmp_table_values_t **) malloc (sizeof (csnmp_table_values_t *)
      * 2 * data->values_len);
  if (value_table == NULL)
  {
    ERROR ("snmp plugin: csnmp_read_table: malloc failed.");
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
    req = snmp_pdu_create (SNMP_MSG_GETNEXT);
    if (req == NULL)
    {
      ERROR ("snmp plugin: snmp_pdu_create failed.");
      status = -1;
      break;
    }

    for (i = 0; (uint32_t) i < oid_list_len; i++)
      snmp_add_null_var (req, oid_list[i].oid, oid_list[i].oid_len);

    res = NULL;
    status = snmp_sess_synch_response (host->sess_handle, req, &res);

    if ((status != STAT_SUCCESS) || (res == NULL))
    {
      char *errstr = NULL;

      snmp_sess_error (host->sess_handle, NULL, NULL, &errstr);

      c_complain (LOG_ERR, &host->complaint,
	  "snmp plugin: host %s: snmp_sess_synch_response failed: %s",
	  host->name, (errstr == NULL) ? "Unknown problem" : errstr);

      if (res != NULL)
	snmp_free_pdu (res);
      res = NULL;

      sfree (errstr);
      csnmp_host_close_session (host);

      status = -1;
      break;
    }
    status = 0;
    assert (res != NULL);
    c_release (LOG_INFO, &host->complaint,
	"snmp plugin: host %s: snmp_sess_synch_response successful.",
	host->name);

    vb = res->variables;
    if (vb == NULL)
    {
      status = -1;
      break;
    }

    /* Check if all values (and possibly the instance) have left their
     * subtree */
    if (csnmp_check_res_left_subtree (host, data, res) != 0)
    {
      status = 0;
      break;
    }

    /* if an instance-OID is configured.. */
    if (data->instance.oid.oid_len > 0)
    {
      /* Allocate a new `csnmp_list_instances_t', insert the instance name and
       * add it to the list */
      if (csnmp_instance_list_add (&instance_list, &instance_list_ptr,
	    res) != 0)
      {
	ERROR ("snmp plugin: csnmp_instance_list_add failed.");
	status = -1;
	break;
      }

      /* Set vb on the last variable */
      for (vb = res->variables;
	  (vb != NULL) && (vb->next_variable != NULL);
	  vb = vb->next_variable)
	/* do nothing */;
      assert (vb != NULL);

      /* Copy OID to oid_list[data->values_len] */
      memcpy (oid_list[data->values_len].oid, vb->name,
	  sizeof (oid) * vb->name_length);
      oid_list[data->values_len].oid_len = vb->name_length;
    }

    for (vb = res->variables, i = 0;
	(vb != NULL) && (i < data->values_len);
	vb = vb->next_variable, i++)
    {
      csnmp_table_values_t *vt;

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
	DEBUG ("snmp plugin: host = %s; data = %s; i = %i; "
	    "SUBID is not increasing.",
	    host->name, data->name, i);
	continue;
      }

      vt = (csnmp_table_values_t *) malloc (sizeof (csnmp_table_values_t));
      if (vt == NULL)
      {
	ERROR ("snmp plugin: malloc failed.");
	status = -1;
	break;
      }

      vt->subid = vb->name[vb->name_length - 1];
      vt->value = csnmp_value_list_to_value (vb, ds->ds[i].type,
	  data->scale, data->shift);
      vt->next = NULL;

      if (value_table_ptr[i] == NULL)
	value_table[i] = vt;
      else
	value_table_ptr[i]->next = vt;
      value_table_ptr[i] = vt;

      /* Copy OID to oid_list[i + 1] */
      memcpy (oid_list[i].oid, vb->name, sizeof (oid) * vb->name_length);
      oid_list[i].oid_len = vb->name_length;
    } /* for (i = data->values_len) */

    if (res != NULL)
      snmp_free_pdu (res);
    res = NULL;
  } /* while (status == 0) */

  if (res != NULL)
    snmp_free_pdu (res);
  res = NULL;

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