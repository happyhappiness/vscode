static int plugin_write_enqueue (value_list_t const *vl) /* {{{ */
{
	write_queue_t *q;

	q = malloc (sizeof (*q));
	if (q == NULL)
		return (ENOMEM);
	q->next = NULL;

	q->vl = plugin_value_list_clone (vl);
	if (q->vl == NULL)
	{
		sfree (q);
		return (ENOMEM);
	}

	/* Store context of caller (read plugin); otherwise, it would not be
	 * available to the write plugins when actually dispatching the
	 * value-list later on. */
	q->ctx = plugin_get_ctx ();

	pthread_mutex_lock (&write_lock);

	if (write_queue_tail == NULL)
	{
		write_queue_head = q;
		write_queue_tail = q;
		write_queue_length = 1;
	}
	else
	{
		write_queue_tail->next = q;
		write_queue_tail = q;
		write_queue_length += 1;
	}

	pthread_cond_signal (&write_cond);
	pthread_mutex_unlock (&write_lock);

	return (0);
}