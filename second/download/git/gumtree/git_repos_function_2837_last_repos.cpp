void *xmallocz_gently(size_t size)
{
	return do_xmallocz(size, 1);
}