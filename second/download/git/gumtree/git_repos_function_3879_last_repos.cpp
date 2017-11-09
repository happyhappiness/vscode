ssize_t read_istream(struct git_istream *st, void *buf, size_t sz)
{
	return st->vtbl->read(st, buf, sz);
}