static double get_drop_probability(void) /* {{{ */
{
  long pos;
  long size;
  long wql;

  pthread_mutex_lock(&write_lock);
  wql = write_queue_length;
  pthread_mutex_unlock(&write_lock);

  if (wql < write_limit_low)
    return 0.0;
  if (wql >= write_limit_high)
    return 1.0;

  pos = 1 + wql - write_limit_low;
  size = 1 + write_limit_high - write_limit_low;

  return (double)pos / (double)size;
}