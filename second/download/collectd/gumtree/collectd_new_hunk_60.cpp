	fprintf (fh, "\n");
	fflush (fh);

	return (0);
} /* int us_handle_getval */

static int us_handle_listval (FILE *fh, char **fields, int fields_num)
{
	char buffer[1024];
	char **value_list = NULL;
	int value_list_len = 0;
	value_cache_t *entry;
	int i;

	if (fields_num != 1)
	{
		DEBUG ("unixsock plugin: us_handle_listval: "
				"Wrong number of fields: %i", fields_num);
		fprintf (fh, "-1 Wrong number of fields: Got %i, expected 1.\n",
				fields_num);
		fflush (fh);
		return (-1);
	}

	pthread_mutex_lock (&cache_lock);

	for (entry = cache_head; entry != NULL; entry = entry->next)
	{
		char **tmp;

		snprintf (buffer, sizeof (buffer), "%u %s\n",
				(unsigned int) entry->time, entry->name);
		buffer[sizeof (buffer) - 1] = '\0';
		
		tmp = realloc (value_list, sizeof (char *) * (value_list_len + 1));
		if (tmp == NULL)
			continue;
		value_list = tmp;

		value_list[value_list_len] = strdup (buffer);

		if (value_list[value_list_len] != NULL)
			value_list_len++;
	} /* for (entry) */

	pthread_mutex_unlock (&cache_lock);

	DEBUG ("unixsock plugin: us_handle_listval: value_list_len = %i", value_list_len);
	fprintf (fh, "%i Values found\n", value_list_len);
	for (i = 0; i < value_list_len; i++)
		fputs (value_list[i], fh);
	fflush (fh);

	return (0);
} /* int us_handle_listval */

static void *us_handle_client (void *arg)
{
	int fd;
	FILE *fh;
	char buffer[1024];
