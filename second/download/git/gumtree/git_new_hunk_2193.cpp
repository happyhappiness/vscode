static struct commit **get_bad_and_good_commits(int *rev_nr)
{
	int len = 1 + good_revs.nr;
	struct commit **rev = xmalloc(len * sizeof(*rev));
	int i, n = 0;

	rev[n++] = get_commit_reference(current_bad_oid->hash);
	for (i = 0; i < good_revs.nr; i++)
		rev[n++] = get_commit_reference(good_revs.sha1[i]);
	*rev_nr = n;

	return rev;
}

static void handle_bad_merge_base(void)
{
	if (is_expected_rev(current_bad_oid)) {
		char *bad_hex = oid_to_hex(current_bad_oid);
		char *good_hex = join_sha1_array_hex(&good_revs, ' ');

		fprintf(stderr, "The merge base %s is bad.\n"
			"This means the bug has been fixed "
			"between %s and [%s].\n",
			bad_hex, bad_hex, good_hex);
