int close_istream(struct git_istream *st)
{
	int r = st->vtbl->close(st);
	free(st);
	return r;
}