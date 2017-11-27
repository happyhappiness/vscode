static int fc_config_add_match (fc_match_t **matches_head, /* {{{ */
    oconfig_item_t *ci)
{
  fc_match_t *m;
  fc_match_t *ptr;
  int status;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("Filter subsystem: `Match' blocks require "
        "exactly one string argument.");
    return (-1);
  }

  ptr = match_list_head;
  while (ptr != NULL)
  {
    if (strcasecmp (ptr->name, ci->values[0].value.string) == 0)
      break;
    ptr = ptr->next;
  }

  if (ptr == NULL)
  {
    WARNING ("Filter subsystem: Cannot find a \"%s\" match. "
        "Did you load the appropriate plugin?",
        ci->values[0].value.string);
    return (-1);
  }

  m = (fc_match_t *) malloc (sizeof (*m));
  if (m == NULL)
  {
    ERROR ("fc_config_add_match: malloc failed.");
    return (-1);
  }
  memset (m, 0, sizeof (*m));

  sstrncpy (m->name, ptr->name, sizeof (m->name));
  memcpy (&m->proc, &ptr->proc, sizeof (m->proc));
  m->user_data = NULL;
  m->next = NULL;

  if (m->proc.create != NULL)
  {
    status = (*m->proc.create) (ci, &m->user_data);
    if (status != 0)
    {
      WARNING ("Filter subsystem: Failed to create a %s match.",
          m->name);
      fc_free_matches (m);
      return (-1);
    }
  }

  if (*matches_head != NULL)
  {
    ptr = *matches_head;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = m;
  }
  else
  {
    *matches_head = m;
  }

  return (0);
}