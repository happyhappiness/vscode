static int perl_write(const data_set_t *ds, const value_list_t *vl,
                      user_data_t *user_data) {
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

  /* Lock the base thread if this is not called from one of the read threads
   * to avoid race conditions with c_ithread_create(). See
   * https://github.com/collectd/collectd/issues/9 for details. */
  if (aTHX == perl_threads->head->interp)
    pthread_mutex_lock(&perl_threads->mutex);

  log_debug("perl_write: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);
  status = pplugin_call(aTHX_ PLUGIN_WRITE, user_data->data, ds, vl);

  if (aTHX == perl_threads->head->interp)
    pthread_mutex_unlock(&perl_threads->mutex);

  return status;
}