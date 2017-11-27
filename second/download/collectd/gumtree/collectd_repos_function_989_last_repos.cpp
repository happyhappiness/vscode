static int call_pv_locked(pTHX_ const char *sub_name) {
  _Bool old_running;
  int ret;

  c_ithread_t *t = (c_ithread_t *)pthread_getspecific(perl_thr_key);
  if (t == NULL) /* thread destroyed */
    return 0;

  old_running = t->running;
  t->running = 1;

  if (t->shutdown) {
    t->running = old_running;
    return 0;
  }

  ret = call_pv(sub_name, G_SCALAR | G_EVAL);

  t->running = old_running;
  return ret;
}