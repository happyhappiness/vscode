static void riemann_msg_protobuf_free(Msg *msg) /* {{{ */
{
	size_t i;

	if (msg == NULL)
		return;

	for (i = 0; i < msg->n_events; i++)
	{
		riemann_event_protobuf_free (msg->events[i]);
		msg->events[i] = NULL;
	}

	sfree (msg->events);
	msg->n_events = 0;

	sfree (msg);
}