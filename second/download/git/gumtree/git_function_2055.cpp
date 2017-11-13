static void exit_if_skipped_commits(struct commit_list *tried,
				    const struct object_id *bad)
{
	if (!tried)
		return;

	printf("There are only 'skip'ped commits left to test.\n"
	       "The first bad commit could be any of:\n");
	print_commit_list(tried, "%s\n", "%s\n");
	if (bad)
		printf("%s\n", oid_to_hex(bad));
	printf("We cannot bisect more!\n");
	exit(2);
}