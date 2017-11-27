static int ignore_ds (const char *name)
{
	int i;

	if (match_ds_g == NULL)
		return (0);

	for (i = 0; i < match_ds_num_g; i++)
		if (strcasecmp (match_ds_g[i], name) == 0)
			return (0);

	return (1);
}