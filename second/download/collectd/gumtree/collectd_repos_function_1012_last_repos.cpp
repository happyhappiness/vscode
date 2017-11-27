static int perl_shutdown(void) {
  c_ithread_t *t;
  int ret;

  dTHX;

  plugin_unregister_complex_config("perl");
  plugin_unregister_read_group("perl");

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  log_debug("perl_shutdown: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);

  plugin_unregister_init("perl");
  plugin_unregister_flush("perl"); /* For collectd-5.6 only, #1731 */

  ret = pplugin_call(aTHX_ PLUGIN_SHUTDOWN);

  pthread_mutex_lock(&perl_threads->mutex);
  t = perl_threads->tail;

  while (NULL != t) {
    struct timespec ts_wait;
    c_ithread_t *thr = t;

    /* the pointer has to be advanced before destroying
     * the thread as this will free the memory */
    t = t->prev;

    thr->shutdown = 1;
    if (thr->running) {
      /* Give some time to thread to exit from Perl interpreter */
      WARNING("perl shutdown: Thread is running inside Perl. Waiting.");
      ts_wait.tv_sec = 0;
      ts_wait.tv_nsec = 500000;
      nanosleep(&ts_wait, NULL);
    }
    if (thr->running) {
      pthread_kill(thr->pthread, SIGTERM);
      ERROR("perl shutdown: Thread hangs inside Perl. Thread killed.");
    }
    c_ithread_destroy(thr);
  }

  pthread_mutex_unlock(&perl_threads->mutex);
  pthread_mutex_destroy(&perl_threads->mutex);
  pthread_mutexattr_destroy(&perl_threads->mutexattr);

  sfree(perl_threads);

  pthread_key_delete(perl_thr_key);

  PERL_SYS_TERM();

  plugin_unregister_shutdown("perl");
  return ret;
}