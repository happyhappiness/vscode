int file_exists(const char *f)
{
	struct stat sb;
	return lstat(f, &sb) == 0;
}