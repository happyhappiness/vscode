static void rearrange_packed_git(void)
{
	struct packed_git **ary, *p;
	int i, n;

	for (n = 0, p = packed_git; p; p = p->next)
		n++;
	if (n < 2)
		return;

	/* prepare an array of packed_git for easier sorting */
	ary = xcalloc(n, sizeof(struct packed_git *));
	for (n = 0, p = packed_git; p; p = p->next)
		ary[n++] = p;

	qsort(ary, n, sizeof(struct packed_git *), sort_pack);

	/* link them back again */
	for (i = 0; i < n - 1; i++)
		ary[i]->next = ary[i + 1];
	ary[n - 1]->next = NULL;
	packed_git = ary[0];

	free(ary);
}