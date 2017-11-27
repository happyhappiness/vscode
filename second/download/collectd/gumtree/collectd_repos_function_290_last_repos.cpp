static int camqp_shutdown(void) /* {{{ */
{
  DEBUG("amqp plugin: Shutting down %zu subscriber threads.",
        subscriber_threads_num);

  subscriber_threads_running = 0;
  for (size_t i = 0; i < subscriber_threads_num; i++) {
    /* FIXME: Sending a signal is not very elegant here. Maybe find out how
     * to use a timeout in the thread and check for the variable in regular
     * intervals. */
    pthread_kill(subscriber_threads[i], SIGTERM);
    pthread_join(subscriber_threads[i], /* retval = */ NULL);
  }

  subscriber_threads_num = 0;
  sfree(subscriber_threads);

  DEBUG("amqp plugin: All subscriber threads exited.");

  return 0;
}