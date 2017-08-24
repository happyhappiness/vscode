{
  int rc;
  _uv_barrier* b;

  if (barrier == NULL || count == 0)
    return EINVAL;

  if (barrier_attr != NULL)
    return ENOTSUP;

  b = uv__malloc(sizeof(*b));
  if (b == NULL)
    return ENOMEM;

  b->in = 0;
  b->out = 0;
  b->threshold = count;

  if ((rc = pthread_mutex_init(&b->mutex, NULL)) != 0)
    goto error2;
  if ((rc = pthread_cond_init(&b->cond, NULL)) != 0)
    goto error;

  barrier->b = b;
  return 0;

error:
  pthread_mutex_destroy(&b->mutex);
error2:
  uv__free(b);
  return rc;
}