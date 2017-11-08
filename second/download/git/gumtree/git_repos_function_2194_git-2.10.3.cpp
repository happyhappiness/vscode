static int chdir_len(const char *orig, int len)
{
	char *path = xmemdupz(orig, len);
	int r = chdir(path);
	free(path);
	return r;
}