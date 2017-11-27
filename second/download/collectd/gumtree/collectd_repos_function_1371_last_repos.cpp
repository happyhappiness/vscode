static void *collector_thread(void *arg) /* {{{ */
{
  receive_loop();

  memset(&collector_thread_id, 0, sizeof(collector_thread_id));
  collector_thread_running = 0;
  pthread_exit(NULL);
  return NULL;
}