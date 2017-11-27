static int rrd_cache_flush_identifier (int timeout, const char *identifier)
{
  rrd_cache_t *rc;
  time_t now;
  int status;
  char key[2048];

  if (identifier == NULL)
  {
    rrd_cache_flush (timeout);
    return (0);
  }

  now = time (NULL);

  if (datadir == NULL)
    snprintf (key, sizeof (key), "%s.rrd",
        identifier);
  else
    snprintf (key, sizeof (key), "%s/%s.rrd",
        datadir, identifier);
  key[sizeof (key) - 1] = 0;

  status = c_avl_get (cache, key, (void *) &rc);
  if (status != 0)
  {
    WARNING ("rrdtool plugin: rrd_cache_flush_identifier: "
        "c_avl_get (%s) failed. Does that file really exist?",
        key);
    return (status);
  }

  if (rc->flags == FLAG_FLUSHQ)
  {
    status = 0;
  }
  else if (rc->flags == FLAG_QUEUED)
  {
    rrd_queue_dequeue (key, &queue_head, &queue_tail);
    status = rrd_queue_enqueue (key, &flushq_head, &flushq_tail);
    if (status == 0)
      rc->flags = FLAG_FLUSHQ;
  }
  else if ((now - rc->first_value) < timeout)
  {
    status = 0;
  }
  else if (rc->values_num > 0)
  {
    status = rrd_queue_enqueue (key, &flushq_head, &flushq_tail);
    if (status == 0)
      rc->flags = FLAG_FLUSHQ;
  }

  return (status);
}