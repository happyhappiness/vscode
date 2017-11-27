static value_list_t *plugin_write_dequeue(void) /* {{{ */
{
  write_queue_t *q;
  value_list_t *vl;

  pthread_mutex_lock(&write_lock);

  while (write_loop && (write_queue_head == NULL))
    pthread_cond_wait(&write_cond, &write_lock);

  if (write_queue_head == NULL) {
    pthread_mutex_unlock(&write_lock);
    return (NULL);
  }

  q = write_queue_head;
  write_queue_head = q->next;
  write_queue_length -= 1;
  if (write_queue_head == NULL) {
    write_queue_tail = NULL;
    assert(0 == write_queue_length);
  }

  pthread_mutex_unlock(&write_lock);

  (void)plugin_set_ctx(q->ctx);

  vl = q->vl;
  sfree(q);
  return (vl);
}