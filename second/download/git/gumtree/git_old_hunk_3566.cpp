{
	if (!tried)
		return;

	printf("There are only 'skip'ped commits left to test.\n"
	       "The first %s commit could be any of:\n", term_bad);
	print_commit_list(tried, "%s\n", "%s\n");
	if (bad)
		printf("%s\n", oid_to_hex(bad));
	printf("We cannot bisect more!\n");
	exit(2);
}

static int is_expected_rev(const struct object_id *oid)
{
	const char *filename = git_path_bisect_expected_rev();
