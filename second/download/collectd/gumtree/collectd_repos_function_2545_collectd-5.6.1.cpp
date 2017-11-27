meta_data_t *meta_data_create (void) /* {{{ */
{
  meta_data_t *md;

  md = calloc (1, sizeof (*md));
  if (md == NULL)
  {
    ERROR ("meta_data_create: calloc failed.");
    return (NULL);
  }

  pthread_mutex_init (&md->lock, /* attr = */ NULL);

  return (md);
}