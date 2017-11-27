static range_t range_warning_g;
static int consolitation_g = CON_NONE;

static char **match_ds_g = NULL;
static int    match_ds_num_g = 0;

static int ignore_ds (const char *name)
{
	int i;

	if (match_ds_g == NULL)
		return (0);

	for (i = 0; i < match_ds_num_g; i++)
		if (strcasecmp (match_ds_g[i], name) == 0)
			return (0);

	return (1);
} /* int ignore_ds */

static void parse_range (char *string, range_t *range)
{
	char *min_ptr;
	char *max_ptr;

