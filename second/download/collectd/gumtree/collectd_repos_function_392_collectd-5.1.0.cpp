static int csnmp_instance_list_add (csnmp_list_instances_t **head,
    csnmp_list_instances_t **tail,
    const struct snmp_pdu *res,
    const host_definition_t *hd, const data_definition_t *dd)
{
  csnmp_list_instances_t *il;
  struct variable_list *vb;

  /* Set vb on the last variable */
  for (vb = res->variables;
      (vb != NULL) && (vb->next_variable != NULL);
      vb = vb->next_variable)
    /* do nothing */;
  if (vb == NULL)
    return (-1);

  il = (csnmp_list_instances_t *) malloc (sizeof (csnmp_list_instances_t));
  if (il == NULL)
  {
    ERROR ("snmp plugin: malloc failed.");
    return (-1);
  }
  il->subid = vb->name[vb->name_length - 1];
  il->next = NULL;

  /* Get instance name */
  if ((vb->type == ASN_OCTET_STR) || (vb->type == ASN_BIT_STR))
  {
    char *ptr;

    csnmp_strvbcopy (il->instance, vb, sizeof (il->instance));

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
    value_t val = csnmp_value_list_to_value (vb, DS_TYPE_COUNTER,
        /* scale = */ 1.0, /* shift = */ 0.0, hd->name, dd->name);
    ssnprintf (il->instance, sizeof (il->instance),
	"%llu", val.counter);
  }

  /* TODO: Debugging output */

  if (*head == NULL)
    *head = il;
  else
    (*tail)->next = il;
  *tail = il;

  return (0);
}