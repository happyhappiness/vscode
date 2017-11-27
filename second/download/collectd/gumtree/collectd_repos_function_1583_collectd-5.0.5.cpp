meta_data_t *meta_data_create (void) /* {{{ */
{
  meta_data_t *md;

  md = (meta_data_t *) malloc (sizeof (*md));
  if (md == NULL)
  {
    ERROR ("meta_data_create: malloc failed.");
    return (NULL);
  }
  memset (md, 0, sizeof (*md));

  md->head = NULL;
  pthread_mutex_init (&md->lock, /* attr = */ NULL);

  return (md);
}