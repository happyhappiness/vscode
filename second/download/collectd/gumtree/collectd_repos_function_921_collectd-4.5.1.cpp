void plugin_shutdown_all (void)
{
	int (*callback) (void);
	llentry_t *le;

	stop_threads ();

	if (list_shutdown == NULL)
		return;

	le = llist_head (list_shutdown);
	while (le != NULL)
	{
		callback = (int (*) (void)) le->value;

		/* Advance the pointer before calling the callback allows
		 * shutdown functions to unregister themselves. If done the
		 * other way around the memory `le' points to will be freed
		 * after callback returns. */
		le = le->next;

		(*callback) ();
	}
}