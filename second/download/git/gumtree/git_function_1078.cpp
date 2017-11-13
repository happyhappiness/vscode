static void freshen_shared_index(char *base_sha1_hex, int warn)
{
	char *shared_index = git_pathdup("sharedindex.%s", base_sha1_hex);
	if (!check_and_freshen_file(shared_index, 1) && warn)
		warning("could not freshen shared index '%s'", shared_index);
	free(shared_index);
}