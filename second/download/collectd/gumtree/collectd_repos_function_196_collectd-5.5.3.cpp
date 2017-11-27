static int lock_file (char const *filename) /* {{{ */
{
  async_create_file_t *ptr;
  struct stat sb;
  int status;

  pthread_mutex_lock (&async_creation_lock);

  for (ptr = async_creation_list; ptr != NULL; ptr = ptr->next)
    if (strcmp (filename, ptr->filename) == 0)
      break;

  if (ptr != NULL)
  {
    pthread_mutex_unlock (&async_creation_lock);
    return (EEXIST);
  }

  status = stat (filename, &sb);
  if ((status == 0) || (errno != ENOENT))
  {
    pthread_mutex_unlock (&async_creation_lock);
    return (EEXIST);
  }

  ptr = malloc (sizeof (*ptr));
  if (ptr == NULL)
  {
    pthread_mutex_unlock (&async_creation_lock);
    return (ENOMEM);
  }

  ptr->filename = strdup (filename);
  if (ptr->filename == NULL)
  {
    pthread_mutex_unlock (&async_creation_lock);
    sfree (ptr);
    return (ENOMEM);
  }

  ptr->next = async_creation_list;
  async_creation_list = ptr;

  pthread_mutex_unlock (&async_creation_lock);

  return (0);
}