int fnmatch_icase(const char *pattern, const char *string, int flags)
{
	return wildmatch(pattern, string,
			 flags | (ignore_case ? WM_CASEFOLD : 0),
			 NULL);
}