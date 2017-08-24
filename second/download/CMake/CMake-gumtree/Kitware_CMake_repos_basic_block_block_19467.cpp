{
  int rc;
  _uv_barrier* b;

  if (barrier == NULL || barrier->b == NULL)
    return EINVAL;

  b = barrier->b;
  /* Lock the mutex*/
  if ((rc = pthread_mutex_lock(&b->mutex)) != 0)
    return rc;

  /* Increment the count. If this is the first thread to reach the threshold,
     wake up waiters, unlock the mutex, then return
     PTHREAD_BARRIER_SERIAL_THREAD. */
  if (++b->in == b->threshold) {
    b->in = 0;
    b->out = b->threshold - 1;
    rc = pthread_cond_signal(&b->cond);
    assert(rc == 0);

    pthread_mutex_unlock(&b->mutex);
    return PTHREAD_BARRIER_SERIAL_THREAD;
  }
  /* Otherwise, wait for other threads until in is set to 0,
     then return 0 to indicate this is not the first thread. */
  do {
    if ((rc = pthread_cond_wait(&b->cond, &b->mutex)) != 0)
      break;
  } while (b->in != 0);

  /* mark thread exit */
  b->out--;
  pthread_cond_signal(&b->cond);
  pthread_mutex_unlock(&b->mutex);
  return rc;
}