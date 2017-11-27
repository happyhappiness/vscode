static void add_hosts (void)
{
	hostlist_t *hl_this;
	hostlist_t *hl_prev;

	hl_this = hosts;
	hl_prev = NULL;
	while (hl_this != NULL)
	{
		DEBUG ("ping plugin: host = %s, wait_left = %i, "
				"wait_time = %i, next = %p",
				hl_this->host, hl_this->wait_left,
				hl_this->wait_time, (void *) hl_this->next);

		if (hl_this->wait_left <= 0)
		{
			if (ping_host_add (pingobj, hl_this->host) == 0)
			{
				DEBUG ("ping plugin: Successfully added host %s", hl_this->host);
				/* Remove the host from the linked list */
				if (hl_prev != NULL)
					hl_prev->next = hl_this->next;
				else
					hosts = hl_this->next;
				free (hl_this->host);
				free (hl_this);
				hl_this = (hl_prev != NULL) ? hl_prev : hosts;
			}
			else
			{
				WARNING ("ping plugin: Failed adding host "
						"`%s': %s", hl_this->host,
						ping_get_error (pingobj));
				hl_this->wait_left = hl_this->wait_time;
				hl_this->wait_time *= 2;
				if (hl_this->wait_time > 86400)
					hl_this->wait_time = 86400;
			}
		}
		else
		{
			hl_this->wait_left -= interval_g;
		}

		if (hl_this != NULL)
		{
			hl_prev = hl_this;
			hl_this = hl_this->next;
		}
	}
}