
	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	plugin_log (level, message);
}

const data_set_t *plugin_get_ds (const char *name)
{
	data_set_t *ds;
	llentry_t *le;

	le = llist_search (list_data_set, name);
	if (le == NULL)
	{
		DEBUG ("No such dataset registered: %s", name);
		return (NULL);
	}

	ds = (data_set_t *) le->value;

	return (ds);
} /* data_set_t *plugin_get_ds */
