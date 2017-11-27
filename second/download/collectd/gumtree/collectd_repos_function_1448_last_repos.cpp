static int ovs_events_ctx_unlock() {
  pthread_mutex_unlock(&ovs_events_ctx.mutex);
  return 0;
}