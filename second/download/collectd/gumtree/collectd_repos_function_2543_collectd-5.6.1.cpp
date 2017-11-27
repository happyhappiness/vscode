static int md_entry_insert_clone (meta_data_t *md, meta_entry_t *orig) /* {{{ */
{
  meta_entry_t *e;
  meta_entry_t *this;
  meta_entry_t *prev;

  /* WARNINGS :
   *  - we do not check that md and e != NULL here. You should have done it before.
   *  - we do not use the lock. You should have set it before.
   */

  e = md_entry_clone_contents(orig);

  prev = NULL;
  this = md->head;
  while (this != NULL)
  {
    if (strcasecmp (e->key, this->key) == 0)
      break;

    prev = this;
    this = this->next;
  }

  if (this == NULL)
  {
    /* This key does not exist yet. */
    if (md->head == NULL)
      md->head = e;
    else
    {
      assert (prev != NULL);
      prev->next = e;
    }

    e->next = NULL;
  }
  else /* (this != NULL) */
  {
    if (prev == NULL)
      md->head = e;
    else
      prev->next = e;

    e->next = this->next;
  }

  if (this != NULL)
  {
    this->next = NULL;
    md_entry_free (this);
  }

  return (0);
}