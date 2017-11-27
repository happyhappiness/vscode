static int rrd_queue_cache_entry (const char *filename)
{
	rrd_queue_t *queue_entry;

	queue_entry = (rrd_queue_t *) malloc (sizeof (rrd_queue_t));
	if (queue_entry == NULL)
		return (-1);

	queue_entry->filename = strdup (filename);
	if (queue_entry->filename == NULL)
	{
		free (queue_entry);
		return (-1);
	}

	queue_entry->next = NULL;

	pthread_mutex_lock (&queue_lock);
	if (queue_tail == NULL)
		queue_head = queue_entry;
	else
		queue_tail->next = queue_entry;
	queue_tail = queue_entry;
	pthread_cond_signal (&queue_cond);
	pthread_mutex_unlock (&queue_lock);

	DEBUG ("rrdtool plugin: Put `%s' into the update queue", filename);

	return (0);
}