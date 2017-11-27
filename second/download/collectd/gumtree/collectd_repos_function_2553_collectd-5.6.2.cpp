int meta_data_delete(meta_data_t *md, const char *key) /* {{{ */
{
  meta_entry_t *this;
  meta_entry_t *prev;

  if ((md == NULL) || (key == NULL))
    return (-EINVAL);

  pthread_mutex_lock(&md->lock);

  prev = NULL;
  this = md->head;
  while (this != NULL) {
    if (strcasecmp(key, this->key) == 0)
      break;

    prev = this;
    this = this->next;
  }

  if (this == NULL) {
    pthread_mutex_unlock(&md->lock);
    return (-ENOENT);
  }

  if (prev == NULL)
    md->head = this->next;
  else
    prev->next = this->next;

  pthread_mutex_unlock(&md->lock);

  this->next = NULL;
  md_entry_free(this);

  return (0);
}