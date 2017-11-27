static int rra_get (char ***ret, const value_list_t *vl)
{
	char **rra_def;
	int rra_num;

	int *rts;
	int  rts_num;

	int rra_max;

	int span;

	int cdp_num;
	int cdp_len;
	int i, j;

	char buffer[64];

	/* The stepsize we use here: If it is user-set, use it. If not, use the
	 * interval of the value-list. */
	int ss;

	if (rrarows <= 0)
	{
		*ret = NULL;
		return (-1);
	}

	ss = (stepsize > 0) ? stepsize : vl->interval;
	if (ss <= 0)
	{
		*ret = NULL;
		return (-1);
	}

	/* Use the configured timespans or fall back to the built-in defaults */
	if (rra_timespans_custom_num != 0)
	{
		rts = rra_timespans_custom;
		rts_num = rra_timespans_custom_num;
	}
	else
	{
		rts = rra_timespans;
		rts_num = rra_timespans_num;
	}

	rra_max = rts_num * rra_types_num;

	if ((rra_def = (char **) malloc ((rra_max + 1) * sizeof (char *))) == NULL)
		return (-1);
	memset (rra_def, '\0', (rra_max + 1) * sizeof (char *));
	rra_num = 0;

	cdp_len = 0;
	for (i = 0; i < rts_num; i++)
	{
		span = rts[i];

		if ((span / ss) < rrarows)
			span = ss * rrarows;

		if (cdp_len == 0)
			cdp_len = 1;
		else
			cdp_len = (int) floor (((double) span)
					/ ((double) (rrarows * ss)));

		cdp_num = (int) ceil (((double) span)
				/ ((double) (cdp_len * ss)));

		for (j = 0; j < rra_types_num; j++)
		{
			if (rra_num >= rra_max)
				break;

			if (ssnprintf (buffer, sizeof (buffer), "RRA:%s:%3.1f:%u:%u",
						rra_types[j], xff,
						cdp_len, cdp_num) >= sizeof (buffer))
			{
				ERROR ("rra_get: Buffer would have been truncated.");
				continue;
			}

			rra_def[rra_num++] = sstrdup (buffer);
		}
	}

#if COLLECT_DEBUG
	DEBUG ("rra_num = %i", rra_num);
	for (i = 0; i < rra_num; i++)
		DEBUG ("  %s", rra_def[i]);
#endif

	*ret = rra_def;
	return (rra_num);
}