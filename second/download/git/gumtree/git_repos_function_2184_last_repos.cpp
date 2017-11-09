int check_and_freshen_file(const char *fn, int freshen)
{
	if (access(fn, F_OK))
		return 0;
	if (freshen && !freshen_file(fn))
		return 0;
	return 1;
}