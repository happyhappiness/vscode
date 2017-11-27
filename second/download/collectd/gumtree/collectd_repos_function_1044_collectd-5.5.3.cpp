static data_volume_perf_t *get_volume_perf (cfg_volume_perf_t *cvp, /* {{{ */
		const char *name)
{
	data_volume_perf_t *last;
	data_volume_perf_t *new;

	int ignore_octets = 0;
	int ignore_operations = 0;
	int ignore_latency = 0;

	if ((cvp == NULL) || (name == NULL))
		return (NULL);

	last = cvp->volumes;
	while (last != NULL)
	{
		if (strcmp (last->name, name) == 0)
			return (last);

		if (last->next == NULL)
			break;

		last = last->next;
	}

	/* Check the ignorelists. If *all three* tell us to ignore a volume, return
	 * NULL. */
	ignore_octets = ignorelist_match (cvp->il_octets, name);
	ignore_operations = ignorelist_match (cvp->il_operations, name);
	ignore_latency = ignorelist_match (cvp->il_latency, name);
	if ((ignore_octets != 0) || (ignore_operations != 0)
			|| (ignore_latency != 0))
		return (NULL);

	/* Not found: allocate. */
	new = malloc (sizeof (*new));
	if (new == NULL)
		return (NULL);
	memset (new, 0, sizeof (*new));
	new->next = NULL;

	new->name = strdup (name);
	if (new->name == NULL)
	{
		sfree (new);
		return (NULL);
	}

	if (ignore_octets == 0)
		new->flags |= CFG_VOLUME_PERF_IO;
	if (ignore_operations == 0)
		new->flags |= CFG_VOLUME_PERF_OPS;
	if (ignore_latency == 0)
		new->flags |= CFG_VOLUME_PERF_LATENCY;

	/* Add to end of list. */
	if (last == NULL)
		cvp->volumes = new;
	else
		last->next = new;

	return (new);
}