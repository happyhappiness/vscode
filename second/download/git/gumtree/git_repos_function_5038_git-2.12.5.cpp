static void handle_ref_opt(const char *pattern, const char *prefix)
{
	if (pattern)
		for_each_glob_ref_in(show_reference, pattern, prefix, NULL);
	else
		for_each_ref_in(prefix, show_reference, NULL);
	clear_ref_exclusion(&ref_excludes);
}