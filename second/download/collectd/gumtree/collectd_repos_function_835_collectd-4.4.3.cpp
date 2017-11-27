void plugin_flush_all (int timeout)
{
	int (*callback) (int);
	llentry_t *le;

	if (list_flush == NULL)
		return;

	le = llist_head (list_flush);
	while (le != NULL)
	{
		callback = (int (*) (int)) le->value;
		le = le->next;

		(*callback) (timeout);
	}
}