FILE *mingw_fopen (const char *filename, const char *otype)
{
	if (filename && !strcmp(filename, "/dev/null"))
		filename = "nul";
	return fopen(filename, otype);
}