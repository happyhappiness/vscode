static int cache_check (const char *type, const value_list_t *vl)
{
	char key[1024];
	time_t *value = NULL;
	int retval = -1;

	if (cache_tree == NULL)
		return (-1);

	if (format_name (key, sizeof (key), vl->host, vl->plugin,
				vl->plugin_instance, type, vl->type_instance))
		return (-1);

	pthread_mutex_lock (&cache_lock);

	if (c_avl_get (cache_tree, key, (void *) &value) == 0)
	{
		if (*value < vl->time)
		{
			*value = vl->time;
			retval = 0;
		}
		else
		{
			DEBUG ("network plugin: cache_check: *value = %i >= vl->time = %i",
					(int) *value, (int) vl->time);
			retval = 1;
		}
	}
	else
	{
		char *key_copy = strdup (key);
		value = malloc (sizeof (time_t));
		if ((key_copy != NULL) && (value != NULL))
		{
			*value = vl->time;
			c_avl_insert (cache_tree, key_copy, value);
			retval = 0;
		}
		else
		{
			sfree (key_copy);
			sfree (value);
		}
	}

	if ((time (NULL) - cache_flush_last) > cache_flush_interval)
		cache_flush ();

	pthread_mutex_unlock (&cache_lock);

	DEBUG ("network plugin: cache_check: key = %s; time = %i; retval = %i",
			key, (int) vl->time, retval);

	return (retval);
}