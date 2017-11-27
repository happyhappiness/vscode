static void riemann_event_protobuf_free (Event *event) /* {{{ */
{
	size_t i;

	if (event == NULL)
		return;

	sfree (event->state);
	sfree (event->service);
	sfree (event->host);
	sfree (event->description);

	strarray_free (event->tags, event->n_tags);
	event->tags = NULL;
	event->n_tags = 0;

	for (i = 0; i < event->n_attributes; i++)
	{
		sfree (event->attributes[i]->key);
		sfree (event->attributes[i]->value);
		sfree (event->attributes[i]);
	}
	sfree (event->attributes);
	event->n_attributes = 0;

	sfree (event);
}