static void *rrd_queue_thread (void *data)
{
        struct timeval tv_next_update;
        struct timeval tv_now;

        gettimeofday (&tv_next_update, /* timezone = */ NULL);

	while (42)
	{
		rrd_queue_t *queue_entry;
		rrd_cache_t *cache_entry;
		char **values;
		int    values_num;
		int    i;

                pthread_mutex_lock (&queue_lock);
                /* Wait for values to arrive */
                while (true)
                {
                  struct timespec ts_wait;
                  int status;

                  while ((flushq_head == NULL) && (queue_head == NULL)
                      && (do_shutdown == 0))
                    pthread_cond_wait (&queue_cond, &queue_lock);

                  if ((flushq_head == NULL) && (queue_head == NULL))
                    break;

                  /* Don't delay if there's something to flush */
                  if (flushq_head != NULL)
                    break;

                  /* Don't delay if we're shutting down */
                  if (do_shutdown != 0)
                    break;

                  /* Don't delay if no delay was configured. */
                  if (write_rate <= 0.0)
                    break;

                  gettimeofday (&tv_now, /* timezone = */ NULL);
                  status = timeval_sub_timespec (&tv_next_update, &tv_now,
                      &ts_wait);
                  /* We're good to go */
                  if (status != 0)
                    break;

                  /* We're supposed to wait a bit with this update, so we'll
                   * wait for the next addition to the queue or to the end of
                   * the wait period - whichever comes first. */
                  ts_wait.tv_sec = tv_next_update.tv_sec;
                  ts_wait.tv_nsec = 1000 * tv_next_update.tv_usec;

                  status = pthread_cond_timedwait (&queue_cond, &queue_lock,
                      &ts_wait);
                  if (status == ETIMEDOUT)
                    break;
                } /* while (true) */

                /* XXX: If you need to lock both, cache_lock and queue_lock, at
                 * the same time, ALWAYS lock `cache_lock' first! */

                /* We're in the shutdown phase */
                if ((flushq_head == NULL) && (queue_head == NULL))
                {
                  pthread_mutex_unlock (&queue_lock);
                  break;
                }

                if (flushq_head != NULL)
                {
                  /* Dequeue the first flush entry */
                  queue_entry = flushq_head;
                  if (flushq_head == flushq_tail)
                    flushq_head = flushq_tail = NULL;
                  else
                    flushq_head = flushq_head->next;
                }
                else /* if (queue_head != NULL) */
                {
                  /* Dequeue the first regular entry */
                  queue_entry = queue_head;
                  if (queue_head == queue_tail)
                    queue_head = queue_tail = NULL;
                  else
                    queue_head = queue_head->next;
                }

		/* Unlock the queue again */
		pthread_mutex_unlock (&queue_lock);

		/* We now need the cache lock so the entry isn't updated while
		 * we make a copy of it's values */
		pthread_mutex_lock (&cache_lock);

		c_avl_get (cache, queue_entry->filename, (void *) &cache_entry);

		values = cache_entry->values;
		values_num = cache_entry->values_num;

		cache_entry->values = NULL;
		cache_entry->values_num = 0;
		cache_entry->flags = FLAG_NONE;

		pthread_mutex_unlock (&cache_lock);

		/* Update `tv_next_update' */
		if (write_rate > 0.0) 
                {
                  gettimeofday (&tv_now, /* timezone = */ NULL);
                  tv_next_update.tv_sec = tv_now.tv_sec;
                  tv_next_update.tv_usec = tv_now.tv_usec
                    + ((suseconds_t) (1000000 * write_rate));
                  while (tv_next_update.tv_usec > 1000000)
                  {
                    tv_next_update.tv_sec++;
                    tv_next_update.tv_usec -= 1000000;
                  }
                }

		/* Write the values to the RRD-file */
		srrd_update (queue_entry->filename, NULL,
				values_num, (const char **)values);
		DEBUG ("rrdtool plugin: queue thread: Wrote %i values to %s",
				values_num, queue_entry->filename);

		for (i = 0; i < values_num; i++)
		{
			sfree (values[i]);
		}
		sfree (values);
		sfree (queue_entry->filename);
		sfree (queue_entry);
	} /* while (42) */

	pthread_mutex_lock (&cache_lock);
	c_avl_destroy (cache);
	cache = NULL;
	pthread_mutex_unlock (&cache_lock);

	pthread_exit ((void *) 0);
	return ((void *) 0);
}