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