FILE *fopen_or_warn(const char *path, const char *mode)
{
	FILE *fp = fopen(path, mode);

	if (fp)
		return fp;

	warn_on_fopen_errors(path);
	return NULL;
}