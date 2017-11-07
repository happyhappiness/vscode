static void free_discovery(struct discovery *d)
{
	if (d) {
		if (d == last_discovery)
			last_discovery = NULL;
		free(d->shallow.sha1);
		free(d->buf_alloc);
		free_refs(d->refs);
		free(d);
	}
}