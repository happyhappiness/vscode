static int plugin_shutdown(void) /* {{{ */
{
  if (collector_thread_running) {
    int status;

    DEBUG("pinba plugin: Shutting down collector thread.");
    collector_thread_do_shutdown = 1;

    status = pthread_join(collector_thread_id, /* retval = */ NULL);
    if (status != 0) {
      char errbuf[1024];
      ERROR("pinba plugin: pthread_join(3) failed: %s",
            sstrerror(status, errbuf, sizeof(errbuf)));
    }

    collector_thread_running = 0;
    collector_thread_do_shutdown = 0;
  } /* if (collector_thread_running) */

  return 0;
}