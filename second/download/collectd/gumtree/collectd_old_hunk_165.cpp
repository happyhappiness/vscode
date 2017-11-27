		(*callback) (level, msg);

		le = le->next;
	}
} /* void plugin_log */

void plugin_complain (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;

	if (c->delay > 0)
	{
		c->delay--;
		return;
	}

	if (c->interval < interval_g)
		c->interval = interval_g;
	else
		c->interval *= 2;

	if (c->interval > 86400)
		c->interval = 86400;

	c->delay = c->interval / interval_g;

	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	plugin_log (level, message);
}

void plugin_relief (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;

	if (c->interval == 0)
		return;

	c->interval = 0;

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
