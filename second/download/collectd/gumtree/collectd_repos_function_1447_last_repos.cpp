static int ovs_events_ctx_lock() {
  pthread_mutex_lock(&ovs_events_ctx.mutex);
  return 1;
}