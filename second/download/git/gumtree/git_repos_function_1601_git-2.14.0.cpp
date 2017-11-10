struct diff_filespec *alloc_filespec(const char *path)
{
	struct diff_filespec *spec;

	FLEXPTR_ALLOC_STR(spec, path, path);
	spec->count = 1;
	spec->is_binary = -1;
	return spec;
}