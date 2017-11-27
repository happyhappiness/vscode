static int fc_exec(int type, const data_set_t *ds, const value_list_t *vl,
                   notification_meta_t **meta, void **user_data) {
  pfc_user_data_t *data = *(pfc_user_data_t **)user_data;

  dTHX;

  if (NULL == perl_threads)
    return 0;

  assert(NULL != data);

  if (NULL == aTHX) {
    c_ithread_t *t = NULL;

    pthread_mutex_lock(&perl_threads->mutex);
    t = c_ithread_create(perl_threads->head->interp);
    pthread_mutex_unlock(&perl_threads->mutex);

    aTHX = t->interp;
  }

  log_debug("fc_exec: c_ithread: interp = %p (active threads: %i)", aTHX,
            perl_threads->number_of_threads);

  return fc_call(aTHX_ type, FC_CB_EXEC, data, ds, vl, meta);
}