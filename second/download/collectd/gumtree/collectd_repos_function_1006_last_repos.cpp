static int perl_init(void) {
  int status;
  dTHX;

  if (NULL == perl_threads)
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  log_debug("perl_init: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);

  /* Lock the base thread to avoid race conditions with c_ithread_create().
   * See https://github.com/collectd/collectd/issues/9 and
   *     https://github.com/collectd/collectd/issues/1706 for details.
   */
  assert(aTHX == perl_threads->head->interp);
  pthread_mutex_lock(&perl_threads->mutex);

  status = pplugin_call(aTHX_ PLUGIN_INIT);

  pthread_mutex_unlock(&perl_threads->mutex);

  return status;
}