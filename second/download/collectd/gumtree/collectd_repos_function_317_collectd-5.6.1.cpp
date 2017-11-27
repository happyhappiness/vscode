static int check_ignorelist (const char *dev,
    const char *type, const char *type_instance)
{
  assert ((dev != NULL) && (type != NULL));

  if (ir_ignorelist_head == NULL)
    return (ir_ignorelist_invert ? 0 : 1);

  for (ir_ignorelist_t *i = ir_ignorelist_head; i != NULL; i = i->next)
  {
    /* i->device == NULL  =>  match all devices */
    if ((i->device != NULL)
        && (strcasecmp (i->device, dev) != 0))
      continue;

    if (strcasecmp (i->type, type) != 0)
      continue;

    if ((i->inst != NULL) && (type_instance != NULL)
        && (strcasecmp (i->inst, type_instance) != 0))
      continue;

    DEBUG ("netlink plugin: check_ignorelist: "
        "(dev = %s; type = %s; inst = %s) matched "
        "(dev = %s; type = %s; inst = %s)",
        dev, type,
        type_instance == NULL ? "(nil)" : type_instance,
        i->device == NULL ? "(nil)" : i->device,
        i->type,
        i->inst == NULL ? "(nil)" : i->inst);

    return (ir_ignorelist_invert ? 0 : 1);
  } /* for i */

  return (ir_ignorelist_invert);
}