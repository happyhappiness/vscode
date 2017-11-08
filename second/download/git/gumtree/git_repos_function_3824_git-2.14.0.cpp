static struct diff_filespec *noindex_filespec(const char *name, int mode)
{
	struct diff_filespec *s;

	if (!name)
		name = "/dev/null";
	s = alloc_filespec(name);
	fill_filespec(s, &null_oid, 0, mode);
	if (name == file_from_standard_input)
		populate_from_stdin(s);
	return s;
}