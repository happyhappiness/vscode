static int unlock_file (char const *filename) /* {{{ */
{
  async_create_file_t *this;
  async_create_file_t *prev;


  pthread_mutex_lock (&async_creation_lock);

  prev = NULL;
  for (this = async_creation_list; this != NULL; this = this->next)
  {
    if (strcmp (filename, this->filename) == 0)
      break;
    prev = this;
  }

  if (this == NULL)
  {
    pthread_mutex_unlock (&async_creation_lock);
    return (ENOENT);
  }

  if (prev == NULL)
  {
    assert (this == async_creation_list);
    async_creation_list = this->next;
  }
  else
  {
    assert (this == prev->next);
    prev->next = this->next;
  }
  this->next = NULL;

  pthread_mutex_unlock (&async_creation_lock);

  sfree (this->filename);
  sfree (this);

  return (0);
}