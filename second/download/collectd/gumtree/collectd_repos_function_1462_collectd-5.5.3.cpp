static Msg *riemann_value_list_to_protobuf (struct riemann_host const *host, /* {{{ */
					    data_set_t const *ds,
					    value_list_t const *vl,
					    int *statuses)
{
	Msg *msg;
	size_t i;
	gauge_t *rates = NULL;

	/* Initialize the Msg structure. */
	msg = malloc (sizeof (*msg));
	if (msg == NULL)
	{
		ERROR ("write_riemann plugin: malloc failed.");
		return (NULL);
	}
	memset (msg, 0, sizeof (*msg));
	msg__init (msg);

	/* Set up events. First, the list of pointers. */
	msg->n_events = (size_t) vl->values_len;
	msg->events = calloc (msg->n_events, sizeof (*msg->events));
	if (msg->events == NULL)
	{
		ERROR ("write_riemann plugin: calloc failed.");
		riemann_msg_protobuf_free (msg);
		return (NULL);
	}

	if (host->store_rates)
	{
		rates = uc_get_rate (ds, vl);
		if (rates == NULL)
		{
			ERROR ("write_riemann plugin: uc_get_rate failed.");
			riemann_msg_protobuf_free (msg);
			return (NULL);
		}
	}

	for (i = 0; i < msg->n_events; i++)
	{
		msg->events[i] = riemann_value_to_protobuf (host, ds, vl,
							    (int) i, rates, statuses[i]);
		if (msg->events[i] == NULL)
		{
			riemann_msg_protobuf_free (msg);
			sfree (rates);
			return (NULL);
		}
	}

	sfree (rates);
	return (msg);
}