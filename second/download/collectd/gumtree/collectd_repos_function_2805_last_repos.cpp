void *c_heap_get_root(c_heap_t *h) {
  void *ret = NULL;

  if (h == NULL)
    return NULL;

  pthread_mutex_lock(&h->lock);

  if (h->list_len == 0) {
    pthread_mutex_unlock(&h->lock);
    return NULL;
  } else if (h->list_len == 1) {
    ret = h->list[0];
    h->list[0] = NULL;
    h->list_len = 0;
  } else /* if (h->list_len > 1) */
  {
    ret = h->list[0];
    h->list[0] = h->list[h->list_len - 1];
    h->list[h->list_len - 1] = NULL;
    h->list_len--;

    reheap(h, /* root = */ 0, DIR_DOWN);
  }

  /* free some memory */
  if ((h->list_len + 32) < h->list_size) {
    void **tmp;

    tmp = realloc(h->list, (h->list_len + 16) * sizeof(*h->list));
    if (tmp != NULL) {
      h->list = tmp;
      h->list_size = h->list_len + 16;
    }
  }

  pthread_mutex_unlock(&h->lock);

  return ret;
}