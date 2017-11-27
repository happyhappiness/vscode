static int perl_flush(cdtime_t timeout, const char *identifier,
                      user_data_t *user_data) {
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

  /* For collectd-5.6 only, #1731 */
  if (user_data == NULL || user_data->data == NULL)
    return pplugin_call(aTHX_ PLUGIN_FLUSH_ALL, timeout, identifier);

  return pplugin_call(aTHX_ PLUGIN_FLUSH, user_data->data, timeout, identifier);
}