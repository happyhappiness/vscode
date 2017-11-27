c_heap_t *c_heap_create (int (*compare) (const void *, const void *))
{
  c_heap_t *h;

  if (compare == NULL)
    return (NULL);

  h = calloc (1, sizeof (*h));
  if (h == NULL)
    return (NULL);

  pthread_mutex_init (&h->lock, /* attr = */ NULL);
  h->compare = compare;

  h->list = NULL;
  h->list_len = 0;
  h->list_size = 0;

  return (h);
}