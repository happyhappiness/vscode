void c_heap_destroy(c_heap_t *h) {
  if (h == NULL)
    return;

  h->list_len = 0;
  h->list_size = 0;
  free(h->list);
  h->list = NULL;

  pthread_mutex_destroy(&h->lock);

  free(h);
}