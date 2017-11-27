static int md_entry_insert(meta_data_t *md, meta_entry_t *e) /* {{{ */
{
  meta_entry_t *this;
  meta_entry_t *prev;

  if ((md == NULL) || (e == NULL))
    return -EINVAL;

  pthread_mutex_lock(&md->lock);

  prev = NULL;
  this = md->head;
  while (this != NULL) {
    if (strcasecmp(e->key, this->key) == 0)
      break;

    prev = this;
    this = this->next;
  }

  if (this == NULL) {
    /* This key does not exist yet. */
    if (md->head == NULL)
      md->head = e;
    else {
      assert(prev != NULL);
      prev->next = e;
    }

    e->next = NULL;
  } else /* (this != NULL) */
  {
    if (prev == NULL)
      md->head = e;
    else
      prev->next = e;

    e->next = this->next;
  }

  pthread_mutex_unlock(&md->lock);

  if (this != NULL) {
    this->next = NULL;
    md_entry_free(this);
  }

  return 0;
}