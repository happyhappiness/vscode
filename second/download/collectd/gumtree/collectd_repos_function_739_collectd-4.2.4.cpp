int ping_host_remove (pingobj_t *obj, const char *host)
{
	pinghost_t *pre, *cur;

	pre = NULL;
	cur = obj->head;

	while (cur != NULL)
	{
		if (strcasecmp (host, cur->hostname))
			break;

		pre = cur;
		cur = cur->next;
	}

	if (cur == NULL)
	{
		ping_set_error (obj, "ping_host_remove", "Host not found");
		return (-1);
	}

	if (pre == NULL)
		obj->head = cur->next;
	else
		pre->next = cur->next;
	
	if (cur->fd >= 0)
		close (cur->fd);

	ping_free (cur);

	return (0);
}