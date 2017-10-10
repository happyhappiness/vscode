		else if (c >= 'A' && c <='F') {
			val = c - 'A' + 10;
			c -= 'A' - 'a';
		}
		else
			return -1;
		ds->hex_pfx[i] = c;
		if (!(i & 1))
			val <<= 4;
		ds->bin_pfx[i >> 1] |= val;
	}

	ds->len = len;
	ds->hex_pfx[len] = '\0';
	prepare_alt_odb();
	return 0;
}

static int show_ambiguous_object(const unsigned char *sha1, void *data)
{
	const struct disambiguate_state *ds = data;
	struct strbuf desc = STRBUF_INIT;
	int type;

	if (ds->fn && !ds->fn(sha1, ds->cb_data))
		return 0;

	type = sha1_object_info(sha1, NULL);
	if (type == OBJ_COMMIT) {
		struct commit *commit = lookup_commit(sha1);
		if (commit) {
			struct pretty_print_context pp = {0};
			pp.date_mode.type = DATE_SHORT;
			format_commit_message(commit, " %ad - %s", &desc, &pp);
		}
	} else if (type == OBJ_TAG) {
		struct tag *tag = lookup_tag(sha1);
		if (!parse_tag(tag) && tag->tag)
			strbuf_addf(&desc, " %s", tag->tag);
	}

	advise("  %s %s%s",
	       find_unique_abbrev(sha1, DEFAULT_ABBREV),
	       typename(type) ? typename(type) : "unknown type",
	       desc.buf);

	strbuf_release(&desc);
	return 0;
}

static int get_short_sha1(const char *name, int len, unsigned char *sha1,
			  unsigned flags)
{
	int status;
	struct disambiguate_state ds;
	int quietly = !!(flags & GET_SHA1_QUIETLY);

	if (init_object_disambiguation(name, len, &ds) < 0)
		return -1;

	if (HAS_MULTI_BITS(flags & GET_SHA1_DISAMBIGUATORS))
		die("BUG: multiple get_short_sha1 disambiguator flags");

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
	else
		ds.fn = default_disambiguate_hint;

	find_short_object_filename(&ds);
	find_short_packed_object(&ds);
	status = finish_object_disambiguation(&ds, sha1);

	if (!quietly && (status == SHORT_NAME_AMBIGUOUS)) {
		error(_("short SHA1 %s is ambiguous"), ds.hex_pfx);

		/*
		 * We may still have ambiguity if we simply saw a series of
		 * candidates that did not satisfy our hint function. In
		 * that case, we still want to show them, so disable the hint
		 * function entirely.
		 */
		if (!ds.ambiguous)
			ds.fn = NULL;

		advise(_("The candidates are:"));
		for_each_abbrev(ds.hex_pfx, show_ambiguous_object, &ds);
	}

	return status;
}

static int collect_ambiguous(const unsigned char *sha1, void *data)
{
	sha1_array_append(data, sha1);
	return 0;
}

int for_each_abbrev(const char *prefix, each_abbrev_fn fn, void *cb_data)
{
	struct sha1_array collect = SHA1_ARRAY_INIT;
	struct disambiguate_state ds;
	int ret;

	if (init_object_disambiguation(prefix, strlen(prefix), &ds) < 0)
		return -1;

	ds.always_call_fn = 1;
	ds.fn = collect_ambiguous;
	ds.cb_data = &collect;
	find_short_object_filename(&ds);
	find_short_packed_object(&ds);

	ret = sha1_array_for_each_unique(&collect, fn, cb_data);
	sha1_array_clear(&collect);
	return ret;
}

/*
 * Return the slot of the most-significant bit set in "val". There are various
 * ways to do this quickly with fls() or __builtin_clzl(), but speed is
 * probably not a big deal here.
 */
static unsigned msb(unsigned long val)
{
	unsigned r = 0;
	while (val >>= 1)
		r++;
	return r;
}

int find_unique_abbrev_r(char *hex, const unsigned char *sha1, int len)
{
	int status, exists;

	if (len < 0) {
		unsigned long count = approximate_object_count();
		/*
		 * Add one because the MSB only tells us the highest bit set,
		 * not including the value of all the _other_ bits (so "15"
		 * is only one off of 2^4, but the MSB is the 3rd bit.
		 */
		len = msb(count) + 1;
		/*
		 * We now know we have on the order of 2^len objects, which
		 * expects a collision at 2^(len/2). But we also care about hex
		 * chars, not bits, and there are 4 bits per hex. So all
		 * together we need to divide by 2; but we also want to round
		 * odd numbers up, hence adding one before dividing.
		 */
		len = (len + 1) / 2;
		/*
		 * For very small repos, we stick with our regular fallback.
		 */
		if (len < FALLBACK_DEFAULT_ABBREV)
			len = FALLBACK_DEFAULT_ABBREV;
	}

	sha1_to_hex_r(hex, sha1);
	if (len == 40 || !len)
		return 40;
	exists = has_sha1_file(sha1);
	while (len < 40) {
		unsigned char sha1_ret[20];
