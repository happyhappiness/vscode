FILE *mingw_freopen (const char *filename, const char *otype, FILE *stream)
{
	if (filename && !strcmp(filename, "/dev/null"))
		filename = "nul";
	return freopen(filename, otype, stream);
}