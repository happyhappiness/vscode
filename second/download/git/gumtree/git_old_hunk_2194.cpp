	exit(1);
}

static void handle_skipped_merge_base(const unsigned char *mb)
{
	char *mb_hex = sha1_to_hex(mb);
	char *bad_hex = sha1_to_hex(current_bad_sha1);
	char *good_hex = join_sha1_array_hex(&good_revs, ' ');

	warning("the merge base between %s and [%s] "
		"must be skipped.\n"
		"So we cannot be sure the first bad commit is "
		"between %s and %s.\n"
