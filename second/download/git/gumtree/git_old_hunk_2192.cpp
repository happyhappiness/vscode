		die("revision walk setup failed");
	if (revs->tree_objects)
		mark_edges_uninteresting(revs, NULL);
}

static void exit_if_skipped_commits(struct commit_list *tried,
				    const unsigned char *bad)
{
	if (!tried)
		return;

	printf("There are only 'skip'ped commits left to test.\n"
	       "The first bad commit could be any of:\n");
	print_commit_list(tried, "%s\n", "%s\n");
	if (bad)
		printf("%s\n", sha1_to_hex(bad));
	printf("We cannot bisect more!\n");
	exit(2);
}

static int is_expected_rev(const unsigned char *sha1)
{
	const char *filename = git_path("BISECT_EXPECTED_REV");
	struct stat st;
	struct strbuf str = STRBUF_INIT;
	FILE *fp;
	int res = 0;
