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

  /* `value_list_head' and `value_list_tail' implement a linked list for each
   * value. `instance_list_head' and `instance_list_tail' implement a linked list of
   * instance names. This is used to jump gaps in the table. */
  csnmp_list_instances_t *instance_list_head;
  csnmp_list_instances_t *instance_list_tail;
  csnmp_table_values_t **value_list_head;
  csnmp_table_values_t **value_list_tail;

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

  /* We're going to construct n linked lists, one for each "value".
   * value_list_head will contain pointers to the heads of these linked lists,
   * value_list_tail will contain pointers to the tail of the lists. */
  value_list_head = calloc (data->values_len, sizeof (*value_list_head));
  value_list_tail = calloc (data->values_len, sizeof (*value_list_tail));
  if ((value_list_head == NULL) || (value_list_tail == NULL))
  {
    ERROR ("snmp plugin: csnmp_read_table: calloc failed.");
    sfree (oid_list);
    sfree (value_list_head);
    sfree (value_list_tail);
    return (-1);
  }

  instance_list_head = NULL;
  instance_list_tail = NULL;

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

    /* Copy the OID of the value used as instance to oid_list, if an instance
     * is configured. */
    if (data->instance.oid.oid_len > 0)
    {
      /* Allocate a new `csnmp_list_instances_t', insert the instance name and
       * add it to the list */
      if (csnmp_instance_list_add (&instance_list_head, &instance_list_tail,
            res, &data->instance.oid) != 0)
      {
        ERROR ("snmp plugin: csnmp_instance_list_add failed.");
        status = -1;
        break;
      }

      /* The instance OID is added to the list of OIDs to GET from the
       * snmp agent last, so set vb on the last variable returned and copy
       * that OID. */
      for (vb = res->variables;
          (vb != NULL) && (vb->next_variable != NULL);
          vb = vb->next_variable)
        /* do nothing */;
      assert (vb != NULL);

      /* Copy the OID of the instance value to oid_list[data->values_len].
       * "oid_list" is used for the next GETNEXT request. */
      memcpy (oid_list[data->values_len].oid, vb->name,
          sizeof (oid) * vb->name_length);
      oid_list[data->values_len].oid_len = vb->name_length;
    }

    /* Iterate over all the (non-instance) values returned by the agent. The
     * (i < value_len) check will make sure we're not handling the instance OID
     * twice. */
    for (vb = res->variables, i = 0;
        (vb != NULL) && (i < data->values_len);
        vb = vb->next_variable, i++)
    {
      csnmp_table_values_t *vt;
      oid_t vb_name;
      oid_t suffix;

      csnmp_oid_init (&vb_name, vb->name, vb->name_length);

      /* Calculate the current suffix. This is later used to check that the
       * suffix is increasing. This also checks if we left the subtree */
      status = csnmp_oid_suffix (&suffix, &vb_name, data->values + i);
      if (status != 0)
      {
        DEBUG ("snmp plugin: host = %s; data = %s; Value %i failed. "
            "It probably left its subtree.",
            host->name, data->name, i);
        continue;
      }

      /* Make sure the OIDs returned by the agent are increasing. Otherwise our
       * table matching algorithm will get confused. */
      if ((value_list_tail[i] != NULL)
          && (csnmp_oid_compare (&suffix, &value_list_tail[i]->suffix) <= 0))
      {
        DEBUG ("snmp plugin: host = %s; data = %s; i = %i; "
            "Suffix is not increasing.",
            host->name, data->name, i);
        continue;
      }

      vt = malloc (sizeof (*vt));
      if (vt == NULL)
      {
        ERROR ("snmp plugin: malloc failed.");
        status = -1;
        break;
      }
      memset (vt, 0, sizeof (*vt));

      vt->value = csnmp_value_list_to_value (vb, ds->ds[i].type,
          data->scale, data->shift);
      memcpy (&vt->suffix, &suffix, sizeof (vt->suffix));
      vt->next = NULL;

      if (value_list_tail[i] == NULL)
        value_list_head[i] = vt;
      else
        value_list_tail[i]->next = vt;
      value_list_tail[i] = vt;

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
    csnmp_dispatch_table (host, data, instance_list_head, value_list_head);

  /* Free all allocated variables here */
  while (instance_list_head != NULL)
  {
    csnmp_list_instances_t *next = instance_list_head->next;
    sfree (instance_list_head);
    instance_list_head = next;
  }

  for (i = 0; i < data->values_len; i++)
  {
    while (value_list_head[i] != NULL)
    {
      csnmp_table_values_t *next = value_list_head[i]->next;
      sfree (value_list_head[i]);
      value_list_head[i] = next;
    }
  }

  sfree (value_list_head);
  sfree (value_list_tail);
  sfree (oid_list);

  return (0);
}