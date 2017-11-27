static int nut_read (void)
{
  nut_ups_t *ups;
  int success = 0;

  pthread_mutex_lock (&read_lock);
  success = read_busy;
  read_busy = 1;
  pthread_mutex_unlock (&read_lock);

  if (success != 0)
    return (0);

  for (ups = upslist_head; ups != NULL; ups = ups->next)
    if (nut_read_one (ups) == 0)
      success++;

  pthread_mutex_lock (&read_lock);
  read_busy = 0;
  pthread_mutex_unlock (&read_lock);

  return ((success != 0) ? 0 : -1);
}