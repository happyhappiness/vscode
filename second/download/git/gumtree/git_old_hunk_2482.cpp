
static void handle_bad_merge_base(void)
{
	if (is_expected_rev(current_bad_oid)) {
		char *bad_hex = oid_to_hex(current_bad_oid);
		char *good_hex = join_sha1_array_hex(&good_revs, ' ');

		fprintf(stderr, "The merge base %s is bad.\n"
			"This means the bug has been fixed "
			"between %s and [%s].\n",
			bad_hex, bad_hex, good_hex);

		exit(3);
	}

	fprintf(stderr, "Some good revs are not ancestor of the bad rev.\n"
		"git bisect cannot work properly in this case.\n"
		"Maybe you mistake good and bad revs?\n");
	exit(1);
}

static void handle_skipped_merge_base(const unsigned char *mb)
{
	char *mb_hex = sha1_to_hex(mb);
	char *bad_hex = sha1_to_hex(current_bad_oid->hash);
	char *good_hex = join_sha1_array_hex(&good_revs, ' ');

	warning("the merge base between %s and [%s] "
		"must be skipped.\n"
		"So we cannot be sure the first bad commit is "
		"between %s and %s.\n"
		"We continue anyway.",
		bad_hex, good_hex, mb_hex, bad_hex);
	free(good_hex);
}

/*
 * "check_merge_bases" checks that merge bases are not "bad".
 *
