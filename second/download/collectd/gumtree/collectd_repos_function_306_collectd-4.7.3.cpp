static int nut_add_ups (const char *name)
{
  nut_ups_t *ups;
  int status;

  DEBUG ("nut plugin: nut_add_ups (name = %s);", name);

  ups = (nut_ups_t *) malloc (sizeof (nut_ups_t));
  if (ups == NULL)
  {
    ERROR ("nut plugin: nut_add_ups: malloc failed.");
    return (1);
  }
  memset (ups, '\0', sizeof (nut_ups_t));

  status = upscli_splitname (name, &ups->upsname, &ups->hostname,
      &ups->port);
  if (status != 0)
  {
    ERROR ("nut plugin: nut_add_ups: upscli_splitname (%s) failed.", name);
    free_nut_ups_t (ups);
    return (1);
  }

  if (upslist_head == NULL)
    upslist_head = ups;
  else
  {
    nut_ups_t *last = upslist_head;
    while (last->next != NULL)
      last = last->next;
    last->next = ups;
  }

  return (0);
}