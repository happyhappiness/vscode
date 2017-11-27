static int riemann_event_add_attribute(Event *event, /* {{{ */
		char const *key, char const *value)
{
	Attribute **new_attributes;
	Attribute *a;

	new_attributes = realloc (event->attributes,
			sizeof (*event->attributes) * (event->n_attributes + 1));
	if (new_attributes == NULL)
	{
		ERROR ("write_riemann plugin: realloc failed.");
		return (ENOMEM);
	}
	event->attributes = new_attributes;

	a = malloc (sizeof (*a));
	if (a == NULL)
	{
		ERROR ("write_riemann plugin: malloc failed.");
		return (ENOMEM);
	}
	attribute__init (a);

	a->key = strdup (key);
	if (value != NULL)
		a->value = strdup (value);

	event->attributes[event->n_attributes] = a;
	event->n_attributes++;

	return (0);
}