static void submit_antx (const char *dev, const char *name,
		u_int32_t *vals, int vals_num)
{
	char ti2[16];
	int i;

	for (i = 0; i < vals_num; i++)
	{
		if (vals[i] == 0)
			continue;

		ssnprintf (ti2, sizeof (ti2), "%i", i);
		submit_counter (dev, "ath_stat", name, ti2,
				(counter_t) vals[i]);
	}
}