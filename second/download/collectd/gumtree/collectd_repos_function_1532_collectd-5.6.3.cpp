static int rrd_queue_dequeue(const char *filename, rrd_queue_t **head,
                             rrd_queue_t **tail) {
  rrd_queue_t *this;
  rrd_queue_t *prev;

  pthread_mutex_lock(&queue_lock);

  prev = NULL;
  this = *head;

  while (this != NULL) {
    if (strcmp(this->filename, filename) == 0)
      break;

    prev = this;
    this = this->next;
  }

  if (this == NULL) {
    pthread_mutex_unlock(&queue_lock);
    return (-1);
  }

  if (prev == NULL)
    *head = this->next;
  else
    prev->next = this->next;

  if (this->next == NULL)
    *tail = prev;

  pthread_mutex_unlock(&queue_lock);

  sfree(this->filename);
  sfree(this);

  return (0);
}