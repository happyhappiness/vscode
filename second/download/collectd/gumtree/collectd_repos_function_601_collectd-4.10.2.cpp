int fc_register_target (const char *name, target_proc_t proc) /* {{{ */
{
  fc_target_t *t;

  DEBUG ("fc_register_target (%s);", name);

  t = (fc_target_t *) malloc (sizeof (*t));
  if (t == NULL)
    return (-ENOMEM);
  memset (t, 0, sizeof (*t));

  sstrncpy (t->name, name, sizeof (t->name));
  memcpy (&t->proc, &proc, sizeof (t->proc));
  t->next = NULL;

  if (target_list_head == NULL)
  {
    target_list_head = t;
  }
  else
  {
    fc_target_t *ptr;

    ptr = target_list_head;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = t;
  }

  return (0);
}