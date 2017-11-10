static int count_cruft(const char *basename, const char *path, void *data)
{
	loose_garbage(path);
	return 0;
}