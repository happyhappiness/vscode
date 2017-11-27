static void perl_log(int level, const char *msg, user_data_t *user_data) {
  dTHX;

  if (NULL == perl_threads)
    return;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  /* Lock the base thread if this is not called from one of the read threads
   * to avoid race conditions with c_ithread_create(). See
   * https://github.com/collectd/collectd/issues/9 for details.
   */

  if (aTHX == perl_threads->head->interp)
    pthread_mutex_lock(&perl_threads->mutex);

  pplugin_call(aTHX_ PLUGIN_LOG, user_data->data, level, msg);

  if (aTHX == perl_threads->head->interp)
    pthread_mutex_unlock(&perl_threads->mutex);

  return;
}