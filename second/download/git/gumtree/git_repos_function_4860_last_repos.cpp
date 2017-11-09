static int xdl_cleanup_merge(xdmerge_t *c)
{
	int count = 0;
	xdmerge_t *next_c;

	/* were there conflicts? */
	for (; c; c = next_c) {
		if (c->mode == 0)
			count++;
		next_c = c->next;
		free(c);
	}
	return count;
}