static void handle_skipped_merge_base(const unsigned char *mb)
{
	char *mb_hex = sha1_to_hex(mb);
	char *bad_hex = sha1_to_hex(current_bad_oid->hash);
	char *good_hex = join_sha1_array_hex(&good_revs, ' ');

	warning("the merge base between %s and [%s] "
		"must be skipped.\n"
		"So we cannot be sure the first %s commit is "
		"between %s and %s.\n"
		"We continue anyway.",
		bad_hex, good_hex, term_bad, mb_hex, bad_hex);
	free(good_hex);
}