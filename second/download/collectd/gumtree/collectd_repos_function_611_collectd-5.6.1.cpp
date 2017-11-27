static int agg_read (void) /* {{{ */
{
  cdtime_t t;
  int success;

  t = cdtime ();
  success = 0;

  pthread_mutex_lock (&agg_instance_list_lock);

  /* agg_instance_list_head only holds data, after the "write" callback has
   * been called with a matching value list at least once. So on startup,
   * there's a race between the aggregations read() and write() callback. If
   * the read() callback is called first, agg_instance_list_head is NULL and
   * "success" may be zero. This is expected and should not result in an error.
   * Therefore we need to handle this case separately. */
  if (agg_instance_list_head == NULL)
  {
    pthread_mutex_unlock (&agg_instance_list_lock);
    return (0);
  }

  for (agg_instance_t *this = agg_instance_list_head; this != NULL; this = this->next)
  {
    int status;

    status = agg_instance_read (this, t);
    if (status != 0)
      WARNING ("aggregation plugin: Reading an aggregation instance "
          "failed with status %i.", status);
    else
      success++;
  }

  pthread_mutex_unlock (&agg_instance_list_lock);

  return ((success > 0) ? 0 : -1);
}