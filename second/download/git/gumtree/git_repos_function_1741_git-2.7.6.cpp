static int freshen_file(const char *fn)
{
	struct utimbuf t;
	t.actime = t.modtime = time(NULL);
	return !utime(fn, &t);
}