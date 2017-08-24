{
  int rc;
  _uv_barrier* b;

  if (barrier == NULL || barrier->b == NULL)
    return EINVAL;

  b = barrier->b;

  if ((rc = pthread_mutex_lock(&b->mutex)) != 0)
    return rc;

  if (b->in > 0 || b->out > 0)
    rc = EBUSY;

  pthread_mutex_unlock(&b->mutex);

  if (rc)
    return rc;

  pthread_cond_destroy(&b->cond);
  pthread_mutex_destroy(&b->mutex);
  uv__free(barrier->b);
  barrier->b = NULL;
  return 0;
}