		else if (c >= 'A' && c <='F') {
			val = c - 'A' + 10;
			c -= 'A' - 'a';
		}
		else
			return -1;
		hex_pfx[i] = c;
		if (!(i & 1))
			val <<= 4;
		bin_pfx[i >> 1] |= val;
	}
	return 0;
}

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

int for_each_abbrev(const char *prefix, each_abbrev_fn fn, void *cb_data)
{
	char hex_pfx[40];
	unsigned char bin_pfx[20];
	struct disambiguate_state ds;
	int len = strlen(prefix);

	if (len < MINIMUM_ABBREV || len > 40)
		return -1;
	if (prepare_prefixes(prefix, len, bin_pfx, hex_pfx) < 0)
		return -1;

	prepare_alt_odb();

	memset(&ds, 0, sizeof(ds));
	ds.always_call_fn = 1;
	ds.cb_data = cb_data;
	ds.fn = fn;

	find_short_object_filename(len, hex_pfx, &ds);
	find_short_packed_object(len, bin_pfx, &ds);
	return ds.ambiguous;
}

int find_unique_abbrev_r(char *hex, const unsigned char *sha1, int len)
{
	int status, exists;

	sha1_to_hex_r(hex, sha1);
	if (len == 40 || !len)
		return 40;
	exists = has_sha1_file(sha1);
	while (len < 40) {
		unsigned char sha1_ret[20];
