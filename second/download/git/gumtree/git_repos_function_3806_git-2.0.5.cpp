static int blame_chunk_cb(long start_a, long count_a,
			  long start_b, long count_b, void *data)
{
	struct blame_chunk_cb_data *d = data;
	blame_chunk(d->sb, d->tlno, d->plno, start_b, d->target, d->parent);
	d->plno = start_a + count_a;
	d->tlno = start_b + count_b;
	return 0;
}