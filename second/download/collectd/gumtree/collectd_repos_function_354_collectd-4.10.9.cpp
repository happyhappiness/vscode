static int csnmp_instance_list_add (csnmp_list_instances_t **head,
    csnmp_list_instances_t **tail,
    struct snmp_pdu const *res,
    oid_t const *root)
{
  csnmp_list_instances_t *il;
  struct variable_list *vb;
  oid_t vb_name;
  int status;

  /* Set vb on the last variable */
  for (vb = res->variables;
      (vb != NULL) && (vb->next_variable != NULL);
      vb = vb->next_variable)
    /* do nothing */;
  if (vb == NULL)
    return (-1);

  csnmp_oid_init (&vb_name, vb->name, vb->name_length);

  il = malloc (sizeof (*il));
  if (il == NULL)
  {
    ERROR ("snmp plugin: malloc failed.");
    return (-1);
  }
  memset (il, 0, sizeof (*il));
  il->next = NULL;

  status = csnmp_oid_suffix (&il->suffix, &vb_name, root);
  if (status != 0)
  {
    sfree (il);
    return (status);
  }

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