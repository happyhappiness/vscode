	found_match++;

	/* This changes the semantics slightly that even under quiet we
	 * detect and return error if the repository is corrupt and
	 * ref points at a nonexistent object.
	 */
	if (!has_sha1_file(sha1))
		die("git show-ref: bad ref %s (%s)", refname,
		    sha1_to_hex(sha1));

	if (quiet)
		return 0;

	show_one(refname, sha1);

	if (!deref_tags)
		return 0;

	if (!peel_ref(refname, peeled)) {
		hex = find_unique_abbrev(peeled, abbrev);
		printf("%s %s^{}\n", hex, refname);
	}
	return 0;
}

static int add_existing(const char *refname, const unsigned char *sha1, int flag, void *cbdata)
{
	struct string_list *list = (struct string_list *)cbdata;
	string_list_insert(list, refname);
	return 0;
}

