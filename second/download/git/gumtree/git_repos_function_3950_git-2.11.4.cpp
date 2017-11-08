static int peel_onion(const char *name, int len, unsigned char *sha1,
		      unsigned lookup_flags)
{
	unsigned char outer[20];
	const char *sp;
	unsigned int expected_type = 0;
	struct object *o;

	/*
	 * "ref^{type}" dereferences ref repeatedly until you cannot
	 * dereference anymore, or you get an object of given type,
	 * whichever comes first.  "ref^{}" means just dereference
	 * tags until you get a non-tag.  "ref^0" is a shorthand for
	 * "ref^{commit}".  "commit^{tree}" could be used to find the
	 * top-level tree of the given commit.
	 */
	if (len < 4 || name[len-1] != '}')
		return -1;

	for (sp = name + len - 1; name <= sp; sp--) {
		int ch = *sp;
		if (ch == '{' && name < sp && sp[-1] == '^')
			break;
	}
	if (sp <= name)
		return -1;

	sp++; /* beginning of type name, or closing brace for empty */
	if (starts_with(sp, "commit}"))
		expected_type = OBJ_COMMIT;
	else if (starts_with(sp, "tag}"))
		expected_type = OBJ_TAG;
	else if (starts_with(sp, "tree}"))
		expected_type = OBJ_TREE;
	else if (starts_with(sp, "blob}"))
		expected_type = OBJ_BLOB;
	else if (starts_with(sp, "object}"))
		expected_type = OBJ_ANY;
	else if (sp[0] == '}')
		expected_type = OBJ_NONE;
	else if (sp[0] == '/')
		expected_type = OBJ_COMMIT;
	else
		return -1;

	lookup_flags &= ~GET_SHA1_DISAMBIGUATORS;
	if (expected_type == OBJ_COMMIT)
		lookup_flags |= GET_SHA1_COMMITTISH;
	else if (expected_type == OBJ_TREE)
		lookup_flags |= GET_SHA1_TREEISH;

	if (get_sha1_1(name, sp - name - 2, outer, lookup_flags))
		return -1;

	o = parse_object(outer);
	if (!o)
		return -1;
	if (!expected_type) {
		o = deref_tag(o, name, sp - name - 2);
		if (!o || (!o->parsed && !parse_object(o->oid.hash)))
			return -1;
		hashcpy(sha1, o->oid.hash);
		return 0;
	}

	/*
	 * At this point, the syntax look correct, so
	 * if we do not get the needed object, we should
	 * barf.
	 */
	o = peel_to_type(name, len, o, expected_type);
	if (!o)
		return -1;

	hashcpy(sha1, o->oid.hash);
	if (sp[0] == '/') {
		/* "$commit^{/foo}" */
		char *prefix;
		int ret;
		struct commit_list *list = NULL;

		/*
		 * $commit^{/}. Some regex implementation may reject.
		 * We don't need regex anyway. '' pattern always matches.
		 */
		if (sp[1] == '}')
			return 0;

		prefix = xstrndup(sp + 1, name + len - 1 - (sp + 1));
		commit_list_insert((struct commit *)o, &list);
		ret = get_sha1_oneline(prefix, sha1, list);
		free(prefix);
		return ret;
	}
	return 0;
}