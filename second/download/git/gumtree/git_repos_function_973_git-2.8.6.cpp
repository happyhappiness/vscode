static int swap_prereleases(const void *p1_,
			    const void *p2_,
			    int *diff)
{
	const char *p1 = p1_;
	const char *p2 = p2_;
	int i, i1 = -1, i2 = -1;

	for (i = 0; i < prereleases->nr; i++) {
		const char *suffix = prereleases->items[i].string;
		if (i1 == -1 && starts_with(p1, suffix))
			i1 = i;
		if (i2 == -1 && starts_with(p2, suffix))
			i2 = i;
	}
	if (i1 == -1 && i2 == -1)
		return 0;
	if (i1 >= 0 && i2 >= 0)
		*diff = i1 - i2;
	else if (i1 >= 0)
		*diff = -1;
	else /* if (i2 >= 0) */
		*diff = 1;
	return 1;
}