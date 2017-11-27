static void ovs_db_callback_remove(ovs_db_t *pdb, ovs_callback_t *del_cb) {
  pthread_mutex_lock(&pdb->mutex);
  ovs_callback_t *pre_cb = del_cb->prev;
  ovs_callback_t *next_cb = del_cb->next;

  if (next_cb)
    next_cb->prev = del_cb->prev;

  if (pre_cb)
    pre_cb->next = del_cb->next;
  else
    pdb->remote_cb = del_cb->next;

  free(del_cb);
  pthread_mutex_unlock(&pdb->mutex);
}