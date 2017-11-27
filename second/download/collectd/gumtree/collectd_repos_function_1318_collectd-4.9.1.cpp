static int udb_legacy_result_create (const char *query_name, /* {{{ */
    udb_result_t **r_head, oconfig_item_t *ci, size_t position)
{
  udb_result_t *r;

  if ((ci->values_num < 1) || (ci->values_num > 2)
      || (ci->values[0].type != OCONFIG_TYPE_STRING)
      || ((ci->values_num == 2)
        && (ci->values[1].type != OCONFIG_TYPE_STRING)))
  {
    WARNING ("db query utils: The `Column' block needs either one or two "
        "string arguments.");
    return (-1);
  }

  r = (udb_result_t *) malloc (sizeof (*r));
  if (r == NULL)
  {
    ERROR ("db query utils: malloc failed.");
    return (-1);
  }
  memset (r, 0, sizeof (*r));

  r->legacy_mode = 1;
  r->legacy_position = position;

  r->type = strdup (ci->values[0].value.string);
  if (r->type == NULL)
  {
    ERROR ("db query utils: strdup failed.");
    free (r);
    return (-1);
  }

  r->instance_prefix = NULL;
  if (ci->values_num == 2)
  {
    r->instance_prefix = strdup (ci->values[1].value.string);
    if (r->instance_prefix == NULL)
    {
      ERROR ("db query utils: strdup failed.");
      free (r->type);
      free (r);
      return (-1);
    }
  }

  /* If all went well, add this result to the list of results. */
  if (*r_head == NULL)
  {
    *r_head = r;
  }
  else
  {
    udb_result_t *last;

    last = *r_head;
    while (last->next != NULL)
      last = last->next;

    last->next = r;
  }

  return (0);
}