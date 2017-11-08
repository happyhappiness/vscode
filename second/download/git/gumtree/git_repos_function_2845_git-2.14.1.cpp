int warn_on_fopen_errors(const char *path)
{
	if (errno != ENOENT && errno != ENOTDIR) {
		warn_on_inaccessible(path);
		return -1;
	}

	return 0;
}