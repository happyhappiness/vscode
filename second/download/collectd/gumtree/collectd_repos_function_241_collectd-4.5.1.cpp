static int csnmp_instance_list_add (csnmp_list_instances_t **head,
    csnmp_list_instances_t **tail,
    const struct snmp_pdu *res)
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
    size_t instance_len;

    memset (il->instance, 0, sizeof (il->instance));
    instance_len = sizeof (il->instance) - 1;
    if (instance_len > vb->val_len)
      instance_len = vb->val_len;

    sstrncpy (il->instance, (char *) ((vb->type == ASN_OCTET_STR)
	  ? vb->val.string
	  : vb->val.bitstring),
	instance_len + 1);

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
    value_t val = csnmp_value_list_to_value (vb, DS_TYPE_COUNTER, 1.0, 0.0);
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