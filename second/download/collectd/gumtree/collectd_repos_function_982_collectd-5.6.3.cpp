static int fc_destroy(int type, void **user_data) {
  pfc_user_data_t *data = *(pfc_user_data_t **)user_data;

  int ret = 0;

  dTHX;

  if ((NULL == perl_threads) || (NULL == data))
    return 0;

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  log_debug("fc_destroy: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);

  ret = fc_call(aTHX_ type, FC_CB_DESTROY, data);

  PFC_USER_DATA_FREE(data);
  *user_data = NULL;
  return ret;
}