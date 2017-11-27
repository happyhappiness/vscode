static void log_list_callbacks (llist_t **list, /* {{{ */
				const char *comment)
{
	char *str;
	int len;
	llentry_t *le;
	int i;
	int n;
	char **keys;

	n = llist_size(*list);
	if (n == 0)
	{
		INFO("%s [none]", comment);
		return;
	}

	keys = calloc(n, sizeof(char*));

	if (keys == NULL)
	{
		ERROR("%s: failed to allocate memory for list of callbacks",
		      comment);

		return;
	}

	for (le = llist_head (*list), i = 0, len = 0;
	     le != NULL;
	     le = le->next, i++)
	{
		keys[i] = le->key;
		len += strlen(le->key) + 6;
	}
	str = malloc(len + 10);
	if (str == NULL)
	{
		ERROR("%s: failed to allocate memory for list of callbacks",
		      comment);
	}
	else
	{
		*str = '\0';
		strjoin(str, len, keys, n, "', '");
		INFO("%s ['%s']", comment, str);
		free(str);
	}
	free(keys);
}