static void handle_skipped_merge_base(const struct object_id *mb)
{
	char *mb_hex = oid_to_hex(mb);
	char *bad_hex = oid_to_hex(current_bad_oid);
	char *good_hex = join_sha1_array_hex(&good_revs, ' ');

	warning(_("the merge base between %s and [%s] "
		"must be skipped.\n"
		"So we cannot be sure the first %s commit is "
		"between %s and %s.\n"
		"We continue anyway."),
		bad_hex, good_hex, term_bad, mb_hex, bad_hex);
	free(good_hex);
}