static int register_callback (llist_t **list, /* {{{ */
		const char *name, callback_func_t *cf)
{
	llentry_t *le;
	char *key;

	if (*list == NULL)
	{
		*list = llist_create ();
		if (*list == NULL)
		{
			ERROR ("plugin: register_callback: "
					"llist_create failed.");
			destroy_callback (cf);
			return (-1);
		}
	}

	key = strdup (name);
	if (key == NULL)
	{
		ERROR ("plugin: register_callback: strdup failed.");
		destroy_callback (cf);
		return (-1);
	}

	le = llist_search (*list, name);
	if (le == NULL)
	{
		le = llentry_create (key, cf);
		if (le == NULL)
		{
			ERROR ("plugin: register_callback: "
					"llentry_create failed.");
			sfree (key);
			destroy_callback (cf);
			return (-1);
		}

		llist_append (*list, le);
	}
	else
	{
		callback_func_t *old_cf;

		old_cf = le->value;
		le->value = cf;

		WARNING ("plugin: register_callback: "
				"a callback named `%s' already exists - "
				"overwriting the old entry!", name);

		destroy_callback (old_cf);
		sfree (key);
	}

	return (0);
}