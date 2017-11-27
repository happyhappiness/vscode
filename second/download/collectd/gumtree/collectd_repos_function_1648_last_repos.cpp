static int rrd_queue_enqueue(const char *filename, rrd_queue_t **head,
                             rrd_queue_t **tail) {
  rrd_queue_t *queue_entry;

  queue_entry = malloc(sizeof(*queue_entry));
  if (queue_entry == NULL)
    return -1;

  queue_entry->filename = strdup(filename);
  if (queue_entry->filename == NULL) {
    free(queue_entry);
    return -1;
  }

  queue_entry->next = NULL;

  pthread_mutex_lock(&queue_lock);

  if (*tail == NULL)
    *head = queue_entry;
  else
    (*tail)->next = queue_entry;
  *tail = queue_entry;

  pthread_cond_signal(&queue_cond);
  pthread_mutex_unlock(&queue_lock);

  return 0;
}