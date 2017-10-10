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

static int is_expected_rev(const struct object_id *oid)
{
	const char *filename = git_path("BISECT_EXPECTED_REV");
	struct stat st;
	struct strbuf str = STRBUF_INIT;
	FILE *fp;
	int res = 0;

	if (stat(filename, &st) || !S_ISREG(st.st_mode))
