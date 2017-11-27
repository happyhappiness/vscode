static void wt_callback_free(void *data) {
  struct wt_callback *cb;

  if (data == NULL)
    return;

  cb = data;

  pthread_mutex_lock(&cb->send_lock);

  wt_flush_nolock(0, cb);

  close(cb->sock_fd);
  cb->sock_fd = -1;

  sfree(cb->node);
  sfree(cb->service);
  sfree(cb->host_tags);

  pthread_mutex_destroy(&cb->send_lock);

  sfree(cb);
}