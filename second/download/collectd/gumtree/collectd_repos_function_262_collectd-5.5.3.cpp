fbhash_t *fbh_create (const char *file) /* {{{ */
{
  fbhash_t *h;
  int status;

  if (file == NULL)
    return (NULL);

  h = malloc (sizeof (*h));
  if (h == NULL)
    return (NULL);
  memset (h, 0, sizeof (*h));

  h->filename = strdup (file);
  if (h->filename == NULL)
  {
    free (h);
    return (NULL);
  }

  h->mtime = 0;
  pthread_mutex_init (&h->lock, /* attr = */ NULL);

  status = fbh_check_file (h);
  if (status != 0)
  {
    fbh_destroy (h);
    free (h);
    return (NULL);
  }

  return (h);
}