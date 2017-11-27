static int cache_flush (void)
{
	char **keys = NULL;
	int    keys_num = 0;

	char **tmp;
	int    i;

	char   *key;
	time_t *value;
	avl_iterator_t *iter;

	time_t curtime = time (NULL);

	iter = avl_get_iterator (cache_tree);
	while (avl_iterator_next (iter, (void *) &key, (void *) &value) == 0)
	{
		if ((curtime - *value) <= cache_flush_interval)
			continue;
		tmp = (char **) realloc (keys,
				(keys_num + 1) * sizeof (char *));
		if (tmp == NULL)
		{
			sfree (keys);
			avl_iterator_destroy (iter);
			ERROR ("network plugin: cache_flush: realloc"
					" failed.");
			return (-1);
		}
		keys = tmp;
		keys[keys_num] = key;
		keys_num++;
	} /* while (avl_iterator_next) */
	avl_iterator_destroy (iter);

	for (i = 0; i < keys_num; i++)
	{
		if (avl_remove (cache_tree, keys[i], (void *) &key,
					(void *) &value) != 0)
		{
			WARNING ("network plugin: cache_flush: avl_remove"
					" (%s) failed.", keys[i]);
			continue;
		}

		sfree (key);
		sfree (value);
	}

	sfree (keys);

	DEBUG ("network plugin: cache_flush: Removed %i %s",
			keys_num, (keys_num == 1) ? "entry" : "entries");
	cache_flush_last = curtime;
	return (0);
}