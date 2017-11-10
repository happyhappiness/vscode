static void check_merge_bases(int no_checkout)
{
	struct commit_list *result;
	int rev_nr;
	struct commit **rev = get_bad_and_good_commits(&rev_nr);

	result = get_merge_bases_many(rev[0], rev_nr - 1, rev + 1);

	for (; result; result = result->next) {
		const unsigned char *mb = result->item->object.sha1;
		if (!hashcmp(mb, current_bad_sha1)) {
			handle_bad_merge_base();
		} else if (0 <= sha1_array_lookup(&good_revs, mb)) {
			continue;
		} else if (0 <= sha1_array_lookup(&skipped_revs, mb)) {
			handle_skipped_merge_base(mb);
		} else {
			printf("Bisecting: a merge base must be tested\n");
			exit(bisect_checkout(sha1_to_hex(mb), no_checkout));
		}
	}

	free(rev);
	free_commit_list(result);
}