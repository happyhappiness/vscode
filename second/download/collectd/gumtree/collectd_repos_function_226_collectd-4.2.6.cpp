static int csnmp_check_res_left_subtree (const host_definition_t *host,
    const data_definition_t *data,
    struct snmp_pdu *res)
{
  struct variable_list *vb;
  int num_checked;
  int num_left_subtree;
  int i;

  vb = res->variables;
  if (vb == NULL)
    return (-1);

  num_checked = 0;
  num_left_subtree = 0;

  /* check all the variables and count how many have left their subtree */
  for (vb = res->variables, i = 0;
      (vb != NULL) && (i < data->values_len);
      vb = vb->next_variable, i++)
  {
    num_checked++;
    if (snmp_oid_ncompare (data->values[i].oid,
	  data->values[i].oid_len,
	  vb->name, vb->name_length,
	  data->values[i].oid_len) != 0)
      num_left_subtree++;
  }

  /* check if enough variables have been returned */
  if (i < data->values_len)
  {
    ERROR ("snmp plugin: host %s: Expected %i variables, but got only %i",
	host->name, data->values_len, i);
    return (-1);
  }

  if (data->instance.oid.oid_len > 0)
  {
    if (vb == NULL)
    {
      ERROR ("snmp plugin: host %s: Expected one more variable for "
	  "the instance..");
      return (-1);
    }

    num_checked++;
    if (snmp_oid_ncompare (data->instance.oid.oid,
	  data->instance.oid.oid_len,
	  vb->name, vb->name_length,
	  data->instance.oid.oid_len) != 0)
      num_left_subtree++;
  }

  DEBUG ("snmp plugin: csnmp_check_res_left_subtree: %i of %i variables have "
      "left their subtree",
      num_left_subtree, num_checked);
  if (num_left_subtree >= num_checked)
    return (1);
  return (0);
}