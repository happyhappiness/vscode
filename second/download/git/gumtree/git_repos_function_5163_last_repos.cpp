static int prune_subdir(unsigned int nr, const char *path, void *data)
{
	if (!show_only)
		rmdir(path);
	return 0;
}