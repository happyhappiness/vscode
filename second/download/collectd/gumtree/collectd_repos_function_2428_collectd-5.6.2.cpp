int fc_register_match(const char *name, match_proc_t proc) /* {{{ */
{
  fc_match_t *m;

  DEBUG("fc_register_match (%s);", name);

  m = calloc(1, sizeof(*m));
  if (m == NULL)
    return (-ENOMEM);

  sstrncpy(m->name, name, sizeof(m->name));
  memcpy(&m->proc, &proc, sizeof(m->proc));

  if (match_list_head == NULL) {
    match_list_head = m;
  } else {
    fc_match_t *ptr;

    ptr = match_list_head;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = m;
  }

  return (0);
}