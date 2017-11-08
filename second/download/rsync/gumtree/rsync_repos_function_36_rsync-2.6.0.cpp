void free_exclude_list(struct exclude_struct ***listp)
{
	struct exclude_struct **list = *listp;

	if (verbose > 2)
		rprintf(FINFO,"clearing exclude list\n");

	if (!list)
		return;

	while (*list)
		free_exclude(*list++);

	free(*listp);
	*listp = NULL;
}