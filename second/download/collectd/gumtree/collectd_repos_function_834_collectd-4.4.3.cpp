int plugin_flush_one (int timeout, const char *name)
{
	int (*callback) (int);
	llentry_t *le;
	int status;

	if (list_flush == NULL)
		return (-1);

	le = llist_search (list_flush, name);
	if (le == NULL)
		return (-1);
	callback = (int (*) (int)) le->value;

	status = (*callback) (timeout);

	return (status);
}