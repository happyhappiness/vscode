static int get_short_sha1(const char *name, int len, unsigned char *sha1,
			  unsigned flags)
{
	int status;
	char hex_pfx[40];
	unsigned char bin_pfx[20];
	struct disambiguate_state ds;
	int quietly = !!(flags & GET_SHA1_QUIETLY);

	if (len < MINIMUM_ABBREV || len > 40)
		return -1;
	if (prepare_prefixes(name, len, bin_pfx, hex_pfx) < 0)
		return -1;

	prepare_alt_odb();

	memset(&ds, 0, sizeof(ds));
	if (flags & GET_SHA1_COMMIT)
		ds.fn = disambiguate_commit_only;
	else if (flags & GET_SHA1_COMMITTISH)
		ds.fn = disambiguate_committish_only;
	else if (flags & GET_SHA1_TREE)
		ds.fn = disambiguate_tree_only;
	else if (flags & GET_SHA1_TREEISH)
		ds.fn = disambiguate_treeish_only;
	else if (flags & GET_SHA1_BLOB)
		ds.fn = disambiguate_blob_only;

	find_short_object_filename(len, hex_pfx, &ds);
	find_short_packed_object(len, bin_pfx, &ds);
	status = finish_object_disambiguation(&ds, sha1);

	if (!quietly && (status == SHORT_NAME_AMBIGUOUS))
		return error("short SHA1 %.*s is ambiguous.", len, hex_pfx);
	return status;
}