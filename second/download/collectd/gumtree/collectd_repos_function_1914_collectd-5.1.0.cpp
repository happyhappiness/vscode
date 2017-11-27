static int lcc_identifier_cmp (const void *a, const void *b)
{
  const lcc_identifier_t *ident_a, *ident_b;

  int status;

  ident_a = a;
  ident_b = b;

  status = strcasecmp (ident_a->host, ident_b->host);
  if (status != 0)
    return (status);

  status = strcmp (ident_a->plugin, ident_b->plugin);
  if (status != 0)
    return (status);

  if ((*ident_a->plugin_instance != '\0') || (*ident_b->plugin_instance != '\0'))
  {
    if (*ident_a->plugin_instance == '\0')
      return (-1);
    else if (*ident_b->plugin_instance == '\0')
      return (1);

    status = strcmp (ident_a->plugin_instance, ident_b->plugin_instance);
    if (status != 0)
      return (status);
  }

  status = strcmp (ident_a->type, ident_b->type);
  if (status != 0)
    return (status);

  if ((*ident_a->type_instance != '\0') || (*ident_b->type_instance != '\0'))
  {
    if (*ident_a->type_instance == '\0')
      return (-1);
    else if (*ident_b->type_instance == '\0')
      return (1);

    status = strcmp (ident_a->type_instance, ident_b->type_instance);
    if (status != 0)
      return (status);
  }
  return (0);
}